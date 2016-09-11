#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import random
import ggtk

random.seed(0)


class AnnotationParserTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.gaf_anno_filename = '../../example_annotations/goa_human.gaf'
        self.mgi_anno_filename = '../../example_annotations/gene_association.mgi'
        self.entrez_anno_filename = '../../example_annotations/human_gene2go'


class CoreMethodsTests(AnnotationParserTestCase):
#########################################################
# Parse an annotation file normally wtih default settings
#########################################################
    def test_annotation_parser_gaf(self):
        """
        Test that the parser reads the gaf annotation file correctly
        """
        data = ggtk.AnnotationParser.parse(self.gaf_anno_filename, 'gaf')
        self.assertTrue(data.getNumGenes() > 0)
        self.assertTrue(data.getNumGoTerms() > 0)

    def test_annotation_parser_mgi(self):
        """
        Test that the parser reads the mgi (same as gaf) annotation file correctly
        """
        data = ggtk.AnnotationParser.parse(self.mgi_anno_filename, 'mgi')
        self.assertTrue(data.getNumGenes() > 0)
        self.assertTrue(data.getNumGoTerms() > 0)

    def test_annotation_parser_entrez(self):
        """
        Test that the parser reads the gene2go annotation file correctly
        """
        data = ggtk.AnnotationParser.parse(self.entrez_anno_filename, 'entrez')
        self.assertTrue(data.getNumGenes() > 0)
        self.assertTrue(data.getNumGoTerms() > 0)

#########################################################
# Test Paerser with bad input
#########################################################
    def test_annotation_parser_gaf_nonexistent_file(self):
        """
        Test that the parsers rasise an error for a bad input file
        """
        with self.assertRaises(IOError):
            ggtk.AnnotationParser.parse('', 'gaf')

    def test_annotation_parser_mgi_nonexistent_file(self):
        """
        Test that the parsers rasise an error for a bad input file
        """
        with self.assertRaises(IOError):
            ggtk.AnnotationParser.parse('', 'mgi')

    def test_annotation_parser_entrez_nonexistent_file(self):
        """
        Test that the parsers rasise an error for a bad input file
        """
        with self.assertRaises(IOError):
            ggtk.AnnotationParser.parse('', 'entrez')

#################
# Bad file format
    def test_annotation_parser_gaf_bad_format(self):
        """
        Test that the parsers rasise an error for bad formatting
        """
        with self.assertRaises(IOError):
            ggtk.AnnotationParser.parse(self.entrez_anno_filename, 'gaf')

    def test_annotation_parser_entrez_bad_format(self):
        """
        Test that the parsers rasise an error for bad formatting
        """
        with self.assertRaises(IOError):
            ggtk.AnnotationParser.parse(self.gaf_anno_filename, 'entrez')


#################
# Bad file format
    def test_annotation_parser_bad_parser_type(self):
        """
        Test that the parser raises an error for having an unrecognised parser
        """
        with self.assertRaises(ValueError):
            ggtk.AnnotationParser.parse(self.gaf_anno_filename, 'fake')


#########################################################
# Test Parser with a subset of evidence codes
#########################################################
    def test_annotation_parser_gaf_custom_evidence_set(self):
        """
        Test that the parser respects evidence code subset
        """
        evidence_codes = ('IEA', 'IDA')
        data = ggtk.AnnotationParser.parse(self.gaf_anno_filename, 'gaf', evidence_codes)
        genes = data.getAllGenes()
        codes = set(data.getGoTermsEvidenceForGene(genes[random.randint(0, len(genes)-1)]))
        code_set = set(evidence_codes)
        for e_code in codes:
            self.assertTrue(e_code in code_set)


    def test_annotation_parser_entrez_custom_evidence_set(self):
        """
        Test that the parser respects evidence code subset
        """
        evidence_codes = ('IEA', 'IDA')
        data = ggtk.AnnotationParser.parse(self.entrez_anno_filename, 'entrez', evidence_codes)
        genes = data.getAllGenes()
        codes = set(data.getGoTermsEvidenceForGene(genes[random.randint(0, len(genes)-1)]))
        code_set = set(evidence_codes)
        for e_code in codes:
            self.assertTrue(e_code in code_set)

####################
# Bad evidence codes
    def test_annotation_parser_gaf_bad_custom_evidence_set(self):
        """
        Test that the parser raises an error for a bad evidence code subset
        """
        evidence_codes = ('','fake')
        with self.assertRaises(ValueError):
            ggtk.AnnotationParser.parse(self.gaf_anno_filename, 'gaf', evidence_codes)

    def test_annotation_parser_entrez_custom_evidence_set(self):
        """
        Test that the parser raises an error for a bad evidence code subset
        """
        evidence_codes = ('', 'fake')
        with self.assertRaises(ValueError):
            ggtk.AnnotationParser.parse(self.entrez_anno_filename, 'entrez', evidence_codes)

#############################
# Experimental evidence codes
    def test_annotation_parser_gaf_experimental_evidence_set(self):
        """
        Test that the parser respects evidence code subset
        """
        evidence_codes = ('EXP', 'IDA', 'IPI', 'IMP', 'IGI', 'IEP')
        data = ggtk.AnnotationParser.parse(self.gaf_anno_filename, 'gaf', 'exp')
        genes = data.getAllGenes()
        codes = set(data.getGoTermsEvidenceForGene(genes[random.randint(0, len(genes)-1)]))
        code_set = set(evidence_codes)
        for e_code in codes:
            self.assertTrue(e_code in code_set)

    def test_annotation_parser_entrez_experimental_evidence_set(self):
        """
        Test that the parser respects evidence code subset
        """
        evidence_codes = ('EXP', 'IDA', 'IPI', 'IMP', 'IGI', 'IEP')
        data = ggtk.AnnotationParser.parse(self.entrez_anno_filename, 'entrez', 'exp')
        genes = data.getAllGenes()
        codes = set(data.getGoTermsEvidenceForGene(genes[random.randint(0, len(genes)-1)]))
        code_set = set(evidence_codes)
        for e_code in codes:
            self.assertTrue(e_code in code_set)


if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)

