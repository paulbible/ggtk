#!/usr/bin/env python
#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
from ggtk import GoParser
from ggtk.TermMaps import TermDepthMap


def main():
    # Load a graph
    obo_go_graph_filename = '../../example_graphs/go-basic.obo'
    print "Loading GO Graph from %s" % obo_go_graph_filename
    go_graph = GoParser.parse(obo_go_graph_filename, "obo")
    print

    # Graph statistics
    print "----> Graph Statistics <----"
    n_edges = go_graph.getNumEdges()
    n_vertices = go_graph.getNumVertices()
    print "Number of Relationships (edges) in the graph: %i" % n_edges
    print "Number of Terms (vertices) in the graph: %i" % n_vertices
    print

    # Sub-ontology statistics
    print "----> Ontology Statistics <----"
    bp_terms = go_graph.getAllTermsBP()
    mf_terms = go_graph.getAllTermsMF()
    cc_terms = go_graph.getAllTermsCC()
    print "Number of BP terms: %i" % len(bp_terms)
    print "-- BP Examples: "
    for term in bp_terms[:3]:
        print ", ".join([term, go_graph.getTermName(term), go_graph.getTermDescription(term)[:50], '..."'])
    print

    print "Number of MF terms: %i" % len(mf_terms)
    print "-- MF Examples: "
    for term in mf_terms[:3]:
        print ", ".join([term, go_graph.getTermName(term), go_graph.getTermDescription(term)[:50], '..."'])
    print

    print "Number of CC terms: %i" % len(cc_terms)
    print "-- CC Examples: "
    for term in cc_terms[:3]:
        print ", ".join([term, go_graph.getTermName(term), go_graph.getTermDescription(term)[:50], '..."'])
    print

    print "Total terms: %i" % (len(bp_terms) + len(mf_terms) + len(cc_terms))
    print

    # Analyze term depth
    print "----> Term Depth of the 3 Ontologies <----"
    termDepth = TermDepthMap(go_graph)

    bp_depths = [termDepth[term] for term in bp_terms]
    max_bp_depth = max(bp_depths)
    print "Max term depth in BP: %i" % max_bp_depth
    print "Avg term depth in BP: %f" % (sum(bp_depths) / float(len(bp_depths)))
    print

    mf_depths = [termDepth[term] for term in mf_terms]
    max_mf_depth = max(mf_depths)
    print "Max term depth in MF: %i" % max_mf_depth
    print "Avg term depth in MF: %f" % (sum(mf_depths) / float(len(mf_depths)))
    print

    cc_depths = [termDepth[term] for term in cc_terms]
    max_cc_depth = max(cc_depths)
    print "Max term depth in CC: %i" % max_cc_depth
    print "Avg term depth in MF: %f" % (sum(cc_depths) / float(len(cc_depths)))
    print

    print "----> In Degree and Out Degree <----"
    bp_in_degrees = [len(go_graph.getChildTerms(term)) for term in bp_terms]
    bp_out_degrees = [len(go_graph.getParentTerms(term)) for term in bp_terms]
    print "Max BP In Degree (Children) %i" % max(bp_in_degrees)
    print "Avg BP In Degree %f" % (sum(bp_in_degrees) / float(len(bp_in_degrees)))
    print "Max BP Out Degree (Parents) %i" % max(bp_out_degrees)
    print "Avg BP Out Degree %f" % (sum(bp_out_degrees) / float(len(bp_out_degrees)))
    print

    mf_in_degrees = [len(go_graph.getChildTerms(term)) for term in mf_terms]
    mf_out_degrees = [len(go_graph.getParentTerms(term)) for term in mf_terms]
    print "Max MF In Degree (Children) %i" % max(mf_in_degrees)
    print "Avg MF In Degree %f" % (sum(mf_in_degrees) / float(len(mf_in_degrees)))
    print "Max MF Out Degree (Parents) %i" % max(mf_out_degrees)
    print "Avg MF Out Degree %f" % (sum(mf_out_degrees) / float(len(mf_out_degrees)))
    print

    cc_in_degrees = [len(go_graph.getChildTerms(term)) for term in cc_terms]
    cc_out_degrees = [len(go_graph.getParentTerms(term)) for term in cc_terms]
    print "Max MF In Degree (Children) %i" % max(cc_in_degrees)
    print "Avg MF In Degree %f" % (sum(cc_in_degrees) / float(len(cc_in_degrees)))
    print "Max MF Out Degree (Parents) %i" % max(cc_out_degrees)
    print "Avg MF Out Degree %f" % (sum(cc_out_degrees) / float(len(cc_out_degrees)))
    print


if __name__ == '__main__':
    main()
