'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
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

