#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk


class GoParserTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph_obo_filename = "../../example_graphs/go-basic.obo"
        self.graph_xml_filename = "../../example_graphs/go_daily-termdb.obo-xml"

class CoreMethodsTests(GoParserTestCase):
##########################################################################
# parse a go file normally with the standard relationship set
##########################################################################
    def test_parse_obo(self):
        """
        Test if an obo go file can be parsed.
        """
        g = ggtk.GoParser.parse(self.graph_obo_filename, 'obo')
        self.assertTrue(g.getNumVertices() > 0)
        self.assertTrue(g.getNumEdges() > 0)

    def test_parse_xml(self):
        """
        Test if an obo-xml file can be parse.
        """
        g = ggtk.GoParser.parse(self.graph_xml_filename, 'xml')
        self.assertTrue(g.getNumVertices() > 0)
        self.assertTrue(g.getNumEdges() > 0)

##########################################################################
# parse a go file with a custom relationship set
##########################################################################
    def test_parse_obo_custom_relationships(self):
        """
        Test if an obo go file can be parsed.
        """
        rels = ['is_a','part_of']
        g = ggtk.GoParser.parse(self.graph_obo_filename, 'obo', rels)
        self.assertTrue(g.getNumVertices() > 0)
        self.assertTrue(g.getNumEdges() > 0)

    def test_parse_xml_custom_relationships(self):
        """
        Test if an obo-xml file can be parse.
        """
        rels = ['is_a','part_of']
        g = ggtk.GoParser.parse(self.graph_xml_filename, 'xml', rels)
        self.assertTrue(g.getNumVertices() > 0)
        self.assertTrue(g.getNumEdges() > 0)

    def test_parse_obo_custom_relationships_bad_set(self):
        """
        Test if an obo go file can be parsed.
        """
        rels = ['part_of']
        with self.assertRaises(ValueError):
            ggtk.GoParser.parse(self.graph_obo_filename, 'obo', rels)

    def test_parse_xml_custom_relationships_bad_set(self):
        """
        Test if an obo-xml file can be parse.
        """
        rels = ['part_of']
        with self.assertRaises(ValueError):
            ggtk.GoParser.parse(self.graph_xml_filename, 'xml', rels)

    def test_parse_obo_all_relationships(self):
        """
        Test if an obo go file can be parsed.
        """
        all_rels = ['is_a', 'part_of', 'regulates', 'positively_regulates', 'negatively_regulates']
        g = ggtk.GoParser.parse(self.graph_obo_filename, 'obo', all_rels)
        self.assertTrue(g.getNumVertices() > 0)
        self.assertTrue(g.getNumEdges() > 0)

    def test_parse_xml_all_relationships(self):
        """
        Test if an obo-xml file can be parse.
        """
        all_rels = ['is_a', 'part_of', 'regulates', 'positively_regulates', 'negatively_regulates']
        g = ggtk.GoParser.parse(self.graph_xml_filename, 'xml', all_rels)
        self.assertTrue(g.getNumVertices() > 0)
        self.assertTrue(g.getNumEdges() > 0)

##########################################################################
# Nonexistant file
##########################################################################
    def test_parse_obo_bad_file_name(self):
        """
        Test parser reaction to a nonexistent file.
        """
        with self.assertRaises(IOError):
	    ggtk.GoParser.parse('', 'obo')

    def test_parse_xml_bad_file_name(self):
        """
        Test parser reaction to a nonexistent file.
        """
        with self.assertRaises(IOError):
            ggtk.GoParser.parse('', 'xml')

##########################################################################
# Bad Formatting
##########################################################################
    def test_parse_obo_bad_format(self):
        """
        Test parser reaction to a non existent file. Obo parser on xml
        """
        with self.assertRaises(IOError):
            ggtk.GoParser.parse(self.graph_xml_filename, 'obo')

    def test_parse_xml_bad_format(self):
        """
        Test parser reaction to a non existent file.
        """
        with self.assertRaises(IOError):
            ggtk.GoParser.parse(self.graph_obo_filename, 'xml')

    def test_parse_bad_parser_type(self):
        """
        Test parser reaction to a non existent file.
        """
        with self.assertRaises(ValueError):
            ggtk.GoParser.parse(self.graph_obo_filename, 'fake')



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)

























