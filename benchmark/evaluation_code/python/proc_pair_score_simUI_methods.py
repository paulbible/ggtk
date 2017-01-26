#!/bin/env python
import sys
import getopt
import ggtk
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSetSimilarity import SimUISetSimilarity
from ggtk.TermSetSimilarity import SimGICSetSimilarity
from ggtk.TermSetSimilarity import SimDICSetSimilarity
from ggtk.TermSetSimilarity import SimUICSetSimilarity

sim_type_set = {'ui', 'gic', 'dic', 'uic'}

def print_usage(msg=''):
    if len(msg) != 0:
        print msg
    print 'usage: proc_pair_score_simUI_methods.py -s score_file -o ontology -g graph_file ' \
          '-a annotation_file -t <sim_type>'
    print 'Take a list of pairs of genes and calculates their similarity'
    print
    print ' -h                               Print this help information'
    print ' -s <score_file>                  tab delimited file of uniprot pairs and scores'
    print ' -t <sim_type>                    The type of similarity method to use. One of the following:'
    print '                                    ui: the SimUI method by Gentleman et al. 2006 (Similar to Jaccard)'
    print '                                    gic: the SimGIC method by Pesquita et al. 2007 (IC weighted SimUI)'
    print '                                    dic: the SimDIC method by Mazandu et al. 2014 (Variation of SimGIC)'
    print '                                    uic: the SimUIC method by Mazandu et al. 2014 (Variation of SimGIC)'
    print ' -o <ontology>                    one of {bp, mf, cc}'
    print ' -g <graph_file>                  A graph-file (go-basic.obo)'
    print ' -a <annotation_file>             An annotation file in GAF format.'


def process_and_validate_arguments():
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'hs:o:t:g:a:', ['help', 'scores', 'ontology',
                                                                 'type', 'graph', 'annotations'])
    except getopt.GetoptError as err:
        print str(err)
        print_usage()
        sys.exit(2)

    score_file = None
    ontology = None
    sim_type = None
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
        elif opt in ('-t', '--type'):
            sim_type = arg
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

    if not sim_type:
        print_usage('ERROR No Similarity type: Please specify the similarity type with \'-t <sim_type>\'')
        sys.exit(1)
    elif sim_type not in sim_type_set:
        print_usage('ERROR Similarity type \'%s\': The similarity type must be one of %s' % (sim_type, sim_type_set))
        sys.exit(1)

    if not graph_file:
        print_usage('ERROR No graph file: a GO graph file must be specified')
        sys.exit(1)

    if not annotation_file:
        print_usage('ERROR No annotation file: a GO annotaiton file must be specified')
        sys.exit(1)

    return score_file, ontology, sim_type, graph_file, annotation_file


def parse_pair_scores(filename):
    records = []
    with open(filename) as f:
        for line in f:
            line = line.strip()
            rec = line.split('\t')
            records.append(rec)
    return records


def get_similarity_calculator(sim_type, graph, annotations):
    if sim_type == 'ui':
        sim = SimUISetSimilarity(graph)
    else:
        term_map = TermInformationContentMap(graph, annotations)
        if sim_type == 'gic':
            sim = SimGICSetSimilarity(graph, term_map)
        elif sim_type == 'dic':
            sim = SimDICSetSimilarity(graph, term_map)
        elif sim_type == 'uic':
            sim = SimUICSetSimilarity(graph, term_map)
        else:
            sim = SimUISetSimilarity(graph)
    return sim


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
    score_file, ontology, sim_type, graph_file, annotation_file = process_and_validate_arguments()

    score_recs = parse_pair_scores(score_file)

    if graph_file.find('xml') > 0:
        graph = ggtk.GoParser.parse(graph_file, 'xml')
    else:
        graph = ggtk.GoParser.parse(graph_file, 'obo')

    annotations = ggtk.AnnotationParser.parse(annotation_file)
    similarity = get_similarity_calculator(sim_type, graph, annotations)

    for rec in score_recs:
        gene_a = rec[0]
        terms_a = get_terms_for_gene(gene_a, ontology, graph, annotations)
        gene_b = rec[1]
        terms_b = get_terms_for_gene(gene_b, ontology, graph, annotations)
        sim_value = similarity.calculateSimilarity(terms_a, terms_b)
        outs = rec
        outs.append(str(sim_value))
        print "\t".join(outs)


if __name__ == '__main__':
    main()
