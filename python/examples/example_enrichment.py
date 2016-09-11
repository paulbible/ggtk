#!/usr/bin/env python
#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
from ggtk import GoParser, AnnotationParser, EnrichmentTools


def main():
    # Load the go graph and annotation data
    obo_go_graph_filename = '../../example_graphs/go-basic.obo'
    human_annotation_gaf_filename = '../../example_annotations/goa_human.gaf'
    print "Loading GO Graph from %s" % obo_go_graph_filename
    go_graph = GoParser.parse(obo_go_graph_filename, "obo")
    print "Loading Annotation Data from %s" % human_annotation_gaf_filename
    anno_data = AnnotationParser.parse(human_annotation_gaf_filename)
    print

    # Get some genes known to be somewhat related
    # GO:0002507 (BP) -> tolerance induction
    tolerance_induction_term = 'GO:0002507'
    descendant_genes = EnrichmentTools.getDescendantGenes(go_graph, anno_data, tolerance_induction_term)

    print '---> Genes having annotations relating to "tolerance induction" (%s) <---' % tolerance_induction_term
    print ', '.join(descendant_genes)
    print

    annotated_terms = []
    for gene in descendant_genes:
        annotated_terms.extend(anno_data.getGoTermsForGeneBP(gene, go_graph))
    # restrict to unique terms
    annotated_terms = set(annotated_terms)
    print '---> These genes are annotated with %i distinct BP terms <---' % len(annotated_terms)
    print

    # test enrichment of each term
    print '---> Enriched terms having a P < %1.1e <---' % 1e-5
    enriched_records = []
    for term in annotated_terms:
        p_val = EnrichmentTools.enrichmentSignificance(go_graph, anno_data, descendant_genes, term)
        if p_val < 1e-5:
            enriched_records.append([p_val, term, go_graph.getTermName(term)])

    # print the sorted list
    enriched_records.sort()
    for p_val, term, name in enriched_records:
        print 'P-value = %.5e, Term: %s, Name = %s' % (p_val, term, name)


if __name__ == "__main__":
    main()
