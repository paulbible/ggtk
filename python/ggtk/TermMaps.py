'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
"""
TermMaps Module
This module orgnaizes the different term maps that inherit from _BaseTermMap
"""
import term_maps
from _BaseTermMap import BaseTermMap


class TermDepthMap(BaseTermMap):
    """
    TermDepthMap class
    This class provides a mapping to a term's depth in the ontology.
    Root terms have a depth of 0.
    """
    def __init__(self, go_graph):
        self.go_graph = go_graph
        dm_proxy = term_maps.TermDepthMap(self.go_graph.graph)
        super(self.__class__,self).__init__(dm_proxy)


class TermProbabilityMap(BaseTermMap):
    """
    TermProbabilityMap class
    Creates a probability map given the annotation database and a GO Graph
    """
    def __init__(self, go_graph, anno_data):
        self.go_graph = go_graph
        self.anno_data = anno_data
        tpm_proxy = term_maps.TermProbabilityMap(self.go_graph.graph, self.anno_data.data)
        super(self.__class__,self).__init__(tpm_proxy)


class TermInformationContentMap(BaseTermMap):
    """
    TermInformationContentMap class
    Creates an information content map given the annotation database and a GO Graph
    """
    def __init__(self, go_graph, anno_data):
        self.go_graph = go_graph
        self.anno_data = anno_data
        icm_proxy = term_maps.TermInformationContentMap(self.go_graph.graph, self.anno_data.data)
        super(self.__class__,self).__init__(icm_proxy)


