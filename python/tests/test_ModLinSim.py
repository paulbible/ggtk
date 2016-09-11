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
from ggtk.TermSimilarity import ModularLin
from ggtk.TermSimilarity import MICASharedInformation


class JiangConrathSimilarityTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.annos = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")
        self.ic_map = TermInformationContentMap(self.graph, self.annos)
        self.sim = LinSimilarity(self.graph, self.ic_map)

        self.si = MICASharedInformation(self.graph, self.ic_map)
        self.mod_sim = ModularLin(self.si)

class CoreMethodsTests(JiangConrathSimilarityTestCase):
##########################################################################
# Non-exsitent terms used as input
##########################################################################
    def test_similarity_bad_ids(self):
        """
        Test similarity between two bad terms.
        """
        mod_val = self.mod_sim.calculateTermSimilarity("bad_id","bad_id2")
        self.assertEqual(self.sim.calculateTermSimilarity("bad_id","bad_id2"),mod_val)

    def test_similarity_1_bad_1_good_id(self):
        """
        Test similarity between on good term and one bad term.
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0032991","bad_id2")
        self.assertEqual(self.sim.calculateTermSimilarity("GO:0032991","bad_id2"), mod_val)


##########################################################################
# Similarity on CC terms
##########################################################################
    def test_similarity_CC_reflexive_sim(self):
        """
        Test similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0043234 -> protein complex
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0043234", "GO:0043234")
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0043234", "GO:0043234"), mod_val)

    def test_similarity_CC(self):
        """
        Test similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0000791 -> euchromatin
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0043234", "GO:0000791")
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0043234", "GO:0000791"), mod_val)

    def test_similarity_CC_1_good_1_root(self):
        """
        Test similarity between two terms in the CC ontology.
        GO:0005575 -> cellular_component
        GO:0043234 -> protein complex

        GO:0005587 -> deeper term: collagen type IV trimer
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0043234", "GO:0005575")
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0043234", "GO:0005575"), mod_val)


##########################################################################
# Normalized Similarity [0-1], on CC terms
##########################################################################

    def test_normalized_similarity_CC_reflexive_sim(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0043234 -> protein complex
        """
        mod_val = self.mod_sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0043234")
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0043234"), mod_val)

    def test_normalized_similarity_CC(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0043234 -> protein complex
        GO:0000791 -> euchromatin
        """ 
        mod_val = self.mod_sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0000791")
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0000791"), mod_val)

    def test_normalized_similarity_CC_1_good_1_root(self):
        """
        Test normalized similarity between two terms in the CC ontology.
        GO:0005575 -> cellular_component
        GO:0043234 -> protein complex
        """
        mod_val = self.mod_sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0005575")
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0043234", "GO:0005575"), mod_val)

##########################################################################
# Similarity in BP
##########################################################################
    def test_similarity_BP(self):
        """
        Test similarity between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0044406 -> adhesion of symbiont to host
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0007155", "GO:0044406")
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0007155", "GO:0044406"), mod_val)

    def test_normalized_similarity_BP(self):
        """
        Test similarity between two terms in the BP ontology.
        GO:0007155 -> cell adhesion
        GO:0044406 -> adhesion of symbiont to host
        """
        mod_val = self.mod_sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0044406")
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0007155", "GO:0044406"), mod_val)

##########################################################################
# Similarity in MF
##########################################################################
    def test_similarity_MF(self):
        """
        Test similarity between two terms in the MF ontology.
        GO:0051192 -> prosthetic group binding
        GO:0050662 -> coenzyme binding
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0051192", "GO:0050662")
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0051192", "GO:0050662"), mod_val)

    def test_normalized_similarity_MF(self):
        """
        Test normalized similarity between two terms in the MF ontology.
        GO:0051192 -> prosthetic group binding
        GO:0050662 -> coenzyme binding
        """
        mod_val = self.mod_sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0050662")
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0050662"), mod_val)



##########################################################################
# Cross Ontology similarity
##########################################################################
    def test_cross_ontology_similarity(self):
        """
        Test similarity between two terms in different ontologies
        GO:0051192 -> prosthetic group binding, MF
        GO:0007155 -> cell adhesion,            BP
        """
        mod_val = self.mod_sim.calculateTermSimilarity("GO:0051192", "GO:0007155")
        self.assertAlmostEqual(self.sim.calculateTermSimilarity("GO:0051192", "GO:0007155"), mod_val)

    def test_cross_ontology_normalized_similarity(self):
        """
        Test normalized similarity between two terms in different ontologies.
        GO:0051192 -> prosthetic group binding, MF
        GO:0007155 -> cell adhesion,            BP
        """
        mod_val = self.mod_sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0007155")
        self.assertAlmostEqual(self.sim.calculateNormalizedTermSimilarity("GO:0051192", "GO:0007155"), mod_val)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)

























