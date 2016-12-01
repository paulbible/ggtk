#==============================================================================
#  Copyright (c) 2016 Paul W. Bible
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================
"""
TermSetSimilarity Module
This module defines the term set similarity classes which inherit from the
base BaseTermSetSim python class
"""
import term_sim
import term_set_sim
import go_graph
import annotation_data
from _BaseTermSetSim import BaseTermSetSim


#############################
# Term set similarity classes
#############################
class JaccardSetSimilarity(BaseTermSetSim):
    """
    A class to calculate Jaccard Set Similarity
    Full details available in ggtk/ResnikSimilarity.hpp
    """
    def __init__(self):
        sim_proxy = term_set_sim.JaccardSetSimilarity()
        super(self.__class__,self).__init__(sim_proxy)


class AllPairsAverageSetSimilarity(BaseTermSetSim):
    """
    A class to calculate the all pairs average set Similarity
    Full details available in ggtk/AllPairsAverageSetSimilarity.hpp
    """
    def __init__(self, term_sim):
        self.sim = term_sim
        sim_proxy = term_set_sim.AllPairsAverageSetSimilarity(self.sim.term_sim)
        super(self.__class__,self).__init__(sim_proxy)


class AllPairsMaxSetSimilarity(BaseTermSetSim):
    """
    A class to calculate the all pairs max set Similarity
    Full details available in ggtk/AllPairsMaxSetSimilarity.hpp

    Only the Resnik method of term similarity is recomended for this set similarity measure.
    """
    def __init__(self, term_sim):
        self.sim = term_sim
        sim_proxy = term_set_sim.AllPairsMaxSetSimilarity(self.sim.term_sim)
        super(self.__class__,self).__init__(sim_proxy)


class BestMatchAverageSetSimilarity(BaseTermSetSim):
    """
    A class to calculate the best match average for set Similarity
    Full details available in ggtk/BestMatchAverageSetSimilarity.hpp
    """
    def __init__(self, term_sim):
        self.sim = term_sim
        sim_proxy = term_set_sim.BestMatchAverageSetSimilarity(self.sim.term_sim)
        super(self.__class__,self).__init__(sim_proxy)


class SimUISetSimilarity(BaseTermSetSim):
    """
    A class to calculate Gentleman's SimUI SetSimilarity. This is an extended Jaccard measure.
    Full details available in ggtk/GentlemanSimUISetSimilarity.hpp
    """
    def __init__(self, go_graph):
        self.go_graph = go_graph
        sim_proxy = term_set_sim.GentlemanSimUISetSimilarity(self.go_graph.graph)
        super(self.__class__,self).__init__(sim_proxy)


class SimGICSetSimilarity(BaseTermSetSim):
    """
    A class to calculate Pesquita et al.'s SimGIC SetSimilarity. This Jaccard weighted by IC.
    Full details available in ggtk/PesquitaSimGICSetSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_set_sim.PesquitaSimGICSetSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class SimDICSetSimilarity(BaseTermSetSim):
    """
    A class to calculate Mazandu and Mulder's SimDIC SetSimilarity. Similar in spriti to Lin's measure.
    Full details available in ggtk/MazanduSimDICSetSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_set_sim.MazanduSimDICSetSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class SimUICSetSimilarity(BaseTermSetSim):
    """
    A class to calculate Mazandu and Mulder's SimUIC SetSimilarity.
    Full details available in ggtk/MazanduSimUICSetSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_set_sim.MazanduSimUICSetSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


