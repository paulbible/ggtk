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
from ggtk.TermSimilarity import TermSimilarityWriter
from ggtk.TermSimilarity import PrecomputedMatrixTermSimilarity

@unittest.skip("Takes over 25min to complete.")
class TermSimWriterJC_BP_TestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)
        self.sim = JiangConrathSimilarity(self.graph, self.ic_map)

        self.writer = TermSimilarityWriter(self.graph, self.annos)
        self.mat_file = "matrix_files/test_bp_mat.txt"
        #self.onto_code = ggtk.go_enums.ontologyStringToCode("molecular_function")
        self.writer.writeSimilarityMatrixBP(self.sim, self.mat_file)

        self.mat_sim = PrecomputedMatrixTermSimilarity(self.mat_file)

class CoreMethodsTests(TermSimWriterJC_BP_TestCase):
##########################################################################
# Test types
##########################################################################
    def test_sim_writer_type(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(type(self.writer), TermSimilarityWriter)
        self.assertEqual(type(self.mat_sim), PrecomputedMatrixTermSimilarity)


##########################################################################
# Non-exsitent terms used as input
##########################################################################
    def test_similarity_JiangConrath_bad_ids(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("bad_id","bad_id2"),0)
        self.assertEqual(self.mat_sim.calculateTermSimilarity("bad_id","bad_id2"),0)

    def test_similarity_JiangConrath_1_bad_1_good_id(self):
        """
        Test similarity between on good term and one bad term.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("GO:0007155","bad_id2"),0)
        self.assertEqual(self.mat_sim.calculateTermSimilarity("GO:0007155","bad_id2"),0)

##########################################################################
# Normalized Similarity [0-1], on MF terms
##########################################################################
    def test_normalized_similarity_JiangConrath_BP_reflexive_sim(self):
        """
        Test similarity between two terms in the MF ontology.
        GO:0007155 -> cell adhesion
        GO:0007155 -> cell adhesion
        """
        val = self.sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0007155")
        mat_val = self.mat_sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0007155")
        #assert similarity up to 6 places
        self.assertAlmostEqual(val, mat_val, 6)

    def test_normalized_similarity_JiangConrath_BP(self):
        """
        Test similarity between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0044406 -> adhesion of symbiont to host
        """
        val = self.sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0044406")
        mat_val = self.mat_sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0044406")
        #assert similarity up to 6 places
        self.assertAlmostEqual(val, mat_val, 6)

    def test_normalized_similarity_JiangConrath_BP_1_good_1_root(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0051192 -> prosthetic group binding
        GO:0003674 -> molecular_function
        """
        """
        Test similarity between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0008150 -> biological_process
        """
        val = self.sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0008150")
        mat_val = self.mat_sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0008150")
        #assert similarity up to 6 places
        self.assertAlmostEqual(val, mat_val, 6)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)


