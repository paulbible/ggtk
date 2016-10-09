#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSimilarity import LinSimilarity
from ggtk.TermSimilarity import TermSimilarityWriter
from ggtk.TermSimilarity import PrecomputedMatrixTermSimilarity


class TermSimWriterLinMF_TestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)
        self.sim = LinSimilarity(self.graph, self.ic_map)

        self.writer = TermSimilarityWriter(self.graph, self.annos)
        self.mat_file = "matrix_files/test_mf_mat.txt"
        #self.onto_code = ggtk.go_enums.ontologyStringToCode("molecular_function")
        self.writer.writeSimilarityMatrixMF(self.sim, self.mat_file)

        self.mat_sim_mf = PrecomputedMatrixTermSimilarity(self.mat_file)

class CoreMethodsTests(TermSimWriterLinMF_TestCase):
##########################################################################
# Test types
##########################################################################
    def test_sim_writer_type(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(type(self.writer), TermSimilarityWriter)
        self.assertEqual(type(self.mat_sim_mf), PrecomputedMatrixTermSimilarity)

##########################################################################
# Test PrecomputedMatrixTermSimilarity raises error on bad filename
##########################################################################
    def test_precomputed_matrix_bad_file(self):
        """
        Test similarity between two bad terms.
        """
        with self.assertRaises(IOError):
            p = PrecomputedMatrixTermSimilarity('fake_file.txt')

##########################################################################
# Non-exsitent terms used as input
##########################################################################
    def test_similarity_Lin_bad_ids(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("bad_id","bad_id2"),0)
        self.assertEqual(self.mat_sim_mf.calculateTermSimilarity("bad_id","bad_id2"),0)

    def test_similarity_Lin_1_bad_1_good_id(self):
        """
        Test similarity between on good term and one bad term.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("GO:0032991","bad_id2"),0)
        self.assertEqual(self.mat_sim_mf.calculateTermSimilarity("GO:0032991","bad_id2"),0)

##########################################################################
# Normalized Similarity [0-1], on MF terms
##########################################################################
    def test_normalized_similarity_Lin_MF_reflexive_sim(self):
        """
        Test similarity between two terms in the MF ontology.
        GO:0050662 -> coenzyme binding
        GO:0050662 -> coenzyme binding
        """
        rs_val = self.sim.calculateNormalizedTermSimilarity("GO:0050662", "GO:0050662")
        mat_val = self.mat_sim_mf.calculateNormalizedTermSimilarity("GO:0050662", "GO:0050662")
        #assert similarity up to 6 places
        self.assertAlmostEqual(rs_val, mat_val, 6)

    def test_normalized_similarity_Lin_MF(self):
        """
        Test similarity between two terms in the MF ontology.
        GO:0030170 -> pyridoxal phosphate binding
        GO:0050662 -> coenzyme binding
        """
        rs_val = self.sim.calculateNormalizedTermSimilarity("GO:0030170", "GO:0050662")
        mat_val = self.mat_sim_mf.calculateNormalizedTermSimilarity("GO:0030170", "GO:0050662")
        #assert similarity up to 6 places
        self.assertAlmostEqual(rs_val, mat_val, 6)

    def test_normalized_similarity_Lin_MF_1_good_1_root(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0051192 -> prosthetic group binding
        GO:0003674 -> molecular_function
        """
        rs_val = self.sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0003674")
        mat_val = self.mat_sim_mf.calculateNormalizedTermSimilarity("GO:0051192", "GO:0003674")
        #assert similarity up to 6 places
        self.assertAlmostEqual(rs_val, mat_val, 6)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)


