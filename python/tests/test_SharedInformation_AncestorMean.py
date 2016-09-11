#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSimilarity import AncestorMeanSharedInformation


class AncestorMeanSharedInformationTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)
        self.si = AncestorMeanSharedInformation(self.graph, self.ic_map)

class CoreMethodsTests(AncestorMeanSharedInformationTestCase):
##########################################################################
# Non-exsitent terms used as input
##########################################################################
    def test_shared_information_bad_ids(self):
        """
        Test shared information between two bad terms.
        """
        self.assertEqual(self.si.sharedInformation("bad_id","bad_id2"),0)

    def test_shared_information_1_bad_1_good_id(self):
        """
        Test shared information between on good term and one bad term.
        """
        self.assertEqual(self.si.sharedInformation("GO:0032991","bad_id2"),0)

##########################################################################
# Deep term
##########################################################################
    def test_shared_information_deep_terms_BP(self):
        """
        Test shared information between two terms in the BP ontology that are relatively deep.
        Terms that are deep should result in distinct values of SI for most measures.
        GO:0000413 -> protein peptidyl-prolyl isomerization
        GO:0043966 -> histone H3 acetylation
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0000413", "GO:0043966"), 4.147530971)

##########################################################################
# Shared Information on CC terms
##########################################################################
    def test_shared_information_CC_reflexive_sim(self):
        """
        Test shared information between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0043234", "GO:0043234"), 3.717040601)

    def test_shared_information_CC(self):
        """
        Test shared information between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0000791 -> euchromatin
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0043234", "GO:0000791"), 2.72114892)

    def test_shared_information_CC_1_good_1_root(self):
        """
        Test shared information between two terms in the CC ontology.
        GO:0005575 -> cellular_component
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0043234", "GO:0005575"), 0.0)

    def test_shared_information_single_term_CC(self):
        """
        Test shared information for a single term in the CC ontology.
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0043234"), self.ic_map["GO:0043234"])

    def test_max_shared_information_CC(self):
        """
        Test the maximum information for a term in the CC ontology.
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.si.maxInformationContent("GO:0043234"), 14.9151563)

##########################################################################
# Shared Information in BP
##########################################################################
    def test_shared_information_BP(self):
        """
        Test shared information between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0044406 -> adhesion of symbiont to host
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0007155", "GO:0044406"), 3.538884429)

    def test_shared_information_single_term_BP(self):
        """
        Test shared information for a single term in the BP ontology.
        GO:0007155 -> cell adhesion
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0007155"), self.ic_map["GO:0007155"])

    def test_max_shared_information_BP(self):
        """
        Test the maximum information for a term in the BP ontology.
        GO:0007155 -> cell adhesion
        """
        self.assertAlmostEqual(self.si.maxInformationContent("GO:0007155"), 15.21457972)

##########################################################################
# Shared Information in MF
##########################################################################
    def test_shared_information_MF(self):
        """
        Test shared information between two terms in the MF ontology.
        GO:0051192 -> prosthetic group binding
        GO:0050662 -> coenzyme binding
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0051192", "GO:0050662"), 2.28338684)

    def test_shared_information_single_term_MF(self):
        """
        Test normalized shared information for a single term in the MF ontology.
        GO:0051192 -> prosthetic group binding
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0051192"), self.ic_map["GO:0051192"])

    def test_max_shared_information_MF(self):
        """
        Test the maximum information for a  term in the MF ontology.
        GO:0051192 -> prosthetic group binding
        """
        self.assertAlmostEqual(self.si.maxInformationContent("GO:0051192"), 12.41485760)

##########################################################################
# Cross Ontology Shared Information
##########################################################################
    def test_cross_ontology_shared_information(self):
        """
        Test shared information between two terms in different ontologies
        GO:0051192 -> prosthetic group binding, MF
        GO:0007155 -> cell adhesion,            BP
        """
        self.assertAlmostEqual(self.si.sharedInformation("GO:0051192", "GO:0007155"), 0.0)

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)

















