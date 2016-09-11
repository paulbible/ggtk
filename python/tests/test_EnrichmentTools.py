#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk
from ggtk import EnrichmentTools

class EnrichmentToolsTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")
        self.database = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")

class CoreMethodsTests(EnrichmentToolsTestCase):
##################################
# Test EnrichmentTools methods
    def test_enrichment_tools_hypergeometric_test(self):
        """
        Test that the enrichment tools function correctly calculates
         the hypergeometric p-value
        """
        p_val = EnrichmentTools.oneSidedRawPvalue_hyper(8,10,17,7)
        self.assertAlmostEqual(p_val, 0.036404771)

    def test_enrichment_tools_child_genes(self):
        """
        Test enrichment tools ability to select genes of a term or child of that term.
        GO:0002507 -> BP, tolerance induction (immune toerance)
        """
        term_genes = EnrichmentTools.getDescendantGenes(self.graph, self.database, 'GO:0002507')
        child_terms = set(self.graph.getDescendantTerms('GO:0002507'))
        child_terms.add('GO:0002507')
        for gene in term_genes:
            bp_terms = set(self.database.getGoTermsForGeneBP(gene, self.graph))
            # the intersection of the gene terms and the descendant terms should be > 0
            self.assertTrue(len(bp_terms & child_terms) > 0)

    def test_enrichment_tools_enrichment_significance(self):
        """
        Test enrichment of a specifit term against a set of genes
        """
        term_genes = EnrichmentTools.getDescendantGenes(self.graph, self.database, 'GO:0002507')
        p_val = EnrichmentTools.enrichmentSignificance(self.graph, self.database, term_genes, 'GO:0002507')
        self.assertAlmostEqual(p_val,1.9224043e-43)

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)



