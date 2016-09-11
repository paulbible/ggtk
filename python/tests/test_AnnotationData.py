#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk


class AnnotationDataTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.data = ggtk.AnnotationParser.parse("../../example_annotations/goa_human.gaf")

class CoreMethodsTests(AnnotationDataTestCase):
##################################
# Gene and GO Term count accessors
    def test_gene_count_accessor(self):
        """
        Test that the AnnotationData object reads the correct number of genes
        """
        self.assertEqual(self.data.getNumGenes(), 19194)

    def test_go_count_accessor(self):
        """
        Test that the AnnotationData object reads the correct number of GO terms
        """
        self.assertEqual(self.data.getNumGoTerms(), 16556)


##################################
# Access all Genes and GO Term as lists
    def test_get_all_go_terms(self):
        """
        Test getting a list of all go terms
        """
        res = self.data.getAllGoTerms()
        self.assertEqual(len(res), self.data.getNumGoTerms())

    def test_get_all_genes(self):
        """
        Test gettting a list of all genes
        """
        res = self.data.getAllGenes()
        self.assertEqual(len(res), self.data.getNumGenes())


######################################################
# Test existence of genes and go terms in the database
    def test_has_gene_bad_id(self):
        """
        Test that the database returns fasle when asked if it has a non existent gene
        """
        self.assertEqual(self.data.hasGene("ABC12345"), False)

    def test_has_gene(self):
        """
        Test that the database returns fasle when asked if it has a non existent gene
        """
        self.assertEqual(self.data.hasGene("A0A024R161"), True)

######################################
# Per Gene/ Per Term annotation counts
    def test_num_gene_annotations_bad_id(self):
        """
        Test access for the number of terms annotated to a gene using a bad id.
        """
        self.assertEqual(self.data.getNumAnnotationsForGene("ABC12345"), 0)

    def test_num_gene_annotations(self):
        """
        Test access for the number of terms annotated to a gene.
        """
        self.assertEqual(self.data.getNumAnnotationsForGene("A0A024R161"), 3)


    def test_num_go_annotations_bad_id(self):
        """
        Test access for the number of genes annotated with a GO term using a bad id.
        """
        self.assertEqual(self.data.getNumAnnotationsForGoTerm("GO:00"), 0)

    def test_num_go_annotations(self):
        """
        Test access for the number of genes annotated with a GO term.
        """
        self.assertEqual(self.data.getNumAnnotationsForGoTerm("GO:0004871"), 216)

###########################################
# List of go terms for genes and vice versa
    def test_go_terms_for_gene_bad_id(self):
        """
        Test list accessor for go terms annotated to a gene with a bad id
        """
        self.assertEqual(self.data.getGoTermsForGene("ABC12345"), ())

    def test_go_terms_for_gene(self):
        """
        Test list accessor for go terms annotated to a gene
        """
        self.assertEqual(self.data.getGoTermsForGene("A0A024R161"), ('GO:0004871', 'GO:0005834', 'GO:0007186'))

    def test_genes_for_go_term_bad_id(self):
        """
        Test list accessor for genes annotated with a go term using a bad id
        """
        self.assertEqual(self.data.getGenesForGoTerm("ABC12345"), ())

    def test_genes_for_go_term(self):
        """
        Test list accessor for genes annotated with a go term
        """
        self.assertEqual(self.data.getGenesForGoTerm("GO:0000015"), ('A6NNW6', 'P06733', 'P09104', 'P13929'))

########################################################
# List of evidence codes for each annotated term or gene
    def test_evidence_codes_for_gos_w_gene_query_bad_id(self):
        """
        Test list accessor for the corresponding evidence code for each go terms with a bad query id
        """
        self.assertEqual(self.data.getGoTermsEvidenceForGene("ABC12345"), ())

    def test_evidence_codes_for_gos_w_gene_query(self):
        """
        Test list accessor for the corresponding evidence code for each go terms
        """
        self.assertEqual(self.data.getGoTermsEvidenceForGene("A0A024R161"), ('IEA', 'IEA', 'IEA'))

    def test_evidence_codes_for_gene_w_go_query_bad_id(self):
        """
        Test list accessor for the corresponding evidence code for each gene with a bad query id
        """
        self.assertEqual(self.data.getGenesEvidenceForGoTerm("GO:1234"), ())

    def test_evidence_codes_for_gene_w_go_query(self):
        """
        Test list accessor for the corresponding evidence code for each gene
        """
        self.assertEqual(self.data.getGenesEvidenceForGoTerm("GO:0000015"), ('IEA', 'IEA', 'IEA', 'IEA'))


    def test_evidence_codes_for_gos_w_gene_query_2(self):
        """
        Test list accessor for the corresponding evidence code for each go terms
        Test with another id with more diversity in evidence codes.
        """
        res = ('IEA', 'ISS', 'IEA', 'ISS', 'IEA',
               'ISS', 'ISS', 'ISS', 'TAS', 'TAS',
               'TAS', 'TAS', 'TAS', 'TAS', 'TAS', 'TAS')
        self.assertEqual(self.data.getGoTermsEvidenceForGene("A0AVF1"), res)

    def test_evidence_codes_and_go_list_w_gene_query(self):
        """
        A more thorough test of the correspondence between evidence codes and go terms associated to a gene.

Recodes from GAF file for A0AVF1
!GOC Validation Date: 07/08/2016 $
!Submission Date: 7/7/2016
...
!Generated: 2016-07-04 09:24
!GO-version: http://purl.obolibrary.org/obo/go/releases/2016-06-29/go.owl
...
--
UniProtKB       A0AVF1  TTC26           GO:0005813      GO_REF:0000019  IEA
UniProtKB       A0AVF1  TTC26           GO:0007224      GO_REF:0000024  ISS
UniProtKB       A0AVF1  TTC26           GO:0007286      GO_REF:0000019  IEA
UniProtKB       A0AVF1  TTC26           GO:0030992      GO_REF:0000024  ISS
UniProtKB       A0AVF1  TTC26           GO:0036064      GO_REF:0000019  IEA
UniProtKB       A0AVF1  TTC26           GO:0042073      GO_REF:0000024  ISS
UniProtKB       A0AVF1  TTC26           GO:0042384      GO_REF:0000024  ISS
UniProtKB       A0AVF1  TTC26           GO:0072372      GO_REF:0000024  ISS
UniProtKB       A0AVF1  TTC26           GO:0072372      Reactome:R-HSA-5624949  TAS
UniProtKB       A0AVF1  TTC26           GO:0072372      Reactome:R-HSA-5625416  TAS
UniProtKB       A0AVF1  TTC26           GO:0072372      Reactome:R-HSA-5625424  TAS
UniProtKB       A0AVF1  TTC26           GO:0072372      Reactome:R-HSA-5625426  TAS
UniProtKB       A0AVF1  TTC26           GO:0097542      Reactome:R-HSA-5624952  TAS
UniProtKB       A0AVF1  TTC26           GO:0097542      Reactome:R-HSA-5625416  TAS
UniProtKB       A0AVF1  TTC26           GO:0097542      Reactome:R-HSA-5625421  TAS
UniProtKB       A0AVF1  TTC26           GO:0097542      Reactome:R-HSA-5625426  TAS
--
        """
        evi = ('IEA', 'ISS', 'IEA', 'ISS', 'IEA',
               'ISS', 'ISS', 'ISS', 'TAS', 'TAS',
               'TAS', 'TAS', 'TAS', 'TAS', 'TAS', 'TAS')
        gos = ('GO:0005813', 'GO:0007224', 'GO:0007286',
               'GO:0030992', 'GO:0036064', 'GO:0042073',
               'GO:0042384', 'GO:0072372', 'GO:0072372',
               'GO:0072372', 'GO:0072372', 'GO:0072372',
               'GO:0097542', 'GO:0097542', 'GO:0097542', 'GO:0097542')
        db_evi = self.data.getGoTermsEvidenceForGene("A0AVF1")
        db_gos = self.data.getGoTermsForGene("A0AVF1")
        self.assertEqual(len(db_evi), len(db_gos))
        self.assertEqual(db_evi, evi)
        self.assertEqual(db_gos, gos)
        self.assertEqual(db_gos[0] == "GO:0005813" and
                         db_evi[0] == "IEA", True)
        self.assertEqual(db_gos[1] == "GO:0007224" and
                         db_evi[1] == "ISS", True)

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)



