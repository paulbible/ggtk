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


class ResnikSimilairtyTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)
        self.sim = ResnikSimilarity(self.graph, self.ic_map)

class CoreMethodsTests(ResnikSimilairtyTestCase):
##########################################################################
# Non-exsitent terms used as input
##########################################################################
    def test_similarity_bad_ids(self):
        """
        Test similarity between two bad terms.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("bad_id","bad_id2"),0)

    def test_similarity_1_bad_1_good_id(self):
        """
        Test similarity between on good term and one bad term.
        """
        self.assertEqual(self.sim.calculateTermSimilarity("GO:0032991","bad_id2"),0)


##########################################################################
# Similarity on CC terms
##########################################################################
    def test_similarity_CC_reflexive_sim(self):
        """
        Test similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0043234", "GO:0043234"), 5.709408519)

    def test_similarity_CC(self):
        """
        Test similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0000791 -> euchromatin
        """
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0043234", "GO:0000791"), 5.442882399)

    def test_similarity_CC_1_good_1_root(self):
        """
        Test similarity between two terms in the CC ontology.
        GO:0005575 -> cellular_component
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0043234", "GO:0005575"), 0.0)

##########################################################################
# Normalized Similarity [0-1], on CC terms
##########################################################################

    def test_normalized_similarity_CC_reflexive_sim(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0043234"), 0.382777400)

    def test_normalized_similarity_CC(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0000791 -> euchromatin
        """
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0000791"), 0.364908618)

    def test_normalized_similarity_CC_1_good_1_root(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0005575 -> cellular_component
        GO:0043234 -> protein complex
        """
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0005575"), 0.0)

##########################################################################
# Similarity in BP
##########################################################################
    def test_similarity_BP(self):
        """
        Test similarity between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0044406 -> adhesion of symbiont to host
        """
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0007155", "GO:0044406"),  7.06391047)

    def test_normalized_similarity_BP(self):
        """
        Test similarity between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0044406 -> adhesion of symbiont to host
        """
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0044406"),  0.457582306)

##########################################################################
# Similarity in MF
##########################################################################
    def test_similarity_MF(self):
        """
        Test similarity between two terms in the MF ontology.
        GO:0051192 -> prosthetic group binding
        GO:0050662 -> coenzyme binding
        """
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0051192", "GO:0050662"), 6.50135459)

    def test_normalized_similarity_MF(self):
        """
        Test normalized similarity between two terms in the MF ontology.
        GO:0051192 -> prosthetic group binding
        GO:0050662 -> coenzyme binding
        """
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0050662"), 0.523675325)



##########################################################################
# Cross Ontology similarity
##########################################################################
    def test_cross_ontology_similarity(self):
        """
        Test similarity between two terms in different ontologies
        GO:0051192 -> prosthetic group binding, MF
        GO:0007155 -> cell adhesion,            BP
        """
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0051192", "GO:0007155"), 0.0)

    def test_cross_ontology_normalized_similarity(self):
        """
        Test normalized similarity between two terms in different ontologies.
        GO:0051192 -> prosthetic group binding, MF
        GO:0007155 -> cell adhesion,            BP
        """
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0007155"), 0.0)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)
























