#!/usr/bin/env python
#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import random
from ggtk import GoParser, AnnotationParser
from ggtk.TermMaps import TermInformationContentMap
from ggtk import TermSimilarity


random.seed(0)


def main():
    # Load the go graph and annotation data
    obo_go_graph_filename = '../../example_graphs/go-basic.obo'
    human_annotation_gaf_filename = '../../example_annotations/goa_human.gaf'
    print "Loading GO Graph from %s" % obo_go_graph_filename
    go_graph = GoParser.parse(obo_go_graph_filename, "obo")
    print "Loading Annotation Data from %s" % human_annotation_gaf_filename
    anno_data = AnnotationParser.parse(human_annotation_gaf_filename)
    print

    # Get only terms with annotations, Some terms without annotations have probability 0
    annotated_go_terms = anno_data.getAllGoTerms()

    # Lets work with some BP terms, Children of the root are all high level categories
    high_level_bp_terms = go_graph.getChildTerms(go_graph.getRootBP())

    # Similiarity values are often 0 when terms only share the root node.
    # So we will work with the descendants of one of these high level terms
    # choose a single high level term.
    bp_term = random.choice(high_level_bp_terms)

    print '---> Working with the "%s" branch of BP  <---' % go_graph.getTermName(bp_term)

    # We will work with the descendants of this term that are also annotated.
    descendants = set(go_graph.getDescendantTerms(bp_term)) & set(annotated_go_terms)

    # Select a few terms to analyze
    test_terms = random.sample(descendants, 4)
    print '---> Selected Test Terms <---'
    for term in test_terms:
        print ", ".join([term, go_graph.getTermName(term), go_graph.getTermDescription(term)[:50], '..."'])
    print

    # Construct the information content map
    ic_map = TermInformationContentMap(go_graph, anno_data)

    # Create similarity calculators from shared information
    # Ancestor mean
    shared_information_anc = TermSimilarity.AncestorMeanSharedInformation(go_graph, ic_map)
    sim_resnik_anc = TermSimilarity.ModularResnik(shared_information_anc)

    # Most informatics common ancestor (MICA)
    shared_information_mica = TermSimilarity.MICASharedInformation(go_graph, ic_map)
    sim_resnik_mica = TermSimilarity.ModularResnik(shared_information_mica)

    # Couto et al. 2007
    shared_information_couto = TermSimilarity.CoutoGraSMSharedInformation(go_graph, ic_map)
    sim_resnik_couto = TermSimilarity.ModularResnik(shared_information_couto)

    # Adjusted Couto measure
    shared_information_couto_adj = TermSimilarity.CoutoGraSMAdjustedSharedInformation(go_graph, ic_map)
    sim_resnik_couto_adj = TermSimilarity.ModularResnik(shared_information_couto_adj)

    # Frontier shared information
    shared_information_frontier = TermSimilarity.FrontierSharedInformation(go_graph, ic_map)
    sim_resnik_frontier = TermSimilarity.ModularResnik(shared_information_frontier)

    # Calculate Resnik similarity using various shared information calculations
    for i in range(len(test_terms)):
        term_i = test_terms[i]
        for j in range(i, len(test_terms)):
            term_j = test_terms[j]
            print '--> ResnikSim( %s, %s) using different Shared Information calculations <--' % (term_i, term_j)
            print '%f Ancestor Mean' % sim_resnik_anc.calculateNormalizedTermSimilarity(term_i, term_j)
            print '%f Most Informative Common Ancestor' % sim_resnik_mica.calculateNormalizedTermSimilarity(term_i, term_j)
            print '%f Couto et al.\'s GraSM' % sim_resnik_couto.calculateNormalizedTermSimilarity(term_i, term_j)
            print '%f Adjusted Couto' % sim_resnik_couto_adj.calculateNormalizedTermSimilarity(term_i, term_j)
            print '%f Frotier Shared Information' % sim_resnik_frontier.calculateNormalizedTermSimilarity(term_i, term_j)
            print

if __name__ == "__main__":
    main()
