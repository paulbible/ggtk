/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef TERM_PROBABILITY_MAP
#define TERM_PROBABILITY_MAP

#include <cmath>
#include <string>

#include <ggtk/GoGraph.hpp>
#include <ggtk/AnnotationData.hpp>
#include <ggtk/Accumulators.hpp>

#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/reverse_graph.hpp>


/*! \class TermProbabilityMap
	\brief A class to calculate the probability of a GO term.

	This class provides a map that returns the probability of GO term. This
	  class is used by Information Content methods to determine the prior probability of
	  a term give an instance of AnnotationData.
*/
class TermProbabilityMap{
public:

	//! A parameterized constructor
	/*!
		This constructor takes pointers to GoGraph and AnnotationData objects.
		  Only the parameterized construtor is allowed to ensure these objects are
		  created with valid parameters.
	*/
	inline TermProbabilityMap(GoGraph* graph, AnnotationData* annoData){

		//set the default minimum probablity policy for normalization
		_isSingleAnnoMin = false;

		//Initialize an annotation list the size of verticies in go, each value is 0
		_probabilities = std::vector<double>(graph->getNumVertices(),0);

		//get the (first) root of the ontology.
		GoGraph::GoVertex root = graph->getRoot();

		//TESTING
		//std::cout << root << std::endl;
		//std::cout << graph->getTermStringIdByIndex(root) << std::endl;

		//a variable for the cummulative annotaions of the graph
		std::vector<std::size_t> annotationCounts(graph->getNumVertices(),0);

		//create the visitor abject
		dfs_cumulative_annotations_visitor vis(graph ,annoData, &annotationCounts,&_nameToIndex);

		//get the boost graph from the GoGraph object. Must be done to utilize boost algorithms
		GoGraph::Graph* g = graph->getGraph();

		//call the boost depth first search using our custom visitor
		// revering the graph is necessary otherwise the root vertex would have no edges.
		boost::depth_first_search(boost::make_reverse_graph(*g), boost::visitor(vis).root_vertex(root));
		 
		// Traverse the vertices to find the roots for each ontology
		Accumulators::SimpleAccumulator minMaxBP;
		Accumulators::SimpleAccumulator minMaxMF;
		Accumulators::SimpleAccumulator minMaxCC;

		// Vertex Iterators
		GoGraph::GoVertexIterator vi,vend;
		for(boost::tie(vi,vend) = boost::vertices(*g); vi != vend; ++vi){
			GoGraph::GoVertex v = *vi;
			std::size_t index = graph->getVertexIndex(v);

			double counts = (double)annotationCounts.at(index);
			if(counts == 0.0){
				continue;
			}

			//switch on ontology, find the max for each set
			switch(graph->getTermOntologyByIndex(index)){
				case GO::BP:
					minMaxBP(counts);
					break;

				case GO::MF:
					minMaxMF(counts);
					break;
			
				case GO::CC:
					minMaxCC(counts);
					break;

				case GO::ONTO_ERROR:
					break;
			}
		}//end for, vertex iterator

		//calculate single annotation minimum normalization factors
		_bp_normalization_min_1anno = 1.0/Accumulators::extractMax(minMaxBP);
		_mf_normalization_min_1anno = 1.0/Accumulators::extractMax(minMaxMF);
		_cc_normalization_min_1anno = 1.0/Accumulators::extractMax(minMaxCC);

		//calculate minimum annotation minimum normalization factors
		_bp_normalization_min_minAnno = Accumulators::extractMin(minMaxBP)/Accumulators::extractMax(minMaxBP);
		_mf_normalization_min_minAnno = Accumulators::extractMin(minMaxMF)/Accumulators::extractMax(minMaxMF);
		_cc_normalization_min_minAnno = Accumulators::extractMin(minMaxCC)/Accumulators::extractMax(minMaxCC);

		//Traverse the cummulative annotation vector, convert to probability, add to probability vector
		for(boost::tie(vi,vend) = boost::vertices(*g); vi != vend; ++vi){
			GoGraph::GoVertex v = *vi;
			std::size_t index = graph->getVertexIndex(v);
			switch (graph->getTermOntologyByIndex(index)){
				case GO::BP:
					_probabilities.at(index) = annotationCounts.at(index)/Accumulators::extractMax(minMaxBP);
					break;
				case GO::MF:
					_probabilities.at(index) = annotationCounts.at(index)/Accumulators::extractMax(minMaxMF);
					break;
				case GO::CC:
					_probabilities.at(index) = annotationCounts.at(index)/Accumulators::extractMax(minMaxCC);
					break;
				case GO::ONTO_ERROR:
					break;
			}
		}
	}//end constructor logic


	//! A default constructor
	/*!
		This constructor initialized the storage structures. Should not be used.
	*/
	inline TermProbabilityMap(){
		//set the default minimum probablity policy for normalization
		_isSingleAnnoMin = true;
		//create empty containers
		_nameToIndex = boost::unordered_map<std::string,std::size_t>();
		_probabilities = std::vector<double>();
	}

	//! A default desctructor
	/*!
		This desctructor clears the containters
	*/
	inline ~TermProbabilityMap(){
		//empty containers
		_nameToIndex.clear();
		_probabilities.clear();
	}

	//! Accessor for probablities vector
	/*!
		Get the vector of values
	*/
	inline std::vector<double> getValues(){
		return _probabilities;
	}

	//! Function to return all the keys in the map
	/*!
		Returns all valid keys in the map.
	*/
	inline std::vector<std::string> getKeys(){
		std::vector<std::string> keys;
		boost::unordered_map<std::string, std::size_t>::iterator it;
		for (it = _nameToIndex.begin(); it != _nameToIndex.end(); ++it){
			keys.push_back(it->first);
		}
		return keys;
	}

	//! Method to test if the id exists in the map
	/*!
		Return true the id is found, false if not
	*/
	inline bool hasTerm(const std::string &testTerm){
		return _nameToIndex.find(testTerm) != _nameToIndex.end();
	}

	//! Return a default value for a term that does not exist.
	/*!
		A value to return if the term is not found (does not exist in the map).
		Returns probability 1 or certanty. This may not be the ideal behavior.
	*/
	inline virtual double badIdValue(){
		return 1.0;
	}

	//! Overloaded [] bracket operator to mimic Map
	/*!
	This defines a bracket operator to access the data inside of the map.
	This is done to mimic the behavior of the map class
	*/
	inline double operator[](std::string termId){
		if (!hasTerm(termId)){
			return badIdValue();
		}
		std::size_t index = _nameToIndex[termId];
		return _probabilities.at(index);
	}

	//! Mapping function to return the value mapped by key
	/*!
	Get the value mapped by the given key. A specified function for the [] operator
	*/
	inline double getValue(std::string termId){
		if (!hasTerm(termId)){
			return badIdValue();
		}
		std::size_t index = _nameToIndex[termId];
		return _probabilities.at(index);
	}

	//-------------------------------------------------------------------

	//! Get the specific minimum probability for BP
	/*!
		This function returns the minimum probablity for the bp ontology
	*/
	inline double getMinBP(){
		return _isSingleAnnoMin ? _bp_normalization_min_1anno : _bp_normalization_min_minAnno;
	}


	//! Get the specific minimum probability for MF
	/*!
		This function returns the minimum probablity for the mf ontology
	*/
	inline double getMinMF(){
		return _isSingleAnnoMin ? _mf_normalization_min_1anno : _mf_normalization_min_minAnno;
	}

	
	//! Get the specific minimum probability for CC
	/*!
		This function returns the minimum probablity for the cc ontology
	*/
	inline double getMinCC(){
		return _isSingleAnnoMin ? _cc_normalization_min_1anno : _cc_normalization_min_minAnno;
	}

	//! Depth first search boost visitor
	/*!
		This defines a class used by TermProabilityMap to calculate the cumulative annotations
		 of a term based on the true path rule. Basically this class is passed to a boost
		 Depth first search algorithm to add the number of a child's annotaitons to the parent.
	*/
	class dfs_cumulative_annotations_visitor: public boost::default_dfs_visitor{

	  public:
		//! A parameterized constructor passing parameters to the boost default_dfs_visitor
		dfs_cumulative_annotations_visitor(GoGraph* inGraph,AnnotationData* inData,
				std::vector<std::size_t>* annotations,boost::unordered_map<std::string,std::size_t>* nameToIndex)
			:goGraph(inGraph),annoData(inData),annoList(annotations),nameIndexMap(nameToIndex){}

		//! The extended method of the default_dfs_visitor, finish_vertex
		/*!
			This method is called during a depth first search traversal of a graph and called
			  when the visitor finished or leaves a node. This is the last time the algorithm touches
			  the node.

			  Here we calculate the number of cummulative annotations for a term (node) by adding the current
			    term's annotations to the annotations of the term's children.
		*/
		template < typename Vertex, typename Graph >
		void finish_vertex(Vertex u, const Graph & g) 
		{

			//get the vertx index
			std::size_t uIndex = get(boost::vertex_index,g)[u];

			//get the termId string
			std::string termId = goGraph->getTermStringIdByIndex(uIndex);

			//use the AnnotationData object to get the actual number of annotations
			std::size_t currentTermAnnos = annoData->getNumAnnotationsForGoTerm(termId);

			//std::cout << termId << std::endl;

			//initialized this map for the TermProbablilityMap, can initialize it for free here
			nameIndexMap->insert(std::make_pair(termId,uIndex));

			//Iterate over the children of the term to add the child annotations
			typename boost::graph_traits< Graph >::out_edge_iterator ei, e_end;
			for(tie(ei, e_end) = boost::out_edges(u, g); ei != e_end; ++ei){

				Vertex v = boost::target(*ei, g);
				std::size_t vIndex = get(boost::vertex_index,g)[v];

				std::string childTermId = goGraph->getTermStringIdByIndex(vIndex);

				//std::cout << "child " << childTermId << std::endl;

				currentTermAnnos += annoList->at(vIndex);

			}//end for, each child

			annoList->at(uIndex) = currentTermAnnos;

			//std::cout << uIndex << std::endl;
			//std::cout << termId << std::endl;
			//std::cout << annoList->at(uIndex) << std::endl;
			//std::cin.get();

		}//end method, finish_vertex

		//! The go graph object
		GoGraph* goGraph;

		//! An AnnotationData object for accessing annotations
		AnnotationData* annoData;

		//! The annotaiton list to hold the and query the cummulative annotations
		std::vector<std::size_t>* annoList;

		//! A map from name To index, initialized in this visitor.
		boost::unordered_map<std::string,std::size_t>* nameIndexMap;
	};//end class, DFS visitor class



protected:
	//! A private map that returns the index of a term.
	/*!
		This map takes string term ids and returns the index for annotation count access.
	*/
	boost::unordered_map<std::string,std::size_t> _nameToIndex;

	//! A private list of term probabilities
	/*!
		This vector of doubles holds the prior probability for each term
	*/
	std::vector<double> _probabilities;

	//! A flag designating the minimum policy
	/*!
		This flag will be true and return true is single annotation probability is used, false otherwise.
	*/
	bool _isSingleAnnoMin;

	//! Normalization factor for calculating normalized simialrites Biological Process
	/*!
		Normalization factor representing the minimum probability using a single annotation
		  devided by the cumulative annotations.
	*/
	double _bp_normalization_min_1anno;

	//! Normalization factor for calculating normalized simialrites for Biological Process
	/*!
		Normalization factor representing the minimum probability using the number of
		  annotations of the least probable term devided by the cumulative annotations.
	*/
	double _bp_normalization_min_minAnno;

	//! Normalization factor for calculating normalized simialrites Molecular Function
	/*!
		Normalization factor representing the minimum probability using a single annotation
		  devided by the cumulative annotations.
	*/
	double _mf_normalization_min_1anno;

	//! Normalization factor for calculating normalized simialrites for Molecular Function
	/*!
		Normalization factor representing the minimum probability using the number of
		  annotations of the least probable term devided by the cumulative annotations.
	*/
	double _mf_normalization_min_minAnno;

	//! Normalization factor for calculating normalized simialrites Cellular Component
	/*!
		Normalization factor representing the minimum probability using a single annotation
		  devided by the cumulative annotations.
	*/
	double _cc_normalization_min_1anno;

	//! Normalization factor for calculating normalized simialrites for Cellular Component
	/*!
		Normalization factor representing the minimum probability using the number of
		  annotations of the least probable term devided by the cumulative annotations.
	*/
	double _cc_normalization_min_minAnno;

};
#endif
