#!/usr/bin/env python
#/*=============================================================================
#Copyright (c) 2016 Paul W. Bible
#
#Distributed under the Boost Software License, Version 1.0. (See accompanying
#file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
import random
from ggtk import GoParser, AnnotationParser, EnrichmentTools
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSimilarity import LinSimilarity
from ggtk.TermSetSimilarity import BestMatchAverageSetSimilarity


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

    # Get some genes known to be somewhat related
    # GO:0002507 (BP) -> tolerance induction
    tolerance_induction_term = 'GO:0002507'
    descendant_genes = EnrichmentTools.getDescendantGenes(go_graph, anno_data, tolerance_induction_term)
    tolerance_induction_genes = random.sample(descendant_genes, 4)
    print '---> Genes having annotations relating to "tolerance induction" (%s) <---' % tolerance_induction_term
    for gene in tolerance_induction_genes:
        print '%s' % gene
    print

    # Randomly choose some other genes
    likely_unrelated_genes = random.sample(anno_data.getAllGenes(), 2)
    print '---> Randomly selected genes, unlikely related to "tolerance induction" <--- '
    for gene in likely_unrelated_genes:
        print gene
    print

    # Construct Term Similarity methods
    ic_map = TermInformationContentMap(go_graph, anno_data)
    lin_similarity = LinSimilarity(go_graph, ic_map)
    # Best Match Average term set similarity (BMA)
    best_match_average = BestMatchAverageSetSimilarity(lin_similarity)

    # Check similarity between genes that are likely related
    print "---> Gene semantic similarity between related genes <---"
    for i in range(len(tolerance_induction_genes)):
        term_i = tolerance_induction_genes[i]
        # get the set of BP terms
        bp_terms_i = anno_data.getGoTermsForGeneBP(term_i, go_graph)
        for j in range(i + 1, len(tolerance_induction_genes)):
            term_j = tolerance_induction_genes[j]
            # get the set of BP terms
            bp_terms_j = anno_data.getGoTermsForGeneBP(term_j, go_graph)

            # Calculate gene similarity by BMA
            sim = best_match_average.calculateSimilarity(bp_terms_i, bp_terms_j)
            print "Sim(%s, %s) = %f" % (term_i, term_j, sim)
    print

    # Check similarity between tolerance induction genes and randomly selected genes
    print "---> Gene semantic similarity between likely unrelated genes <---"
    for i in range(len(tolerance_induction_genes)):
        term_i = tolerance_induction_genes[i]
        # get the set of BP terms
        bp_terms_i = anno_data.getGoTermsForGeneBP(term_i, go_graph)
        for j in range(len(likely_unrelated_genes)):
            term_j = likely_unrelated_genes[j]
            # get the set of BP terms
            bp_terms_j = anno_data.getGoTermsForGeneBP(term_j, go_graph)
            # Calculate gene similarity by BMA
            sim = best_match_average.calculateSimilarity(bp_terms_i, bp_terms_j)
            print "Sim(%s, %s) = %f" % (term_i, term_j, sim)

if __name__ == "__main__":
    main()
