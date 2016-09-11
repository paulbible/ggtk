'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
"""
_GoGraph class, a more friendly python wrapper for the C++ GoGraph class
This class should not be instatiated by the user. It is returned by GoParser functions
"""
import app_utilities
import go_enums
import go_graph

class GoGraph:
    """
    The GoGraph provides a friendly python interface to the c++ GoGraph Class
    """
    def __init__(self, go_graph_swig_proxy):
        """
        The constructor take a swig proxy object. Should not be used by the user.
        """
        self.graph = go_graph_swig_proxy


    def getRootBP(self):
        """
        Get the term string of the BP root term.
        """
        return go_enums.getRootTermBP()

    def getRootMF(self):
        """
        Get the term string of the MF root term.
        """
        return go_enums.getRootTermMF()

    def getRootCC(self):
        """
        Get the term string of the CC root term.
        """
        return go_enums.getRootTermCC()

    def getNumVertices(self):
        """
        Returns the number of Vertices or terms in the graph
        """
        return self.graph.getNumVertices()

    def getNumEdges(self):
        """
        Returns the number of Edges or relationships in the graph
        """
        return self.graph.getNumEdges()

    def getAllTerms(self):
        """
        Returns all the terms in the graph
        """
        return app_utilities.setToVec(self.graph.getAllTerms())

    def getAllTermsBP(self):
        """
        Returns all BP terms in the graph
        """
        return app_utilities.setToVec(self.graph.getAllTermsBP())

    def getAllTermsMF(self):
        """
        Returns all MF terms in the graph
        """
        return app_utilities.setToVec(self.graph.getAllTermsMF())

    def getAllTermsCC(self):
        """
        Returns all CC terms in the graph
        """
        return app_utilities.setToVec(self.graph.getAllTermsCC())

    def getTermName(self, go_term):
        """
        Gives the human readable name of the term, e.g. 'membrane-enclosed lumen' for GO:0031974
        """
        return self.graph.getTermName(go_term)

    def getTermDescription(self, go_term):
        """
        Gives the human readable long for description of the term. Usually a few sentences.
        """
        return self.graph.getTermDescription(go_term)

    def getTermOntology(self, go_term):
        """
        Gives the human readable, ontology name of the term.
        One of:
        * biological_process
        * molecular_function
        * cellular_component
        * ONTOLOGY_ERROR, if the term is not found
        """
        return go_enums.ontologyToString(self.graph.getTermOntology(go_term))

    def getTermOntologyCode(self, go_term):
        """
        Gives an integer code for the ontology the term.
        One of:
        * 0: biological_process
        * 1: molecular_function
        * 2: cellular_component
        * 3: ONTOLOGY_ERROR, if the term is not found
        """
        return self.graph.getTermOntology(go_term)


    def getAncestorTerms(self, go_term):
        """
        Returns a list of unique ancestors of the given term in no particular order.
        Ancestors are defined as all terms for which the given term is a descendant.
        """
        return app_utilities.setToVec(self.graph.getAncestorTerms(go_term))


    def getDescendantTerms(self, go_term):
        """
        Returns a list of unique descendants of the given term in no particular order.
        Descendants are defined as children of the given or any children of its childrend.
        """
        return app_utilities.setToVec(self.graph.getDescendantTerms(go_term))


    def hasTerm(self, go_term):
        """
        Test if a term exists in the current graph. Returns True if the term can be found and false otherwise.
        """
        return self.graph.hasTerm(go_term)


    def getParentTerms(self, go_term):
        """
        Return a list of the parents of the given term. Parents are the term's immediate ancestors
        """
        return app_utilities.setToVec(self.graph.getParentTerms(go_term))


    def getChildTerms(self, go_term):
        """
        Return a list of the children of the given term. Children are the term's immediate descendants
        """
        return app_utilities.setToVec(self.graph.getChildTerms(go_term))


    def filterForBP(self, go_terms):
        """
        This method will filter a list of terms and return only BP terms
        """
        return app_utilities.setToVec(self.graph.filterSetForBP(go_terms))


    def filterForMF(self, go_terms):
        """
        This method will filter a list of terms and return only MF terms
        """
        return app_utilities.setToVec(self.graph.filterSetForMF(go_terms))


    def filterForCC(self, go_terms):
        """
        This method will filter a list of terms and return only CC terms
        """
        return app_utilities.setToVec(self.graph.filterSetForCC(go_terms))


