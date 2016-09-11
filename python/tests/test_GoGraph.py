#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import unittest
import ggtk


class GoGraphTestCase(unittest.TestCase):
    @classmethod
    def setUpClass(self):
        self.graph = ggtk.GoParser.parse("../../example_graphs/go-basic.obo","obo")

class CoreMethodsTests(GoGraphTestCase):
##########################################################################
# Vertex and Edge count accessors
##########################################################################
    def test_vertex_count_accessor(self):
        """
        print "Access vertex count"
        print "calling g.getNumVertices()", "\'%i\'"%(g.getNumVertices())
        print "--"
        print
        """
        self.assertEqual(self.graph.getNumVertices(),42718)

    def test_edge_count_accessor(self):
        """
            print "Access edge count"
            print "calling g.getNumEdges()", "\'%i\'"%(g.getNumEdges())
            print "--"
            print
        """
        self.assertEqual(self.graph.getNumEdges(), 81084)

##########################################################################
# Term attribute access, Name Descriptiona and Ontology type
##########################################################################
    def test_term_name_bad_id(self):
        """
            print "Get term name for non-existant term"
            print "calling g.getTermName(\"GO:00507\")", "\'%s\'"%(g.getTermName("GO:00507"))
            print "--"
            print
        """
        self.assertEqual(self.graph.getTermName("GO:00507"),'')

    def test_term_desc_bad_id(self):
        """
            print "Get term description for non-existant term"
            print "calling g.getTermDescription(\"GO:00507\")", "\'%s\'"%(g.getTermDescription("GO:00507"))
            print "--"
            print
        """
        self.assertEqual(self.graph.getTermDescription("GO:00507"), '')

    def test_term_name_BP(self):
        """
            print "Get term name, GO:0050789 in BP"
            print "calling g.getTermName(\"GO:0050789\")", "\'%s\'"%(g.getTermName("GO:0050789"))
            print "--"
            print
        """
        self.assertEqual(self.graph.getTermName("GO:0050789"), 'regulation of biological process')

    def test_term_desc_BP(self):
        """
            print "Get term description, GO:0050789 in BP"
            print "calling g.getTermDescription(\"GO:0050789\")", "\'%s\'"%(g.getTermDescription("GO:0050789"))
            print "--"
            print
        """
        desc = '"Any process that modulates the frequency, rate or extent of a biological process. Biological processes are regulated by many means; examples include the control of gene expression, protein modification or interaction with a protein or substrate molecule." [GOC:ai, GOC:go_curators]'
        self.assertEqual(self.graph.getTermDescription("GO:0050789"),desc)

    def test_term_name_MF(self):
        """
            print "Get term description, GO:0005385 in MF"
            print "calling g.getTermName(\"GO:0005385\")", "\'%s\'"%(g.getTermName("GO:0005385"))
            print "--"
            print
        """
        self.assertEqual(self.graph.getTermName("GO:0005385"),'zinc ion transmembrane transporter activity')

    def test_term_desc_MF(self):
        """
            print "Get term description, GO:0005385 in MF"
            print "calling g.getTermDescription(\"GO:0005385\")", "\'%s\'"%(g.getTermDescription("GO:0005385"))
            print "--"
            print
        """
        desc = '"Enables the transfer of zinc (Zn) ions from one side of a membrane to the other." [GOC:dgf]'
        self.assertEqual(self.graph.getTermDescription("GO:0005385"), desc)

    def test_term_name_CC(self):
        """
            print "Get term name, GO:0009898 in CC"
            print "calling g.getTermName(\"GO:0009898\")", "\'%s\'"%(g.getTermName("GO:0009898"))
            print "--"
            print
        """
        self.assertEqual(self.graph.getTermName("GO:0009898"), 'cytoplasmic side of plasma membrane')

    def test_term_desc_CC(self):
        """
            print "Get term description, GO:0009898 in CC"
            print "calling g.getTermName(\"GO:0009898\")", "\'%s\'"%(g.getTermDescription("GO:0009898"))
            print "--"
            print
        """
        desc = '"The leaflet the plasma membrane that faces the cytoplasm and any proteins embedded or anchored in it or attached to its surface." [GOC:dos, GOC:tb]'
        self.assertEqual(self.graph.getTermDescription("GO:0009898"), desc)

########################
# Ontology type and code

    def test_term_ontology_bad_id(self):
        """
        Test the ontology accessor with a bad id.
        """
        self.assertEqual(self.graph.getTermOntology("GO:00098"),'ONTOLOGY_ERROR')


    def test_term_ontology_code_bad_id(self):
        """
        Test the ontology accessor with a bad id.
        """
        self.assertEqual(self.graph.getTermOntologyCode("GO:00098"), 3)

    def test_term_ontology_BP(self):
        """
        Test the ontology accessor for BP term GO:0022403
        """
        self.assertEqual(self.graph.getTermOntology("GO:0022403"),'biological_process')

    def test_term_ontology_code_BP(self):
        """
        Test the ontology code accessor for BP term GO:0022403
        """
        self.assertEqual(self.graph.getTermOntologyCode("GO:0022403"), 0)


    def test_term_ontology_MF(self):
        """
        Test the ontology accessor for MF term GO:0048037
        """
        self.assertEqual(self.graph.getTermOntology("GO:0048037"),'molecular_function')

    def test_term_ontology_code_MF(self):
        """
        Test the ontology code accessor for MF term GO:0048037
        """
        self.assertEqual(self.graph.getTermOntologyCode("GO:0048037"), 1)

    def test_term_ontology_CC(self):
        """
        Test the ontology accessor for CC term GO:0005911
        """
        self.assertEqual(self.graph.getTermOntology("GO:0005911"),'cellular_component')

    def test_term_ontology_code_CC(self):
        """
        Test the ontology code accessor for CC term GO:0005911
        """
        self.assertEqual(self.graph.getTermOntologyCode("GO:0005911"), 2)

##########################################################################
# Relative accessors, Ancestors, Descendants, Parents, Childred
##########################################################################

###########
# Ancestors
    def test_term_ancestors_bad_id(self):
        """
        Test the accessor for term ancestors with a bad id.
        """
        self.assertEqual(self.graph.getAncestorTerms("GO:00098"), ())

    def test_term_ancestors_BP(self):
        """
        Test the accessor for term ancestors of GO:0022403 in BP
        """
        self.assertEqual(self.graph.getAncestorTerms("GO:0022403"), ('GO:0044848', 'GO:0008150'))

    def test_term_ancestors_MF(self):
        """
        Test the accessor for term ancestors of GO:0048037 in MF
        """
        self.assertEqual(self.graph.getAncestorTerms("GO:0048037"), ('GO:0005488', 'GO:0003674'))

    def test_term_ancestors_CC(self):
        """
        Test the accessor for term ancestors of GO:0005911 in CC
        """
        self.assertEqual(self.graph.getAncestorTerms("GO:0005911"), ('GO:0005575', 'GO:0030054'))

#############
# Descendants
    def test_term_descendants_bad_id(self):
        """
        Test the accessor for term descendants with a bad id.
        """
        self.assertEqual(self.graph.getDescendantTerms("GO:00098"), ())

    def test_term_descendants_BP(self):
        """
        Test the accessor for term descendants GO:0051318 in BP
        """
        self.assertEqual(self.graph.getDescendantTerms("GO:0051318"), ('GO:0000080', 'GO:0051330'))

    def test_term_descendants_MF(self):
        """
        Test the accessor for term descendants GO:0042165 in MF
        """
        self.assertEqual(self.graph.getDescendantTerms("GO:0042165"), ('GO:0031626', 'GO:0042166'))

    def test_term_descendants_CC(self):
        """
        Test the accessor for term descendants GO:0030057 in CC
        """
        self.assertEqual(self.graph.getDescendantTerms("GO:0030057"), ('GO:0090635', 'GO:0090636', 'GO:0090637'))

##############################
# Parents, immediate ancestors
    def test_term_parents_bad_id(self):
        """
        Test the parent accessor for a bad term id
        """
        self.assertEqual(self.graph.getParentTerms("GO:0022"),())

    def test_term_parents_BP(self):
        """
        Test the accessor for term ancestors of GO:0022403 in BP
        """
        self.assertEqual(self.graph.getParentTerms("GO:0022403"), ('GO:0044848',))

    def test_term_parents_MF(self):
        """
        Test the accessor for term ancestors of GO:0048037 in MF
        """
        self.assertEqual(self.graph.getParentTerms("GO:0048037"), ('GO:0005488',))

    def test_term_parents_CC(self):
        """
        Test the accessor for term ancestors of GO:0005911 in CC
        """
        self.assertEqual(self.graph.getParentTerms("GO:0005911"), ('GO:0030054',))

#################################
# Children, immediate descendants
    def test_term_children_bad_id(self):
        """
        Test the accessor for term children with a bad id.
        """
        self.assertEqual(self.graph.getChildTerms("GO:00098"), ())

    def test_term_children_BP(self):
        """
        Test the accessor for term children of GO:0051319 in BP
        """
        self.assertEqual(self.graph.getChildTerms("GO:0051319"), ('GO:0051331', 'GO:0000085'))

    def test_term_children_MF(self):
        """
        Test the accessor for term children of GO:0001071 in MF
        """
        self.assertEqual(self.graph.getChildTerms("GO:0001071"), ('GO:0003700', 'GO:0001070'))

    def test_term_children_CC(self):
        """
        Test the accessor for term children GO:0031974 in CC
        """
        children = ('GO:1904724', 'GO:1904813', 'GO:0043233', 'GO:0031970')
        self.assertEqual(self.graph.getChildTerms("GO:0031974"), children)


###########################################################################
# Retrieve terms sets and ontology term sets
###########################################################################
    def test_all_terms_accessor(self):
        """
        Test access for all terms in the graph
        """
        all_terms = self.graph.getAllTerms()
        self.assertEqual(len(all_terms), 42718)

    def test_all_terms_accessor_bp(self):
        """
        Test access for all terms in the graph
        """
        all_terms = self.graph.getAllTermsBP()
        self.assertEqual(len(all_terms), 28651)

    def test_all_terms_accessor_mf(self):
        """
        Test access for all terms in the graph
        """
        all_terms = self.graph.getAllTermsMF()
        self.assertEqual(len(all_terms), 10160)

    def test_all_terms_accessor_cc(self):
        """
        Test access for all terms in the graph
        """
        all_terms = self.graph.getAllTermsCC()
        self.assertEqual(len(all_terms), 3907)



###########################################################################
# Test filtering functions
###########################################################################
    def test_filter_for_bp(self):
        """
        Test the graph can filter the list for BP only
        GO:0033631 (BP) -> cell-cell adhesion mediated by integrin 
        GO:0033627 (BP) -> cell adhesion mediated by integrin
        GO:0004099 (MF) -> chitin deacetylase activity
        GO:0019213 (MF) -> deacetylase activity
        GO:0044225 (CC) -> apical pole of neuron
        GO:0043025 (CC) -> neuronal cell body
        """
        test_list = ('GO:0033631', 'GO:0033627', 'GO:0004099', 'GO:0019213', 'GO:0044225', 'GO:0043025')
        filtered_list = self.graph.filterForBP(test_list)
        for term in filtered_list:
            self.assertEqual(self.graph.getTermOntology(term), 'biological_process')
        self.assertEqual(len(filtered_list),2)
        

    def test_filter_for_mf(self):
        """
        Test the graph can filter the list for BP only
        GO:0033631 (BP) -> cell-cell adhesion mediated by integrin
        GO:0033627 (BP) -> cell adhesion mediated by integrin
        GO:0004099 (MF) -> chitin deacetylase activity
        GO:0019213 (MF) -> deacetylase activity
        GO:0044225 (CC) -> apical pole of neuron
        GO:0043025 (CC) -> neuronal cell body
        """
        test_list = ('GO:0033631', 'GO:0033627', 'GO:0004099', 'GO:0019213', 'GO:0044225', 'GO:0043025')
        filtered_list = self.graph.filterForMF(test_list)
        for term in filtered_list:
            self.assertEqual(self.graph.getTermOntology(term), 'molecular_function')
        self.assertEqual(len(filtered_list),2)


    def test_filter_for_cc(self):
        """
        Test the graph can filter the list for BP only
        GO:0033631 (BP) -> cell-cell adhesion mediated by integrin
        GO:0033627 (BP) -> cell adhesion mediated by integrin
        GO:0004099 (MF) -> chitin deacetylase activity
        GO:0019213 (MF) -> deacetylase activity
        GO:0044225 (CC) -> apical pole of neuron
        GO:0043025 (CC) -> neuronal cell body
        """
        test_list = ('GO:0033631', 'GO:0033627', 'GO:0004099', 'GO:0019213', 'GO:0044225', 'GO:0043025')
        filtered_list = self.graph.filterForCC(test_list)
        for term in filtered_list:
            self.assertEqual(self.graph.getTermOntology(term), 'cellular_component')
        self.assertEqual(len(filtered_list),2)


#############################################################################
# Test accessors for the root terms of the 3 ontologies
#############################################################################
    def test_root_term_access_bp(self):
        """
        Test access for the root term in the BP ontology
        """
        self.assertEqual(self.graph.getRootBP(),'GO:0008150')

    def test_root_term_access_mf(self):
        """
        Test access for the root term in the MF ontology
        """
        self.assertEqual(self.graph.getRootMF(),'GO:0003674')

    def test_root_term_access_cc(self):
        """
        Test access for the root term in the CC ontology
        """
        self.assertEqual(self.graph.getRootCC(),'GO:0005575')



if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(CoreMethodsTests)
    unittest.TextTestRunner(verbosity=2).run(suite)

























