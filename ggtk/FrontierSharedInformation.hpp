/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FRONTIER_SHARED_INFORMATION
#define FRONTIER_SHARED_INFORMATION

#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/SharedInformationInterface.hpp>
#include <ggtk/SetUtilities.hpp>
#include <ggtk/Accumulators.hpp>
#include <ggtk/GoGraph.hpp>

#include <utility>
#include <algorithm>

#include <boost/unordered_map.hpp>
#include <boost/graph/breadth_first_search.hpp>

/*! \class FrontierSharedInformation
	\brief A class to calculate shared infromation across disjoint common ancestors in linear time.

	This class calculates shared infromation along a semantic frontier between terms.
*/
class FrontierSharedInformation : public SharedInformationInterface{

public:
	
	//! A constructor
	/*!
		Creates the CoutoGraSMSharedInformation class
	*/
	inline FrontierSharedInformation(GoGraph* goGraph,TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
	}


	//! A method for determining the common disjunctive ancestors
	/*!
		This method returns the common disjunctive ancestors for two terms
	*/
	inline boost::unordered_set<std::string> getCommonDisjointAncestors(const std::string &termC1, const std::string &termC2){

		//common disjoint ancestors set
		boost::unordered_set<std::string> cda;

		//commonDisjointAncestors(c,c) = {c}, by definition
		if(termC1.compare(termC2) == 0){
			cda.insert(termC1);
			return cda;
		}

		//std::cout << "Linear GraSm " << std::endl;
		boost::unordered_set<std::string> ancestorsC1 = _goGraph->getAncestorTerms(termC1);
		ancestorsC1.insert(termC1);
		//std::cout << ancestorsC1.size() << std::endl;
		boost::unordered_set<std::string> ancestorsC2 = _goGraph->getAncestorTerms(termC2);
		ancestorsC2.insert(termC2);
		//std::cout << ancestorsC2.size() << std::endl;


		//Couto: Anc = CommonAnc(c1,c2)
		boost::unordered_set<std::string> commonAncestors = SetUtilities::set_intersection(ancestorsC1,ancestorsC2);
		//std::cout << commonAncestors.size() << std::endl;

		//commonDisjointAncestors(c,c) = {c}, by definition
		if(commonAncestors.size() == 1){
			return commonAncestors;
		}

		//std::cout << "CA size " << commonAncestors.size() << std::endl;

		//get the boost graph
		GoGraph::Graph* g = _goGraph->getGraph();

		boost::unordered_set<std::size_t> edgesC1;
		boost::unordered_set<std::size_t> edgesC2;
		GoGraph::EdgeIndexMap eMap = boost::get(boost::edge_index,*g);

		boost::unordered_map<std::string,boost::unordered_set<std::size_t> > termToEdges;
		
		EdgeSetVisitor c1EdgeVisitor(edgesC1,eMap,termToEdges);
		EdgeSetVisitor c2EdgeVisitor(edgesC2,eMap,termToEdges);

		//get edges for c1
		boost::breadth_first_search(*g,_goGraph->getVertexByName(termC1),boost::visitor(c1EdgeVisitor));

		//get edges for c1
		boost::breadth_first_search(*g,_goGraph->getVertexByName(termC2),boost::visitor(c2EdgeVisitor));

		//std::cout << "edges 1 " << edgesC1.size() << std::endl;
		//std::cout << "edges 2 " << edgesC2.size() << std::endl;
		//std::cout << "edge map " << termToEdges.size() << std::endl;

		boost::unordered_set<std::string>::iterator iter;
		for(iter = commonAncestors.begin(); iter != commonAncestors.end(); ++iter){
			std::string term = *iter;

			//std::cout << term << std::endl;
			boost::unordered_set<std::size_t> edges = termToEdges[term];
			//std::cout << edges.size() << std::endl;

			bool isDisj = false;

			//check if the term is attached to a frontier edge
			boost::unordered_set<std::size_t>::iterator iter;
			for(iter = edges.begin(); iter != edges.end(); ++iter){
				std::size_t edgeId = *iter;
				
				if(edgesC1.find(edgeId) == edgesC1.end() 
					|| edgesC2.find(edgeId) == edgesC2.end())
				{
					isDisj = true;
					break;
				}
			}

			//if the term is a disjoint ancestor add it to the set
			if(isDisj){
				cda.insert(term);
			}

		}

		//std::cout << "frontier cda size " << cda.size() << std::endl;
		return cda;
	
	}

	//! An method for returning the shared information of two terms
	/*!
		This method returns the mean information content of the frontier ancestors
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


	//breadth first search to calculate the visited edges
	class EdgeSetVisitor:public boost::default_bfs_visitor{

	public:
		EdgeSetVisitor(boost::unordered_set<std::size_t>& inSet,
			GoGraph::EdgeIndexMap& inMap,
			boost::unordered_map<std::string,boost::unordered_set<std::size_t> >& termToEdges):
		edgeSet(inSet),eMap(inMap),termEdgesMap(termToEdges){}


		template < typename Edge, typename Graph >
		void examine_edge(Edge e, const Graph & g)
		{
			//add the edge to the set of visited edges
			edgeSet.insert(eMap[e]);

			//get the vertex of the target
			typename Graph::vertex_descriptor v = boost::target(e,g);
			std::string term = g[v].termId;
			
			//create a set for the term if none exists
			if(termEdgesMap.find(term) == termEdgesMap.end()){
				termEdgesMap[term] = boost::unordered_set<std::size_t>();
			}
			//add the edge to the map
			termEdgesMap[term].insert(eMap[e]);


		}

		boost::unordered_set<std::size_t>& edgeSet;
		GoGraph::EdgeIndexMap& eMap;
		boost::unordered_map<std::string,boost::unordered_set<std::size_t> >& termEdgesMap;
	};

	GoGraph* _goGraph;
	TermInformationContentMap _icMap;


};
#endif
