'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
"""
TermSimilarity Module
This module defines the term similarity classes which inherit from the 
base BaseTermSim python class
"""
import term_sim
import go_graph
import annotation_data
from _BaseTermSim import BaseTermSim
from _BaseSharedInformation import BaseSharedInformation


#########################
# Term similarity classes
#########################
class ResnikSimilarity(BaseTermSim):
    """
    A class to calculate Resnik Similarity
    Full details available in ggtk/ResnikSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_sim.ResnikSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class LinSimilarity(BaseTermSim):
    """
    A class to calculate Lin Similarity
    Full details available in ggtk/LinSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_sim.LinSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class JiangConrathSimilarity(BaseTermSim):
    """
    A class to calculate Jiang Conrath Similarity
    Full details available in ggtk/JiangConrathSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_sim.JiangConrathSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class PekarStaabSimilarity(BaseTermSim):
    """
    A class to calculate Pekar Staab similarity
    Full details available in ggtk/PekarStaabSimilarity.hpp
    """
    def __init__(self, go_graph, depth_map):
        self.go_graph = go_graph
        self.depth_map = depth_map
        sim_proxy = term_sim.PekarStaabSimilarity(self.go_graph.graph, self.depth_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class RelevanceSimilarity(BaseTermSim):
    """
    A class to calculate Relevance Similarity
    Full details available in ggtk/RelevanceSimilarity.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map = ic_map
        sim_proxy = term_sim.RelevanceSimilarity(self.go_graph.graph, self.ic_map.term_map)
        super(self.__class__,self).__init__(sim_proxy)


class PrecomputedMatrixTermSimilarity(BaseTermSim):
    """
    A class to calculate similarity from a precomputed matrix
    Full details available in ggtk/PrecomputedMatrixTermSimilarity.hpp
    Designed to read an !Ontology Specific! similarity matrix,
    written by a TermSimilarityWriter.
    """
    def __init__(self, matrix_file):
        sim_proxy = term_sim.PrecomputedMatrixTermSimilarity(matrix_file)
        super(self.__class__,self).__init__(sim_proxy)

#################################
# Modular term similarity classes
#################################
class ModularJiangConrath(BaseTermSim):
    """
    A class to calculate Jiang Conrath Similarity using a
    shared infromation calculator (other than MCIA)
    Full details available in ggtk/ModularJiangConrath.hpp
    """
    def __init__(self, si_type):
        self.si = si_type
        sim_proxy = term_sim.ModularJiangConrath(self.si.term_si)
        super(self.__class__,self).__init__(sim_proxy)


class ModularLin(BaseTermSim):
    """
    A class to calculate Lin Similarity using a
    shared infromation calculator (other than MCIA)
    Full details available in ggtk/ModularLin.hpp
    """
    def __init__(self, si_type):
        self.si = si_type
        sim_proxy = term_sim.ModularLin(self.si.term_si)
        super(self.__class__,self).__init__(sim_proxy)


class ModularResnik(BaseTermSim):
    """
    A class to calculate Resnik Similarity using a
    shared infromation calculator (other than MCIA)
    Full details available in ggtk/ModularResnik.hpp
    """
    def __init__(self, si_type):
        self.si = si_type
        sim_proxy = term_sim.ModularResnik(self.si.term_si)
        super(self.__class__,self).__init__(sim_proxy)


#########################################
# TermSimilarityWriter
class TermSimilarityWriter(object):
    """
    TermSimilarityWrite calculates and writes a term matrix
    for use with the PrecomputedMatrixTermSimilarity
    Full details are available in ggtk/TermSimilarityWriter.hpp
    """
    def __init__(self, go_graph, anno_data):
        self.go_graph = go_graph
        self.annos    = anno_data
        self.writer = term_sim.TermSimilarityWriter(self.go_graph.graph, self.annos.data)

    def writeSimilarityMatrix(self, term_sim, file_name, ontology):
        self.writer.writeSimilarityMatrix(term_sim.term_sim, file_name, ontology)

    def writeSimilarityMatrixBP(self, term_sim, file_name):
        self.writer.writeSimilarityMatrixBP(term_sim.term_sim, file_name)

    def writeSimilarityMatrixMF(self, term_sim, file_name):
        self.writer.writeSimilarityMatrixMF(term_sim.term_sim, file_name)

    def writeSimilarityMatrixCC(self, term_sim, file_name):
        self.writer.writeSimilarityMatrixCC(term_sim.term_sim, file_name)


#########################################
# SharedInformation methods
class AncestorMeanSharedInformation(BaseSharedInformation):
    """
    A class for calculating the shared information between two terms
    by the mean information content of common ancestors method.
    Full details are available in ggtk/AncestorMeanSharedInformation.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map   = ic_map
        si_proxy = term_sim.AncestorMeanSharedInformation(self.go_graph.graph,  self.ic_map.term_map)
        super(self.__class__,self).__init__(si_proxy)


class CoutoGraSMSharedInformation(BaseSharedInformation):
    """
    A class for calculating the shared information between two terms
    by Couto et al.'s GraSM method.
    Full details are available in ggtk/CoutoGraSMSharedInformation.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map   = ic_map
        si_proxy = term_sim.CoutoGraSMSharedInformation(self.go_graph.graph,  self.ic_map.term_map)
        super(self.__class__,self).__init__(si_proxy)


class CoutoGraSMAdjustedSharedInformation(BaseSharedInformation):
    """
    A class for calculating the shared information between two terms
    by an adjusted version of Couto et al.'s GraSM method.
    Full details are available in ggtk/CoutoGraSMAdjustedSharedInformation.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map   = ic_map
        si_proxy = term_sim.CoutoGraSMAdjustedSharedInformation(self.go_graph.graph,  self.ic_map.term_map)
        super(self.__class__,self).__init__(si_proxy)


class ExclusivelyInheritedSharedInformation(BaseSharedInformation):
    """
    A class for calculating the shared information between two terms
    by the exclusively inherited shared information method.
    Full details are available in ggtk/ExclusivelyInheritedSharedInformation.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map   = ic_map
        si_proxy = term_sim.ExclusivelyInheritedSharedInformation(self.go_graph.graph,  self.ic_map.term_map)
        super(self.__class__,self).__init__(si_proxy)


class FrontierSharedInformation(BaseSharedInformation):
    """
    A class for calculating the shared information between two terms
    by the semantic frontier method.
    Full details are available in ggtk/FrontierSharedInformation.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map   = ic_map
        si_proxy = term_sim.FrontierSharedInformation(self.go_graph.graph,  self.ic_map.term_map)
        super(self.__class__,self).__init__(si_proxy)


class MICASharedInformation(BaseSharedInformation):
    """
    A class for calculating the shared information between two terms
    by the Most Informative Common Ancestor (MICA) method.
    Full details are available in ggtk/MICASharedInformation.hpp
    """
    def __init__(self, go_graph, ic_map):
        self.go_graph = go_graph
        self.ic_map   = ic_map
        si_proxy = term_sim.MICASharedInformation(self.go_graph.graph,  self.ic_map.term_map)
        super(self.__class__,self).__init__(si_proxy)



