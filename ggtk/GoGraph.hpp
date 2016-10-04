/*=============================================================================
    Copyright (c) 2016 Paul W. Bible

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GO_GRAPH
#define GO_GRAPH

#include <ggtk/GoEnums.hpp>
#include <boost/unordered_set.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/subgraph.hpp>
#include <boost/graph/adjacency_iterator.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/strong_components.hpp>
#include <boost/graph/reverse_graph.hpp>
#include <boost/tuple/tuple.hpp>

/*! \class GoGraph
	\brief This class holds the Gene Ontology directed acyclic graph

	This class holds the Gene Ontology as a boost graph. It provides the graph data,
	 as well as other strucutres which make working with the graph easier.

*/
class GoGraph{

public:

	//! A Vertex Property object
    /*!
		This struct represent the data needed by each vertex. Boost provides
		 constant time access to these members by querying them using the vertex
		 and graph objects (graphVar[vertex].termId ... etc.).
	*/
	struct VertexProps{
		/*!
			The term id of the go term, the GO accession, GO:########.
		*/
		std::string termId;

		//std::size_t onto_type;
		/*!
			The ontology of the GO term, BP, MF, CC
		*/
		GO::Onto ontology;

		/*!
			Desctructor
		*/
		~VertexProps(){}
	};

	//! An Edge Property object
    /*!
		This struct represent the data needed by each edge. Boost provides
		 constant time access to these members by querying them using the vertex
		 and graph objects (graphVar[edge].relType).
	*/
	struct EdgeProps{
		//std::size_t index;
		/*!
			The type of relationship between the terms, is_a, part_of etc.
		*/
		GO::Relationship relType;

		/*!
		Desctructor
		*/
		~EdgeProps(){}
	};

	//! A Graph type representing Go
    /*!
		This typedef defines a graph type used as the basic go graph. This typedef
		 takes VertexProps and EdgeProps as templete arguments.
	*/
	typedef boost::adjacency_list<boost::vecS, boost::vecS,
			boost::bidirectionalS,
			boost::property< boost::vertex_index_t, size_t, VertexProps>, 
			boost::property< boost::edge_index_t, size_t, EdgeProps> > Graph_t;


	//! The main Graph type representing Go
    /*!
		This typedef defines the main type as a subgraph of Graph_t. This allows the 
		 the graph to be divided into subgraphs if needed. Virtually not differnece but
		 can cause problems with some boost constructors such as random graph generators.
	*/
	typedef boost::subgraph<Graph_t> Graph;

	////////////////////////////
	//  Vertex and Edge typedefs
	////////////////////////////
	//! A vertex object
    /*!
		A typedef of the boost vertex_descriptor. Saves typing by using GoVertex.
	*/
	typedef boost::graph_traits<Graph>::vertex_descriptor GoVertex;

	//! An edge object
    /*!
		A typedef of the boost edge_descriptor. Saves typing by using GoEdge.
	*/
	typedef boost::graph_traits<Graph>::edge_descriptor GoEdge;


	/////////////////////////////
	//  Vertex and Edge iterators
	/////////////////////////////
	//! A vertex iterator
    /*!
		A typedef of the boost vertex_iterator. Saves typing by using GoVertexIterator.
	*/
	typedef boost::graph_traits<Graph>::vertex_iterator GoVertexIterator;

	//! An in edge iterator
    /*!
		A typedef of the boost in_edge_iterator. Saves typing by using InEdgeIterator.
	*/
	typedef boost::graph_traits<Graph>::in_edge_iterator InEdgeIterator;

	//! An out edge iterator
    /*!
		A typedef of the boost out_edge_iterator. Saves typing by using OutEdgeIterator.
	*/
	typedef boost::graph_traits<Graph>::out_edge_iterator OutEdgeIterator;


	//////////////////////////////////
	//  Index maps for edge and vertex
	//////////////////////////////////
	//! A vertex to index map
    /*!
		A typedef of the boost property_map. Saves typing by using VertexIndexMap.
	*/
	typedef boost::property_map<Graph, boost::vertex_index_t >::type VertexIndexMap;

	//! An edge to index map
    /*!
		A typedef of the boost property_map. Saves typing by using EdgeIndexMap.
	*/
	typedef boost::property_map<Graph, boost::edge_index_t >::type EdgeIndexMap;



	//! A destructor
	/*!
	Destroying the graph calls clear on all the containers. Other data should be
	destroyed when leaving scope.
	*/
	inline ~GoGraph(){
		_nameToIndex.clear();
		_names.clear();
		_descriptions.clear();
	}

	//! Method to insert terms into the graph
	/*!
		This method takes a go term, description, and ontology information (MF,BP,CC).
		 The method will check if the term already exists in the graph then add the vertex
		 or update the meta data accordingly. The parser can call this method without having
		 to consider if terms have already been added or not.
	*/
	inline void insertTerm(const std::string &termId, const std::string &name, const std::string &description, const std::string &ontology){

		//term already exists, update its information,
		if(_nameToIndex.find(termId) != _nameToIndex.end()){
			std::size_t index = _nameToIndex[termId];

			//Term needs to be updated
			//If name is "name", this is a stub, no need to update
			if(name.compare("name") != 0){
				_names.at(index) = name;
				_descriptions.at(index) = description;
				GoVertex V = boost::vertex(index,_goGraph);
				_goGraph[V].ontology = GO::ontologyStringToCode(ontology);

			}

		}else{
			//term is new and must be added
			//map termId to index
			_nameToIndex[termId] = boost::num_vertices(_goGraph);

			//add the vertex to the graph, get back a reference to the vertex, V
			GoVertex V = boost::add_vertex(_goGraph);

			//set the termId
			_goGraph[V].termId = termId;
			//set the ontology
			_goGraph[V].ontology = GO::ontologyStringToCode(ontology);

			//add name to list
			_names.push_back(name);
			//add description to list
			_descriptions.push_back(description);
		}
	}


	//! Method to insert relationship edges into the graph
	/*!
		This method takes a parent term, child term, and relationshp type as arguments.
		 The method will insert the edge into the graph, setting the relationship type based
		 on the data provided.
	*/
	inline void insertRelationship(const std::string &termParent, const std::string &termChild, const std::string &relationship){

		//get the vertices by name, they should already exit in the graph 
		GoVertex v = boost::vertex(_nameToIndex[termParent],_goGraph);
		GoVertex u = boost::vertex(_nameToIndex[termChild],_goGraph);

		//get the relationship type as its enum value
		GO::Relationship relType = GO::relationshipStringToCode(relationship);

		//add the edge to the graph, get a reference to the edge
		std::pair<GoEdge,bool> myPair = boost::add_edge(v,u,_goGraph);

		//set that edge's internal value for relationship type
		GoEdge e = myPair.first;
		_goGraph[e].relType = relType;
	}


	//! Helper method to get number of vertices
	/*!
		This method calls boost num_vertices on the go graph
	*/
	inline std::size_t getNumVertices(){
		return boost::num_vertices(_goGraph);
	}

	//! Helper method to get number of edges
	/*!
		This method calls boost num_edges on the go graph
	*/
	inline std::size_t getNumEdges(){
		return boost::num_edges(_goGraph);
	}


	//! A method to initialize internal index maps
	/*!
		This method sets the private map variables by call calling boost get on the property maps.
	*/
	inline void initMaps(){
		_vMap = boost::get(boost::vertex_index,_goGraph);
		_eMap = boost::get(boost::edge_index,_goGraph);
	}//end method initMaps



	//! A method to return the boost graph
	/*!
		This method is needed to return the graph to other boost algorithms. As stated by boost,
		 subclasses of adjacency_list are not recommended.
		 http://www.boost.org/doc/libs/1_54_0/libs/graph/doc/graph_concepts.html
	*/
	inline Graph* getGraph(){
		return &_goGraph;
	}


	//! A helper method to test term existence
	/*!
		Tests the map for existence of the term.
	*/
	inline bool hasTerm(const std::string &term){
		return _nameToIndex.find(term) != _nameToIndex.end();
	}


	//! A helper method to return the index of the term
	/*!
		This method returns the index of the given term.
	*/
	inline size_t getTermIndex(const std::string &term){
		return _nameToIndex[term];
	}

	//! A helper method to return the string id based on the index
	/*!
		This method returns the term's string id using its index.
		  Used mainly for testing.
	*/
	inline std::string getTermStringIdByIndex(std::size_t index){
		GoVertex v = getVertexByIndex(index);
		return _goGraph[v].termId;
	}

	//! A helper method to return the string name based on the index
	/*!
		This method returns the term's string name using its index.
		  Used mainly for testing.
	*/
	inline std::string getTermNameByIndex(std::size_t index){
		return _names.at(index);
	}

	//! A helper method to return the string name based on the go term
	/*!
		This method returns the term's string name using the go term.
	*/
	inline std::string getTermName(std::string term){
		if (hasTerm(term)){
			size_t index = getTermIndex(term);
			return _names.at(index);
		}else{
			return "";
		}
	}

	//! A helper method to return the string description based on the index
	/*!
		This method returns the term's description string using its index.
		  Used mainly for testing.
	*/
	inline std::string getTermDescriptionByIndex(std::size_t index){
		return _descriptions.at(index);
	}

	//! A helper method to return the string description based on the go term
	/*!
		This method returns the term's description string using the go term.
	*/
	inline std::string getTermDescription(std::string term){
		if (hasTerm(term)){
			size_t index = getTermIndex(term);
			return _descriptions.at(index);
		}else{
			return "";
		}
		
	}


	//! A helper method to return the root of the graph
	/*!
		This method returns the root vertex or first root vertex of a graph.
	*/
	inline GoVertex getRoot(){

		//Create vertex iterators
		GoVertexIterator vi,vend;

		//creat a vertex variable
		GoVertex root;

		for(boost::tie(vi,vend) = boost::vertices(_goGraph); vi != vend; ++vi){
			//if it has no out edges it is a root
			if(boost::out_degree(*vi,_goGraph) == 0){
				//set the variable and break the loop
				root = *vi;
				break;
			}
		}
		//return the root
		return root;
	}

	//! A helper method to return the ontology of a term by term string
	/*!
		This method returns the term's ontoogy taking a string term as an argument
	*/
	inline GO::Onto getTermOntology(const std::string &term){
		if (!hasTerm(term)){
			return GO::ONTO_ERROR;
		}else{
			return _goGraph[getTermIndex(term)].ontology;
		}
	}

	//! A helper method to return the ontology of a term by index
	/*!
		This method returns the term's ontoogy taking an index as an argument
	*/
	inline GO::Onto getTermOntologyByIndex(std::size_t index){
		GoVertex v = getVertexByIndex(index);
		return _goGraph[v].ontology;
	}

	//! A helper method to return the ontology of a term by GoVertex
	/*!
		This method returns the term's ontoogy taking GoVertex as an argument
	*/
	inline GO::Onto getTermOntologyByVertex(GoVertex vertex){
		return _goGraph[vertex].ontology;
	}

	//! A helper method to return the index of a GoVertex
	/*!
		This method returns the index of a GoVertex
	*/
	inline std::size_t getVertexIndex(GoVertex vertex){
		return _vMap[vertex];
	}

	//! A helper method to return the GoVertex for the given index
	/*!
		This method returns the GoVertex based on the given index
	*/
	inline GoVertex getVertexByIndex(std::size_t index){
		return boost::vertex(index,_goGraph);
	}

	//! A helper method to return the GoVertex for the given term
	/*!
		This method returns the GoVertex based on the given term
	*/
	inline GoVertex getVertexByName(const std::string &term){
		return boost::vertex(getTermIndex(term),_goGraph);
	}

	//! A helper method to get the desendant terms for a given term.
	/*!
		This method takes a term and returns a list of desendant terms.
	*/
	inline boost::unordered_set<std::string> getDescendantTerms(const std::string &term){
		//return empty set, if term is not found
		if (!hasTerm(term)){
			return boost::unordered_set<std::string>();
		}

		//get the correct index from the term string
		std::size_t vIndex = _nameToIndex[term];

		//get the vertex from the term index
		GoVertex vertex = getVertexByIndex(vIndex);

		//create a map set
		boost::unordered_map<std::size_t,bool> desendantMap;

		//call the recursive helper method.
		getDescendantTermsHelper(vertex, desendantMap);

		//create output container
		boost::unordered_set<std::string> desendantTerms;

		//create an iterator for the map
		boost::unordered_map<std::size_t,bool>::iterator mapIter;
		for(mapIter = desendantMap.begin(); mapIter != desendantMap.end(); ++mapIter){
			std::string term = getTermStringIdByIndex(mapIter->first);
			desendantTerms.insert(term);
		}
		return desendantTerms;	
	}



	//! A helper method to get the ancestor terms for a given term.
	/*!
		This method takes a term and returns a list of ancestor terms.
	*/
	inline boost::unordered_set<std::string> getAncestorTerms(const std::string &term){
		//return empty set, if term is not found
		if (!hasTerm(term)){
			return boost::unordered_set<std::string>();
		}

		//get the correct index from the term string
		std::size_t vIndex = _nameToIndex[term];
		GoVertex vertex = getVertexByIndex(vIndex);

		//create a map set
		boost::unordered_map<std::size_t,bool> ancestorMap;

		//call the recursive helper method.
		getAncestorTermsHelper(vertex, ancestorMap);

		//create output container
		boost::unordered_set<std::string> ancestorTerms;

		//create an iterator for the map
		boost::unordered_map<std::size_t,bool>::iterator mapIter;
		for(mapIter = ancestorMap.begin(); mapIter != ancestorMap.end(); ++mapIter){
			std::string term = getTermStringIdByIndex(mapIter->first);
			ancestorTerms.insert(term);
		}
		return ancestorTerms;
	}

	//! A helper method to get the parent terms for a given term.
	/*!
		This method takes a term and returns a list of parent terms (immediate ancestors).
	*/
	inline boost::unordered_set<std::string> getParentTerms(const std::string &term){
		//return empty set, if term is not found
		if (!hasTerm(term)){
			return boost::unordered_set<std::string>();
		}
		else{
			GoVertex vertex = getVertexByName(term);
			boost::unordered_set<std::string> parents;

			OutEdgeIterator ei, end;
			for (boost::tie(ei, end) = boost::out_edges(vertex, _goGraph); ei != end; ++ei){
				GoVertex v = boost::target(*ei, _goGraph);
				parents.insert(_goGraph[v].termId);
			}
			return parents;
		}
	}

	//! A helper method to get the child terms for a given term.
	/*!
		This method takes a term and returns a list of child terms.
	*/
	inline boost::unordered_set<std::string> getChildTerms(const std::string &term){
		//return empty set, if term is not found
		if (!hasTerm(term)){
			return boost::unordered_set<std::string>();
		}
		else{
			GoVertex vertex = getVertexByName(term);
			boost::unordered_set<std::string> children;

			InEdgeIterator ei, end;
			for (boost::tie(ei, end) = boost::in_edges(vertex, _goGraph); ei != end; ++ei){
				GoVertex v = boost::source(*ei, _goGraph);
				children.insert(_goGraph[v].termId);
			}
			return children;
		}
	}


	//! A helper method to retrieve all terms in the GoGraph
	/*!
		This method returns a set of term strings
	*/
	inline boost::unordered_set<std::string> getAllTerms(){
		//create a collection to return
		boost::unordered_set<std::string> outSet;
		for (std::size_t i = 0; i < getNumVertices(); ++i){
			GoVertex v = getVertexByIndex(i);
			outSet.insert(_goGraph[v].termId);
		}
		return outSet;
	}

	//! A helper method to retrieve all terms in the GoGraph belonging to the BP ontology
	/*!
		This method returns a set of BP terms in the graph
	*/
	inline boost::unordered_set<std::string> getAllTermsBP(){
		boost::unordered_set<std::string> outSet = getDescendantTerms(GO::getRootTermBP());
		outSet.insert(GO::getRootTermBP());
		return outSet;
	}

	//! A helper method to retrieve all terms in the GoGraph belonging to the MF ontology
	/*!
		This method returns a set of MF terms in the graph
	*/
	inline boost::unordered_set<std::string> getAllTermsMF(){
		boost::unordered_set<std::string> outSet = getDescendantTerms(GO::getRootTermMF());
		outSet.insert(GO::getRootTermMF());
		return outSet;
	}

	//! A helper method to retrieve all terms in the GoGraph belonging to the CC ontology
	/*!
		This method returns a set of CC terms in the graph
	*/
	inline boost::unordered_set<std::string> getAllTermsCC(){
		boost::unordered_set<std::string> outSet = getDescendantTerms(GO::getRootTermCC());
		outSet.insert(GO::getRootTermCC());
		return outSet;
	}

	//! A helper method to filter out all terms not belonging to a particular ontology
	/*!
		This method returns a filtered set of ontology terms matching the given ontology
	*/
	inline boost::unordered_set<std::string> filterSetForOntology(const boost::unordered_set<std::string> &inSet, GO::Onto onto){
		//create a collection to return
		boost::unordered_set<std::string> outSet;

		//iterate over the collection
		boost::unordered_set<std::string>::iterator iter;
		for(iter = inSet.begin(); iter != inSet.end(); ++iter){
			std::string term = *iter;

			if(getTermOntology(term) == onto){
				outSet.insert(term);
			}
		}
		return outSet;
	}

	//! A helper method to filter out all terms not belonging to a particular ontology from a vector
	/*!
		This method returns a filtered set of ontology terms matching the given ontology
	*/
	inline boost::unordered_set<std::string> filterSetForOntology(const std::vector<std::string> &inSet, GO::Onto onto){
		//create a collection to return
		boost::unordered_set<std::string> outSet;

		//iterate over the collection
		std::vector<std::string>::const_iterator iter;
		for (iter = inSet.begin(); iter != inSet.end(); ++iter){
			std::string term = *iter;

			if (getTermOntology(term) == onto){
				outSet.insert(term);
			}
		}
		return outSet;
	}

	//! Get the root term for a particular term
	/*!
		Return the root node for a term's ontology
	*/
	std::string getTermRoot(const std::string &term){
		GO::Onto ontology = getTermOntology(term);
		switch (ontology){
			case GO::BP:
				return GO::getRootTermBP();
			case GO::MF:
				return GO::getRootTermMF();
			case GO::CC:
				return GO::getRootTermCC();
			default:
				return "";
		}
	}

	//! Get the root vertex for a particular term
	/*!
		Get the root vertex for a particular term
	*/
	GoVertex getTermRootVertex(const std::string &term){
		return getVertexByName(getTermRoot(term));
	}


	//! A helper method to retrun only BP terms from a vector
	/*!
		This method returns a filtered set containing only BP terms
	*/
	inline boost::unordered_set<std::string> filterSetForBP(const std::vector<std::string> &inSet){
		return filterSetForOntology(inSet, GO::BP);
	}

	//! A helper method to retrun only BP terms from a set
	/*!
		This method returns a filtered set containing only BP terms
	*/
	inline boost::unordered_set<std::string> filterSetForBP(const boost::unordered_set<std::string> &inSet){
		return filterSetForOntology(inSet, GO::BP);
	}

	//! A helper method to retrun only MF terms from a vector
	/*!
		This method returns a filtered set containing only MF terms
	*/
	inline boost::unordered_set<std::string> filterSetForMF(const std::vector<std::string> &inSet){
		return filterSetForOntology(inSet, GO::MF);
	}

	//! A helper method to retrun only MF terms from a set
	/*!
		This method returns a filtered set containing only MF terms
	*/
	inline boost::unordered_set<std::string> filterSetForMF(const boost::unordered_set<std::string> &inSet){
		return filterSetForOntology(inSet, GO::MF);
	}

	//! A helper method to retrun only CC terms from a vector
	/*!
		This method returns a filtered set containing only CC terms
	*/
	inline boost::unordered_set<std::string> filterSetForCC(const std::vector<std::string> &inSet){
		return filterSetForOntology(inSet, GO::CC);
	}

	//! A helper method to retrun only CC terms from a set
	/*!
		This method returns a filtered set containing only CC terms
	*/
	inline boost::unordered_set<std::string> filterSetForCC(const boost::unordered_set<std::string> &inSet){
		return filterSetForOntology(inSet, GO::CC);
	}


	//!	A helper method to return only the terms of the give ontology.
	/*!
		Returns only those terms used that occur for the given ontology.
	*/
	inline boost::unordered_set<std::string> getOntologyTerms(GO::Onto ontology){
		//Use only terms in the annotation database, this will save on space and computation time.
		std::string rootId;
		switch (ontology){
			case GO::BP:
				rootId = GO::getRootTermBP();
				break;
			case GO::MF:
				rootId = GO::getRootTermMF();
				break;
			case GO::CC:
				rootId = GO::getRootTermCC();
				break;
			case GO::ECODE_ERROR:
			default:
				rootId = "";
				break;
		}
		//All Ontology terms are descendants of the root.
		boost::unordered_set<std::string> ontologyTerms = getDescendantTerms(rootId);
		// Add the root.
		ontologyTerms.insert(rootId);
		return ontologyTerms;
	}


	//! A method to return the induced subgraph of a given term, ancestor graph
	/*!
		This method returns a subgraph of the graph induced by traversing the ancestors of 
		  the given vertex.
	*/
	inline Graph* getInducedSubgraph2(const std::string &termId){
		
		Graph* subgraph = &_goGraph.create_subgraph();

		SubgraphBFSVisitor subgraphVisitor(subgraph);
		boost::breadth_first_search(_goGraph,getVertexByName(termId),boost::visitor(subgraphVisitor));
		return subgraph;
	}

	//! A method to return the induced subgraph of a given term, ancestor graph
	/*!
		This method returns a subgraph of the graph induced by traversing the ancestors of 
		  the given vertex.
	*/
	inline Graph* getInducedSubgraph(const std::string &termId){
		
		Graph* subgraph = &_goGraph.create_subgraph();
		boost::add_vertex(getVertexByName(termId), *subgraph);

		boost::unordered_set<std::string> ancestors = getAncestorTerms(termId);
		boost::unordered_set<std::string>::iterator iter;
		for(iter = ancestors.begin(); iter != ancestors.end(); ++iter){
			boost::add_vertex(getVertexByName(*iter),*subgraph);
		}

		return subgraph;
	}

	//! A method to calculate the number of connected components of the graph
	/*!
		This method calculates the number of connected components in the graph.
		  This is used to check if the GO graph conatains only the 3 sub-ontologies.
	*/
	inline std::size_t getNumComponents(){
		//Define undirected graph type
		typedef boost::adjacency_list < boost::vecS, boost::vecS, boost::undirectedS> undirected_graph_t;
		undirected_graph_t undirected_g;

		//Make an undirected copy of the graph
		for (std::size_t i = 0; i < getNumVertices(); ++i){
			//add graph vertices
			boost::add_vertex(undirected_g);
		}
		boost::graph_traits<Graph>::edge_iterator iter, end;
		boost::tie(iter, end) = boost::edges(_goGraph);
		for (; iter != end; ++iter){
			GoVertex s = boost::source(*iter, _goGraph);
			GoVertex t = boost::target(*iter, _goGraph);
			//add edges, undirected
			boost::add_edge(_vMap[s], _vMap[t], undirected_g);
		}

		//calculate the connected components
		std::vector<std::size_t> componentAssignment(getNumVertices());
		return boost::connected_components(boost::make_reverse_graph(undirected_g), &componentAssignment[0]);
	}

private:
	//! Private graph member
	/*!
		The go graph defined as subgraph<Graph_t>.
	*/
	Graph _goGraph;

	/////////////////////////////
	//  maps from vertex to index
	/////////////////////////////
	//! Private vertex map
	/*!
		This maps a vertex object (GoVertex) to its index.
	*/
	VertexIndexMap _vMap;

	//! Private edge map
	/*!
		This maps an edge object (GoEdge) to its index.
	*/
	EdgeIndexMap   _eMap;

	//! A map from term name to index
	/*!
		This maps a term string to its index. Boost unordered_map has O(1) find like a hash map.
	*/
	boost::unordered_map<std::string,std::size_t> _nameToIndex;


	/*
		list of go short names and long descriptions (termId --> index --> name/description)
	*/

	//! A list of term names, titles
	/*!
		A list of go names, the title of the term such as "positive regulation of cell cycle".
	*/
	std::vector<std::string> _names;

	//! A list of term descriptions.
	/*!
		A list of go term descriptions. Long explanation and detailed description of the term.
	*/
	std::vector<std::string> _descriptions;



	//! A private recursive helper method to get the desendant terms for a given term.
	/*!
		This method is wrapped by a public method. It traverses the children of a node,
		  populating the map with node indices of desendant terms.
	*/
	inline void getDescendantTermsHelper(GoVertex vertex, boost::unordered_map<std::size_t,bool> &desendantMap){
		//create edge iterators
		InEdgeIterator ei,end;
		//loop over each edge
		for(boost::tie(ei,end) = boost::in_edges(vertex, _goGraph); ei != end; ++ei){
			//get the soruce vertex ( specific --is_a--> general )
			GoVertex v = boost::source(*ei,_goGraph);
			//add the vertex index to the desendant map, addressed in the method call
			//  redundancies are handled by the map
			desendantMap[_vMap[v]] = true;
			//make the recursive call
			getDescendantTermsHelper(v, desendantMap);
		}
	}

	//! A private recursive helper method to get the ancestor terms for a given term.
	/*!
		This method is wrapped by a public method. It traverses the parents of a node,
		  populating the map with node indices of ancestor terms.
	*/
	inline void getAncestorTermsHelper(GoVertex vertex, boost::unordered_map<std::size_t,bool> &ancestorMap){

		//create edge iterators
		OutEdgeIterator ei,end;

		//loop over each edge
		for(boost::tie(ei,end) = boost::out_edges(vertex,_goGraph); ei != end; ++ei){
			//get the soruce vertex ( specific --is_a--> general )
			GoVertex v = boost::target(*ei,_goGraph);

			//add the vertex index to the desendant map, addressed in the method call
			//  redundancies are handled by the map
			ancestorMap[_vMap[v]] = true;

			//make the recursive call
			getAncestorTermsHelper(v,ancestorMap);
		}
	}


	//! A Breath first search visitor that creates the induced subgraph of a graph
	/*!
		This class extends breadth first search and adds a vertex to a subgraph
		  of the graph being visited.
	*/
	class SubgraphBFSVisitor:public boost::default_bfs_visitor{

	public:
		SubgraphBFSVisitor(GoGraph::Graph* sub):subgraph(sub){}

		template < typename Vertex, typename Graph >
		void discover_vertex(Vertex u, const Graph & g)
		{
			boost::add_vertex(u,*subgraph);
		}

		GoGraph::Graph* subgraph;
	};

};
#endif
