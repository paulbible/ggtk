#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSimilarity import JiangConrathSimilarity
from ggtk.TermSetSimilarity import SimDICSetSimilarity


class SimDICSetSimilarityTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)

        # self.term_sim = JiangConrathSimilarity(self.graph, self.ic_map)

        self.set_sim = SimDICSetSimilarity(self.graph, self.ic_map)

class CoreMethodsTests(SimDICSetSimilarityTestCase):
    ####################
    # Basic test
    ####################
    def test_set_similarity_empty_sets(self):
        """
        Test similarity between two empty sets
        """
        g1_terms = ()
        g2_terms = ()
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g2_terms), 0.0)

    def test_set_similarity_1_empty_1_good(self):
        """
        Test similarity between two BP term sets.
        """
        g1_terms = self.annos.getGoTermsForGeneBP("A0A0B4J269", self.graph)
        g2_terms = ()
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g2_terms), 0.0)

    ####################
    # Biological process
    ####################
    def test_set_similarity_reflexive_BP(self):
        """
        Test similarity between a set of BP terms and itself.
        """
        g1_terms = self.annos.getGoTermsForGeneBP("A0A0B4J269", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g1_terms), 1.0)

    def test_set_similarity_reflexive_slice_BP(self):
        """
        Test similarity between a set of BP terms and a subset of itself
        """
        g1_terms = self.annos.getGoTermsForGeneBP("A0A0B4J269", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g1_terms[1:]), 0.639792938)

    def test_set_similarity_BP(self):
        """
        Test similarity between two BP term sets.
        """
        g1_terms = self.annos.getGoTermsForGeneBP("A0A0B4J269", self.graph)
        g2_terms = self.annos.getGoTermsForGeneBP("A1A4S6", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g2_terms), 0.448659504)

    ####################
    # Molecular function
    ####################
    def test_set_similarity_reflexive_MF(self):
        """
        Test similarity between a set of MF terms and itself.
        """
        g1_terms = self.annos.getGoTermsForGeneMF("A0A0J9YVX5", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g1_terms), 1.0)

    def test_set_similarity_reflexive_slice_MF(self):
        """
        Test similarity between a set of MF terms and a subset of itself
        """
        g1_terms = self.annos.getGoTermsForGeneMF("A0A0J9YVX5", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g1_terms[1:]), 0.94979587)

    def test_set_similarity_MF(self):
        """
        Test similarity between two MF term sets.
        """
        g1_terms = self.annos.getGoTermsForGeneMF("A0A0J9YVX5", self.graph)
        g2_terms = self.annos.getGoTermsForGeneMF("O00159", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g2_terms), 0.51465157)

    ####################
    # Cellular component
    ####################
    def test_set_similarity_reflexive_CC(self):
        """
        Test similarity between a set of CC terms and itself.
        """
        g1_terms = self.annos.getGoTermsForGeneCC("A0AVI4", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g1_terms), 1.0)

    def test_set_similarity_reflexive_slice_CC(self):
        """
        Test similarity between a set of CC terms and a subset of itself
        """
        g1_terms = self.annos.getGoTermsForGeneCC("A0AVI4", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g1_terms[1:]), 0.933680311)

    def test_set_similarity_CC(self):
        """
        Test similarity between two CC term sets.
        """
        g1_terms = self.annos.getGoTermsForGeneCC("A0AVI4", self.graph)
        g2_terms = self.annos.getGoTermsForGeneCC("A0PK00", self.graph)
        self.assertAlmostEqual(self.set_sim.calculateSimilarity(g1_terms,g2_terms), 0.528753124)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)
