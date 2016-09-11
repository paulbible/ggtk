#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSimilarity import ResnikSimilarity
from ggtk.TermSimilarity import TermSimilarityWriter
from ggtk.TermSimilarity import PrecomputedMatrixTermSimilarity


class TermSimWriterResnikCC_TestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)
        self.sim = ResnikSimilarity(self.graph, self.ic_map)

        self.writer = TermSimilarityWriter(self.graph, self.annos)
        self.mat_file = "matrix_files/test_cc_mat.txt"
        self.onto_code = ggtk.go_enums.ontologyStringToCode("cellular_component")
        self.writer.writeSimilarityMatrix(self.sim, self.mat_file, self.onto_code)

        self.mat_sim_cc = PrecomputedMatrixTermSimilarity(self.mat_file)

class CoreMethodsTests(TermSimWriterResnikCC_TestCase):
##########################################################################
# Test types
##########################################################################
    def test_sim_writer_type(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(type(self.writer), TermSimilarityWriter)
        self.assertEqual(type(self.mat_sim_cc), PrecomputedMatrixTermSimilarity)


##########################################################################
# Non-exsitent terms used as input
##########################################################################
    def test_similarity_Resnik_bad_ids(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("bad_id","bad_id2"),0)
        self.assertEqual(self.mat_sim_cc.calculateTermSimilarity("bad_id","bad_id2"),0)

    def test_similarity_Resnik_1_bad_1_good_id(self):
        """
        Test similarity between on good term and one bad term.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("GO:0032991","bad_id2"),0)
        self.assertEqual(self.mat_sim_cc.calculateTermSimilarity("GO:0032991","bad_id2"),0)

##########################################################################
# Normalized Similarity [0-1], on CC terms
##########################################################################
    def test_normalized_similarity_Resnik_CC_reflexive_sim(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0043234 -> protein complex
        """
        rs_val = self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0043234")
        mat_val = self.mat_sim_cc.calculateNormalizedTermSimilarity("GO:0043234", "GO:0043234")
        #assert similarity up to 6 places
        self.assertAlmostEqual(rs_val, mat_val, 6)

    def test_normalized_similarity_Resnik_CC(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0000791 -> euchromatin
        """
        rs_val = self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0000791")
        mat_val = self.mat_sim_cc.calculateNormalizedTermSimilarity("GO:0043234", "GO:0000791")
        #assert similarity up to 6 places
        self.assertAlmostEqual(rs_val, mat_val, 6)

    def test_normalized_similarity_Resnik_CC_1_good_1_root(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0005575 -> cellular_component
        GO:0043234 -> protein complex
        """
        rs_val = self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0005575")
        mat_val = self.mat_sim_cc.calculateNormalizedTermSimilarity("GO:0043234", "GO:0005575")
        #assert similarity up to 6 places
        self.assertAlmostEqual(rs_val, mat_val, 6)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)


