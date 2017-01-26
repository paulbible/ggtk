#!/bin/env python
import sys
import getopt
import ggtk
from ggtk.TermSimilarity import PrecomputedMatrixTermSimilarity
from ggtk.TermSetSimilarity import BestMatchAverageSetSimilarity


def print_usage(msg=''):
    if len(msg) != 0:
        print msg
    print 'usage: proc_pair_scores.py -s score_file -o ontology -m matrix file -g graph_file -a annotation_file'
    print 'Take a list of pairs of genes and calculates their similarity'
    print
    print ' -h                               Print this help information'
    print ' -s <score_file>                  tab delimited file of uniprot pairs and scores'
    print ' -o <ontology>                    one of {bp, mf, cc}'
    print ' -m <matrix_file>                 A precompueted score matrix file'
    print ' -g <graph_file>                  A graph-file (go-basic.obo)'
    print ' -a <annotation_file>             An annotation file in GAF format.'


def process_and_validate_arguments():
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hs:o:m:g:a:', ['help', 'scores', 'ontology',
                                                                 'matrix', 'graph', 'annotations'])
    except getopt.GetoptError as err:
        print str(err)
        print_usage()
        sys.exit(2)

    score_file = None
    ontology = None
    matrix_file = None
    graph_file = None
    annotation_file = None

    if len(opts) == 0:
        print_usage()
        sys.exit(1)

    for opt, arg in opts:
        if opt in ('-h', '-help', '--help'):
            print_usage()
            sys.exit(1)
        elif opt in ('-s', '--scores'):
            score_file = arg
        elif opt in ('-o', '--ontology'):
            ontology = arg
        elif opt in ('-m', '--matrix'):
            matrix_file = arg
        elif opt in ('-g', '--graph'):
            graph_file = arg
        elif opt in ('-a', '--annotations'):
            annotation_file = arg
        else:
            print_usage("Error: Option %s non recognized" % opt)
            sys.exit(1)

    if not score_file:
        print_usage('ERROR No Score File: a pair scores file must be specified.')
        sys.exit(1)

    if not ontology:
        print_usage('ERROR No Ontology: an ontology must be specified bp, mf, cc')
        sys.exit(1)
    elif ontology not in ('bp', 'cc', 'mf'):
        print_usage('ERROR %s not a valid ontology: an ontology must be specified bp, mf, cc' % ontology)
        sys.exit(1)

    if not matrix_file:
        print_usage('ERROR No Matrix file: a matrix file must be specified')
        sys.exit(1)

    if not graph_file:
        print_usage('ERROR No graph file: a GO graph file must be specified')
        sys.exit(1)

    if not annotation_file:
        print_usage('ERROR No annotation file: a GO annotaiton file must be specified')
        sys.exit(1)

    return score_file, ontology, matrix_file, graph_file, annotation_file


def parse_pair_scores(filename):
    records = []
    with open(filename) as f:
        for line in f:
            line = line.strip()
            rec = line.split('\t')
            records.append(rec)
    return records


def get_terms_for_gene(gene, ontology, go_graph, annotations):
    if ontology == 'bp':
        return annotations.getGoTermsForGeneBP(gene, go_graph)
    if ontology == 'mf':
        return annotations.getGoTermsForGeneMF(gene, go_graph)
    if ontology == 'cc':
        return annotations.getGoTermsForGeneCC(gene, go_graph)
    else:
        return None


def main():
    score_file, ontology, matrix_file, graph_file, annotation_file = process_and_validate_arguments()

    score_recs = parse_pair_scores(score_file)
    similarity = PrecomputedMatrixTermSimilarity(matrix_file)
    bma_sim = BestMatchAverageSetSimilarity(similarity)

    if graph_file.find('xml') >= 0:
        graph = ggtk.GoParser.parse(graph_file, 'xml')
    else:
        graph = ggtk.GoParser.parse(graph_file, 'obo')
    annotations = ggtk.AnnotationParser.parse(annotation_file)

    for rec in score_recs:
        gene_a = rec[0]
        terms_a = get_terms_for_gene(gene_a, ontology, graph, annotations)
        gene_b = rec[1]
        terms_b = get_terms_for_gene(gene_b, ontology, graph, annotations)
        #print terms_a
        #print terms_b
        sim_value = bma_sim.calculateSimilarity(terms_a, terms_b)
        outs = rec
        outs.append(str(sim_value))
        print "\t".join(outs)
        #raw_input()


if __name__ == '__main__':
    main()
