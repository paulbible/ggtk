/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef RELEVANCE_SIMILARITY
#define RELEVANCE_SIMILARITY

#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/GoGraph.hpp>

//! A class to calculate Relevance similarity between 2 terms
/*! \class RelevanceSimilarity

	This class calculates Relevance similarity.
	
	A. Schlicker, F. S. Domingues, J. Rahnenfuhrer, and T. Lengauer, 
	 "A new measure for functional similarity of gene products based
	 on Gene Ontology," BMC Bioinformatics, vol. 7, p. 302, 2006.

	P. W. Lord, R. D. Stevens, A. Brass, and C. A. Goble, 
	 "Semantic similarity measures as tools for exploring the gene ontology,"
	 Pac Symp Biocomput, pp. 601-12, 2003.
	  
	  Basically this is Lin similarity scaled by the 
	   complement of the probability of the mica
	2 * IC(MICA) / ( IC(termA) + IC(termB) )*(1-p(Mica))
*/
class RelevanceSimilarity: public TermSimilarityInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline RelevanceSimilarity(GoGraph* goGraph,TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
	}

	//! A method for calculating term-to-term similarity for GO terms using Relevance similarity
	/*!
		This method returns the Relevance similarity.
	*/
	inline double calculateTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if (!_icMap.hasTerm(goTermA) || !_icMap.hasTerm(goTermB)){
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

		//return the normalized information content similarity of Relevance
		return (2*_icMap[mica]/(_icMap[goTermA]+_icMap[goTermB]))*(1-std::exp(-_icMap[mica]));
	}

	//! A method for calculating term-to-term similarity for GO terms using Normalized Relevance similarity
	/*!
		This method returns the Relevance similarity scaled between 0 and 1 [0,1] inclusive
	*/
	inline double calculateNormalizedTermSimilarity(std::string goTermA, std::string goTermB){
		//Relevance's method is already normalized
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