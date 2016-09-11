#ifndef RESNIK_SIMILARITY
#define RESNIK_SIMILARITY

#include <cmath>
#include <string>

#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/GoGraph.hpp>

#include <boost/unordered_set.hpp>

/*! \class ResnikSimilarity
	\brief A class to calculate resnik similarity between 2 terms

	This class calculates Resnik similarity.
	Philip Resnik (1995). "Using information content to evaluate semantic similarity in a taxonomy". 
	  In Chris S. Mellish (Ed.). Proceedings of the 14th international joint conference on Artificial intelligence (IJCAI'95)

    P. W. Lord, R. D. Stevens, A. Brass, and C. A. Goble, 
	 "Semantic similarity measures as tools for exploring the gene ontology,"
	 Pac Symp Biocomput, pp. 601-12, 2003.

	maximun information content of all shared ancestors
	IC(MICA)

*/
class ResnikSimilarity: public TermSimilarityInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline ResnikSimilarity(GoGraph* goGraph,TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
	}

	//! A method for calculating term-to-term similarity for GO terms using Resnik similarity
	/*!
		This method returns the Resnik similarity or the information content of the most informative common ancestor.
	*/
	inline double calculateTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if(!_icMap.hasTerm(goTermA) || !_icMap.hasTerm(goTermB)){
			return 0.0;
		}

		//if not from same ontology, return 0;
		if(_goGraph->getTermOntology(goTermA) != _goGraph->getTermOntology(goTermB)){
			return 0.0;
		}

		//create 2 sets
		boost::unordered_set<std::string> ancestorsA = _goGraph->getAncestorTerms(goTermA);
		ancestorsA.insert(goTermA);
		boost::unordered_set<std::string> ancestorsB = _goGraph->getAncestorTerms(goTermB);
		ancestorsB.insert(goTermB);

		//if either set is empty, return 0
		if(ancestorsA.size() == 0 || ancestorsB.size() == 0){
			return 0.0;
		}

		//get the MICA
		std::string mica = getMICA(ancestorsA,ancestorsB);

		//return the inforamtion content of the mica
		return _icMap[mica];
	}

	//! A method for calculating term-to-term similarity for GO terms using Normalized Resnik similarity
	/*!
		This method returns the Resnik similarity divided by the maximum possible similarity
	*/
	inline double calculateNormalizedTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if (!_icMap.hasTerm(goTermA) || !_icMap.hasTerm(goTermB)){
			return 0.0;
		}

		//call base similarity
		double resnik = calculateTermSimilarity(goTermA,goTermB);

		double maxIC;

		//select the correct ontology normalization factor
		GO::Onto ontoType = _goGraph->getTermOntology(goTermA);
		if(ontoType == GO::BP){
			maxIC = -std::log(_icMap.getMinBP());
		}else if(ontoType == GO::MF){
			maxIC = -std::log(_icMap.getMinMF());
		}else{
			maxIC = -std::log(_icMap.getMinCC());
		}

		return resnik/maxIC;
	}

	//! A method for calculating the most informative common ancestor
	/*!
		This method searches the sets to determine the most informatics ancestor.
	*/
	inline std::string getMICA(boost::unordered_set<std::string> &ancestorsA,boost::unordered_set<std::string> &ancestorsB){
		//get the first term as a start
		std::string mica = *ancestorsA.begin();
		double max = -1.0;

		//always traverse the shortest list
		if(ancestorsA.size() > ancestorsB.size()){
			ancestorsA.swap(ancestorsB);
		}

		//loop over shorter list
		boost::unordered_set<std::string>::iterator iter;
		for(iter = ancestorsA.begin(); iter != ancestorsA.end(); ++iter){
			//current string
			std::string currentTerm = *iter;

			if(ancestorsB.find(currentTerm) == ancestorsB.end()){
				//continue, not a shared ancestor term
				continue;
			}

			//if new max, update
			if(_icMap[currentTerm] > max){
				mica = currentTerm;
				max = _icMap[currentTerm];
			}
		}

		return mica;
	}


private:

	GoGraph* _goGraph;
	TermInformationContentMap _icMap;

};
#endif
