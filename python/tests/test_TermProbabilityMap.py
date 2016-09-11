#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk
from ggtk.TermMaps import TermProbabilityMap

class TermProbabilityMapTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.database = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.term_map = TermProbabilityMap(self.graph, self.database)

class CoreMethodsTests(TermProbabilityMapTestCase):
##################################
# Gene and GO Term count accessors
    def test_get_values_type(self):
        """
        Test that the values returned are in a list form
        """
        vals = self.term_map.values()
        self.assertEqual(type(vals), type(()))

    def test_get_keys_type(self):
        """
        Test that the values returned are in a list form
        """
        key_vals = self.term_map.keys()
        self.assertEqual(type(key_vals), type(()))

    def test_number_of_values(self):
        """
        Test that the number of values return by the probablity map equals the go term number
        """
        num_terms = self.graph.getNumVertices()
        vals = self.term_map.values()
        self.assertEqual(len(vals), num_terms)

    def test_number_of_keys(self):
        """
        Test that the number of values return by the probablity map equals the go term number
        """
        num_terms = self.graph.getNumVertices()
        key_vals = self.term_map.keys()
        self.assertEqual(len(key_vals), num_terms)

    def test_contains_builtin_bad_id(self):
        """
        Test that bracket access with a bad id fails
        """
        self.assertEqual("bad_go_term" in self.term_map, False)

    def test_contains_builtin(self):
        """
        Test that bracket access with a bad id fails
        """
        self.assertEqual("GO:0000015" in self.term_map, True)

    def test_bracket_access_bad_id_key_error(self):
        """
        Test that bracket access with a bad id fails with key error
        """
        with self.assertRaises(KeyError):
            self.term_map["bad_go_term"]

    def test_bracket_access(self):
        """
        Test that bracket access with a bad id fails with key error
        """
        test_prob = 1.33117e-06
        prob = self.term_map["GO:0000015"]
        self.assertAlmostEqual(prob,test_prob)

    def test_root_prob_1_BP(self):
        """
        Test that the informaiton content of the root is 0
        """
        bp_root_prob = self.term_map[ggtk.go_enums.getRootTermBP()]
        self.assertAlmostEqual(bp_root_prob, 1)

    def test_root_prob_1_MF(self):
        """
        Test that the informaiton content of the root is 0
        """
        mf_root_prob = self.term_map[ggtk.go_enums.getRootTermMF()]
        self.assertAlmostEqual(mf_root_prob, 1)

    def test_root_prob_1_CC(self):
        """
        Test that the informaiton content of the root is 0
        """
        cc_root_prob = self.term_map[ggtk.go_enums.getRootTermCC()]
        self.assertAlmostEqual(cc_root_prob, 1)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)

