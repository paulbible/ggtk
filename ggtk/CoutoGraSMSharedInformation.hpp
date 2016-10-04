/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GRASM_SHARED_INFORMATION
#define GRASM_SHARED_INFORMATION

#include <ggtk/SharedInformationInterface.hpp>
#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/GoGraph.hpp>
#include <ggtk/Accumulators.hpp>
#include <ggtk/SetUtilities.hpp>

#include <utility>
#include <algorithm>

#include <boost/unordered_map.hpp>
#include <boost/graph/breadth_first_search.hpp>

/*! \class CoutoGraSMSharedInformation
	\brief A class to calculate shared infromation accross disjoint common ancetors using the exact algorithm as written in the paper.

	This class calculates shared infromation accross disjoint common ancetors.

    F. M. Couto, M. J. Silva, and P. M. Coutinho, "Measuring semantic similarity
	between Gene Ontology terms," Data & Knowledge Engineering, vol. 61, 
	pp. 137-152, Apr 2007.

	Couto proposing calculating this value a subsituite for the IC of the MICA in calculating
	 Resnik, Lin, and Jiang-Conrath

*/
class CoutoGraSMSharedInformation : public SharedInformationInterface{

public:
	
	//! A constructor
	/*!
		Creates the CoutoGraSMGreaterOrEqual class
	*/
	inline CoutoGraSMSharedInformation(GoGraph* goGraph, TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
		_pathMemory = boost::unordered_map<std::string, size_t>();
	}


	//! A method for determining the common disjunctive ancestors
	/*!
		This method returns the common disjunctive ancestors for two terms
	*/
	inline boost::unordered_set<std::string> getCommonDisjointAncestors(const std::string &termC1,const std::string &termC2){

		boost::unordered_set<std::string> ancestorsC1 = _goGraph->getAncestorTerms(termC1);
		ancestorsC1.insert(termC1);
		//std::cout << ancestorsC1.size() << std::endl;
		boost::unordered_set<std::string> ancestorsC2 = _goGraph->getAncestorTerms(termC2);
		ancestorsC2.insert(termC2);
		//std::cout << ancestorsC2.size() << std::endl;
		
		//Couto: CommonDisjAnc = {}
		boost::unordered_set<std::string> cda;

		if(termC1.compare(termC2) == 0){
			cda.insert(termC1);
			return cda;
		}

		//Couto: Anc = CommonAnc(c1,c2)
		boost::unordered_set<std::string> commonAncestors = SetUtilities::set_intersection(ancestorsC1,ancestorsC2);
		//std::cout << commonAncestors.size() << std::endl;

		std::vector<std::pair<double,std::string> > orderedCommonAncestors;

		

		//create a pair to associate a term with its information content
		boost::unordered_set<std::string>::iterator iter;
		for(iter = commonAncestors.begin(); iter != commonAncestors.end(); ++iter){
			std::string term = *iter;
			orderedCommonAncestors.push_back(std::pair<double,std::string>(_icMap[term],term));
		}

		//sort descending
		std::sort(orderedCommonAncestors.begin(),orderedCommonAncestors.end(),std::greater<std::pair<double,std::string> >());

		
		//start of main algorithm
		std::vector<std::pair<double,std::string> >::iterator pairIter;
		//Couto: for all a in sortDescByIC(Anc) do ...
		for(pairIter = orderedCommonAncestors.begin(); pairIter != orderedCommonAncestors.end(); ++pairIter){
			std::pair<double,std::string> myPair = *pairIter;
			//std::cout << myPair.first << " " << myPair.second << std::endl;

			std::string termA = myPair.second;

			//Couto: isDisj=true
			bool isDisj = true;

			//std::cout << "testing " << termA << std::endl;

			//Couto: for all cda in CommonDisjAnc do ...
			boost::unordered_set<std::string>::iterator cdaIter;
			for(cdaIter = cda.begin(); cdaIter != cda.end();++cdaIter){
				std::string termCda = *cdaIter;

				//std::cout << "VS " << termCda << std::endl;

				//continue if the terms are the same
				if(termCda.compare(termA) == 0){
					continue;
				}

				//Couto: isDisj = isDisj ^ ( DisjAnc(c1,(a,cda)) or DisjAnc(c2,(a,cda)) )
				isDisj = isDisj && (isDisjoint(termC1,termA,termCda) || isDisjoint(termC2,termA,termCda));

			}

			//Couto: if isDisj then...
			if(isDisj){
				//std::cout << myPair.second << " is cda " << std::endl;
				//Couto: addTo(CommonDisjAnc,a)
				cda.insert(myPair.second);
			}
		}
		return cda;
	}


	//! A method for determining if for a term c, a pair (a1,a2) is disjoint in c
	/*!
		This method returns
	*/
	inline bool isDisjoint(const std::string &termC, const std::string &termA1, const std::string &termA2){

		//std::cout << "isDisjoint " << termC << " ("  << termA1 << " , " << termA2 << ") "; //<< std::endl;
		//if not from same ontology, return 0;
		if(_goGraph->getTermOntology(termA1) != _goGraph->getTermOntology(termA2) ||
		   _goGraph->getTermOntology(termC) != _goGraph->getTermOntology(termA1) ||
		   _goGraph->getTermOntology(termC) != _goGraph->getTermOntology(termA2))
		{
			return false;
		}

		if(_icMap[termA1] <= _icMap[termA2]){
			//std::cout << "case 1" << std::endl;
			size_t nPaths = getNumPaths(termA1,termA2);
			//std::cout << "nPaths " << termA1 << " to "  << termA2 << " " << nPaths << std::endl << std::endl;
			size_t nPaths1 = getNumPaths(termA1,termC);
			//std::cout << "nPaths " << termA1 << " to "  << termC << " " << nPaths1 << std::endl << std::endl;
			size_t nPaths2 = getNumPaths(termA2,termC);
			//std::cout << "nPaths " << termA2 << " to "  << termC << " " << nPaths2 << std::endl << std::endl;
			if(nPaths1 >= nPaths*nPaths2){
				//std::cout << "true" << std::endl;
				return true;
			}else{
				//std::cout << "false" << std::endl;
				return false;
			}
			//return nPaths1 > nPaths*nPaths2;
		}else{
			return false;
		}
	}


	//! A method for calculating the number of paths for one term to another.
	/*!
		This method returns the number of paths between two terms
	*/
	inline std::size_t getNumPaths(const std::string &termA, const std::string &termB){
		if(_icMap[termA] > _icMap[termB]){
			return 0;
		}

		return pathCount(termA, termB);
	}


	//! An method for returning the shared information of two terms
	/*!
		This method returns the mean information content disjoint common ancestors
	*/
	inline double sharedInformation(const std::string &termA, const std::string &termB){
		// return 0 for any terms not in the datbase
		if (!_icMap.hasTerm(termA) || !_icMap.hasTerm(termB)){
			return 0.0;
		}
		// return 0 for terms in different ontologies
		if (_goGraph->getTermOntology(termA) != _goGraph->getTermOntology(termB)){
			return 0.0;
		}

		Accumulators::MeanAccumulator meanIC;
		boost::unordered_set<std::string> cda = getCommonDisjointAncestors(termA,termB);
		//std::cout << "size " << cda.size() << std::endl;

		boost::unordered_set<std::string>::iterator iter = cda.begin();
		for(;iter != cda.end(); ++iter){
			//std::cout << *iter << std::endl;
			//std::cout << _icMap[*iter] << std::endl;
			meanIC(_icMap[*iter]);
		}

		return Accumulators::extractMean(meanIC);
	}

	//! An interface method for returning the shared information of a single terms,or information content
	/*!
		This method privdes a mechanism for returing a term's infromation content.
	*/
	inline double sharedInformation(const std::string &term){
		// return 0 for any terms not in the datbase
		if (!_icMap.hasTerm(term)){
			return 0.0;
		}
		return _icMap[term];
	}

	//! An interface method for returning the maximum information content for a term
	/*!
		This method provides the absolute max information content within a corpus for normalization purposes.
	*/
	inline double maxInformationContent(const std::string &term){

		double maxIC;

		//select the correct ontology normalization factor
		GO::Onto ontoType = _goGraph->getTermOntology(term);
		if(ontoType == GO::BP){
			maxIC = -std::log(_icMap.getMinBP());
		}else if(ontoType == GO::MF){
			maxIC = -std::log(_icMap.getMinMF());
		}else{
			maxIC = -std::log(_icMap.getMinCC());
		}

		return maxIC;
	}

	//! An interface method for determining if a term can be found
	/*!
		Determines if the term can be found in the current map.
	*/
	inline bool hasTerm(const std::string &term){
		return _icMap.hasTerm(term);
	}

	//! An interface method for determining if the two terms are of like ontologies.
	/*!
		Determine if two terms are of the same ontology.
	*/
	bool isSameOntology(const std::string &termA, const std::string &termB){
		return _goGraph->getTermOntology(termA) == _goGraph->getTermOntology(termB);
	}


private:

	//! Count paths from B to A
	/*!
		Count paths between B and A
	*/
	std::size_t pathCount(const std::string &termA, const std::string &termB){
		if (_icMap[termA] > _icMap[termB]){
			return 0;
		}

		boost::unordered_set<std::string> ancestors = _goGraph->getAncestorTerms(termB);
		boost::unordered_set<std::string> finished;
		boost::unordered_map<std::string, size_t> pathMap;
		ancestors.insert(termB);
		GoGraph::Graph* g = _goGraph->getGraph();
		GoGraph::GoVertex v = _goGraph->getTermRootVertex(termB);
		visitHelper(v, g, ancestors, finished, pathMap);

		return pathMap[termA];
	}

	//! Recursive helper method that performs the DFS topological sort for path counting
	/*!
		A path counting topological sort recursive method.
	*/
	void visitHelper(const GoGraph::GoVertex &v, GoGraph::Graph* g,
		boost::unordered_set<std::string> &ancestors,
		boost::unordered_set<std::string> &finished,
		boost::unordered_map<std::string, size_t> &pathMap)
	{
		size_t childCount = 0;
		std::string vTerm = (*g)[v].termId;
		//std::cout << "discover vertex " << vTerm << std::endl;

		//examine children and recurse
		GoGraph::InEdgeIterator it, end;
		for (boost::tie(it, end) = boost::in_edges(v, *g); it != end; ++it){
			GoGraph::GoVertex child = boost::source(*it, *g);
			std::string childTerm = (*g)[child].termId;
			if (!SetUtilities::set_contains(ancestors, childTerm)){
				continue;
			}
			//recurse if child is not finished
			if (!SetUtilities::set_contains(finished, childTerm)){
				visitHelper(child, g, ancestors, finished, pathMap);
			}
			++childCount;
		}

		//finish vertex
		finished.insert(vTerm);
		//std::cout << "finish vertex " << vTerm << ", childred " << childCount << std::endl;
		if (childCount == 0){
			pathMap[vTerm] = 1;
		}
		else{
			pathMap[vTerm] = 0;
			for (boost::tie(it, end) = boost::in_edges(v, *g); it != end; ++it){
				GoGraph::GoVertex child = boost::source(*it, *g);
				std::string childTerm = (*g)[child].termId;
				if (!SetUtilities::set_contains(ancestors, childTerm)){
					continue;
				}
				pathMap[vTerm] += pathMap[childTerm];
			}
		}
	}

	//! A private function to create a string key from a pair of terms
	/*!
		Creates a string key our of a pair to use in memorizing path counts
	*/
	std::string keyPair(const std::string &termA, const std::string &termB){
		if (termA.compare(termB) > 0){
			return termB + "_" + termA;
		}
		else{
			return termB + "_" + termA;
		}
	}

	//! A private function to test if the key as been seen already
	/*!
		A private function to test if the key as been seen already.
	*/
	bool hasSeenKey(const std::string &key){
		if (_pathMemory.find(key) != _pathMemory.end()){
			return true;
		}
		else{
			return false;
		}
	}

	GoGraph* _goGraph;
	TermInformationContentMap _icMap;
	boost::unordered_map<std::string, size_t> _pathMemory;
};
#endif
