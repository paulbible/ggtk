/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef TERM_DEPTH_MAP
#define TERM_DEPTH_MAP

#include <ggtk/GoGraph.hpp>
#include <ggtk/AnnotationData.hpp>

#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/reverse_graph.hpp>

#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics.hpp>
#include <boost/accumulators/statistics/min.hpp>
#include <boost/accumulators/statistics/max.hpp>

/*! \class TermDepthMap
	\brief A class to calculate the depth of a GO term in the ontology.

	This class provides a map that returns the depth of a GO term. This method
	 is used in graph and edge based similarity methods to calculate a node's depth
*/
class TermDepthMap{
public:
	//! A parameterized constructor
	/*!
		This constructor takes pointers to GoGraph and AnnotationData objects.
		  Only the parameterized construtor is allowed to ensure these objects are
		  created with valid parameters.
	*/
	inline TermDepthMap(GoGraph* graph){

		//Initialize an annotation list the size of verticies in go, each value is 0
		//_depths = std::vector<std::size_t>(graph->getNumVertices(),0);
		_depths = std::vector<double>(graph->getNumVertices(), 0);

		//get the (first) root of the ontology.
		//GoGraph::GoVertex root = graph->getRoot();
		//TESTING
		//std::cout << root << std::endl;
		//std::cout << graph->getTermStringIdByIndex(root) << std::endl;

		//get the boost graph from the GoGraph object. Must be done to utilize boost algorithms
		GoGraph::Graph* g = graph->getGraph();

		//wrap _depth with a vertex map
		GoGraph::VertexIndexMap vMap = boost::get(boost::vertex_index,*g);

		/* // Temparary fix until I can get SWIG to recognize std::size_t
		boost::iterator_property_map< std::vector<std::size_t>::iterator,
			                          GoGraph::VertexIndexMap > 
									  d_map(_depths.begin(), vMap);
		*/
		boost::iterator_property_map< std::vector<double>::iterator,
			GoGraph::VertexIndexMap >
			d_map(_depths.begin(), vMap);
		
		//call the boost depth first search using our custom visitor
		// revering the graph is necessary otherwise the root vertex would have no edges.
		//boost::depth_first_search(boost::make_reverse_graph(*g),boost::visitor(vis).root_vertex(root));
		GoGraph::GoVertex bpRoot = graph->getVertexByName(GO::getRootTermBP());
		GoGraph::GoVertex mfRoot = graph->getVertexByName(GO::getRootTermMF());
		GoGraph::GoVertex ccRoot = graph->getVertexByName(GO::getRootTermCC());

		//Start at bproot, record depths
		// must reverse graph due to edge relationship direction
		boost::breadth_first_search(boost::make_reverse_graph(*g), bpRoot,
			boost::visitor(boost::make_bfs_visitor(
			  boost::record_distances(d_map, boost::on_tree_edge())
			  )));

		//Start at bproot, record depths
		// must reverse graph due to edge relationship direction
		boost::breadth_first_search(boost::make_reverse_graph(*g), mfRoot,
			boost::visitor(boost::make_bfs_visitor(
			  boost::record_distances(d_map, boost::on_tree_edge())
			  )));

		//Start at bproot, record depths
		// must reverse graph due to edge relationship direction
		boost::breadth_first_search(boost::make_reverse_graph(*g), ccRoot,
			boost::visitor(boost::make_bfs_visitor(
			  boost::record_distances(d_map, boost::on_tree_edge())
			  )));

		//initialize the term to index map
		_nameToIndex = boost::unordered_map<std::string,std::size_t>(boost::num_vertices(*g));

		// Vertex Iterators
		GoGraph::GoVertexIterator vi,vend;
		for(boost::tie(vi,vend) = boost::vertices(*g); vi != vend; ++vi){
			GoGraph::GoVertex v = *vi;
			_nameToIndex[graph->getTermStringIdByIndex(vMap[v])] = vMap[v];
			//std::cout << vMap[v] << " " << _depths.at(vMap[v]) << " " << graph->getTermNameByIndex(vMap[v]) << std::endl;
			//std::cin.get();
		}
	}//end constructor


	//! A default constructor
	/*!
		This constructor initialized the storage structures. Should not be used.
	*/
	inline TermDepthMap(){
		//creat empty containers
		_nameToIndex = boost::unordered_map<std::string,std::size_t>();
		//_depths = std::vector<std::size_t>();
		_depths = std::vector<double>();
	}

	//! A default desctructor
	/*!
		This desctructor clears the containters
	*/
	inline ~TermDepthMap(){
		//empty containers
		_nameToIndex.clear();
		_depths.clear();
	}

	//! Accessor for probablities vector
	/*!
		Get the vector of values
	*/
	inline std::vector<double> getValues(){
	//inline std::vector<std::size_t> getValues(){
		return _depths;
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
	inline bool hasTerm(std::string testTerm){
		return _nameToIndex.find(testTerm) != _nameToIndex.end();
	}

	//! Overloaded [] bracket operator to mimic Map
	/*!
		This defines a bracket operator to access the data inside of the map.
		  This is done to mimic the behavior of the map class
	*/
	inline double operator[](std::string termId){
	//inline size_t& operator[](std::string termId){
		//get index
		std::size_t index = _nameToIndex[termId];
		//return the depth
		return _depths.at(index);
	}

	//! Mapping function to return the value mapped by key
	/*!
		Get the value mapped by the given key. A specified function for the [] operator
	*/
	inline double getValue(std::string termId){
		//get index
		std::size_t index = _nameToIndex[termId];
		//return the depth
		return _depths.at(index);
	}
	
protected:
	//! A private map that returns the index of a term.
	/*!
		This map takes string term ids and returns the index for annotation count access.
	*/
	boost::unordered_map<std::string,std::size_t> _nameToIndex;

	//! A private list of term depths
	/*!
		This vector of doubles holds the depth for each term
	*/
	std::vector<double> _depths;		//temparary fix until I can get SWIG to recognize std::size_t
	//std::vector<std::size_t> _depths;
};
#endif
