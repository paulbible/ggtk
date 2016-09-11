/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PEKAR_STAAB_SIMILARITY
#define PEKAR_STAAB_SIMILARITY

#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/TermDepthMap.hpp>
#include <ggtk/GoGraph.hpp>

/*! \class PekarStaabSimilarity
	\brief A class to calculate PekarStaab similarity between 2 terms

	This class calculates Pekar Staab similarity.
	
	V. Pekar and S. Staab, "Taxonomy learning: factoring the structure 
	 of a taxonomy into a semantic classification decision," in 
	 Proc. of 19th International Conference on Computational Linguistics. 
	 Morristown NJ USA: Association for Computational Linguistics, pp. 1-7, 2002.

	H. Yu, L. Gao, K. Tu, and Z. Guo, "Broadly predicting specific gene 
	 functions with expression similarity and taxonomy similarity,"
	 Gene, vol. 352, pp. 75-81, Jun 6 2005.
	  
    lowest common ancestor (LCA)
	GraphDist(LCA,root)/(GraphDist(a,LCA)+GraphDist(b,LCA)+GraphDist(LCA,root))

*/
class PekarStaabSimilarity: public TermSimilarityInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline PekarStaabSimilarity(GoGraph* goGraph,TermDepthMap &icMap){
		_goGraph = goGraph;
		_depthMap = icMap;
	}

	//! A method for calculating term-to-term similarity for GO terms using Pekar Staab similarity
	/*!
		This method returns the PekarStaab similarity.
	*/
	inline double calculateTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if (!_depthMap.hasTerm(goTermA) || !_depthMap.hasTerm(goTermB)){
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

		std::string lca = getLCA(ancestorsA,ancestorsB);

		//std::cout << "Pekar Staab LCA " << lca << std::endl;

		double lcaDepth = _depthMap[lca];

		//std::cout << "Pekar Staab LCA " << lcaDepth << std::endl;
		//std::cout << "Pekar Staab delta(a,lca) " << (_depthMap[goTermA] - lcaDepth) << std::endl;
		//std::cout << "Pekar Staab delta(b,lca) " << (_depthMap[goTermB] - lcaDepth) << std::endl;


		//return the similarity of Pekar Staab
		return (double)lcaDepth/( (_depthMap[goTermA] - lcaDepth) + (_depthMap[goTermB] - lcaDepth) +lcaDepth);
	}

	//! A method for calculating term-to-term similarity for GO terms using Normalized Pekar Staab similarity
	/*!
		This method returns the PekarStaab similarity scaled between 0 and 1 [0,1] inclusive
	*/
	inline double calculateNormalizedTermSimilarity(std::string goTermA, std::string goTermB){
		//if the terms do not exit return 0.0 similarity
		if (!_depthMap.hasTerm(goTermA) || !_depthMap.hasTerm(goTermB)){
			return 0.0;
		}
		//Pekar and Staab's method is already normalized
		return calculateTermSimilarity(goTermA,goTermB);
	}

	//! A method for calculating the least common ancestor
	/*!
		This method searches the sets to determine the deepest common ancestor
	*/
	inline std::string getLCA(boost::unordered_set<std::string> &ancestorsA,boost::unordered_set<std::string> &ancestorsB){
		//get the first term as a start
		std::string lca = *ancestorsA.begin();
		//max depth
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
			if(_depthMap[currentTerm] > max){
				lca = currentTerm;
				max = _depthMap[currentTerm];
			}
		}

		return lca;
	}


private:

	GoGraph* _goGraph;
	TermDepthMap _depthMap;

};
#endif