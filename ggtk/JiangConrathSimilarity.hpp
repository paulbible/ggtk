/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef JIANG_CONRATH_SIMILARITY
#define JIANG_CONRATH_SIMILARITY

#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/GoGraph.hpp>

/*! \class JiangConrathSimilarity
	\brief A class to calculate Jiang Conrath similarity between 2 terms

	This class calculates Jiang Conrath similarity.
	
	Jiang, J. J., & Conrath, D. W. (1997). Semantic similarity based on corpus 
	  statistics and lexical taxonomy. In Proc. of 10th International Conference
	  on Research on Computational Linguistics, Taiwan.

	P. W. Lord, R. D. Stevens, A. Brass, and C. A. Goble, 
	 "Semantic similarity measures as tools for exploring the gene ontology,"
	 Pac Symp Biocomput, pp. 601-12, 2003.
	  
	distance = IC(termA) + IC(termB) - 2*IC(MICA)
	maxDistance = 2*IC(single annotaiotn)
	similarity = 1 - distance/maxDistance
	(see Lord et al.)

*/
class JiangConrathSimilarity: public TermSimilarityInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline JiangConrathSimilarity(GoGraph* goGraph,TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
	}

	//! A method for calculating term-to-term similarity for GO terms using JiangConrath similarity
	/*!
		This method returns the JiangConrath similarity or the information content of the most informative common ancestor.
	*/
	inline double calculateTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if(!_icMap.hasTerm(goTermA) || !_icMap.hasTerm(goTermB)){
			return 0.0;
		}

		//if not from same ontology, return 0;
		if(_goGraph->getTermOntology(goTermA) != _goGraph->getTermOntology(goTermB)){
			return 0;
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

		//get the MICA
		std::string mica = getMICA(ancestorsA,ancestorsB);

		double dist = (_icMap[goTermA] + _icMap[goTermB] - 2*_icMap[mica]);

		return 1 - (dist/(2.0*maxIC));
	}

	//! A method for calculating term-to-term similarity for GO terms using Normalized JiangConrath similarity
	/*!
		This method returns the JiangConrath similarity scaled between 0 and 1 [0,1] inclusive
	*/
	inline double calculateNormalizedTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if (!_icMap.hasTerm(goTermA) || !_icMap.hasTerm(goTermB)){
			return 0.0;
		}

		//JiangConrath's method is already normalized
		return calculateTermSimilarity(goTermA,goTermB);
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
