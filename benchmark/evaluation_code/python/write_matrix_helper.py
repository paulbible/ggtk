#!/bin/env python
import sys
import getopt
import ggtk
import  ggtk.TermSimilarity


def print_usage(msg=''):
    if len(msg) != 0:
        print msg
    print 'usage: write_matrix_helper.py -o ontology -s similarity_type -i si_type -g graph_file -a annotation_file -o' \
          ' output_file'
    print
    print 'This scripts helps to automate writing term similarity matrix files for use with the ' \
          'PrecomputedMatrixTermSimilarity'
    print
    print 'Warning: grasm and agrasm Shared Information methods are extremely slow. BP is slower than MF,' \
          ' and MF is slower than CC'
    print
    print ' -h                               Print this help information'
    print ' -o <ontology>                    One of {bp, mf, cc}'
    print ' -s <similarity_type>             One of {res, lin, jc} for Resnik, Lin, Jiang-Conrath'
    print ' -i <si_type>                     One of {casi, mica, grasm, agrasm, sf} shared information types'
    print ' -g <graph_file>                  A graph-file (go-basic.obo-xml)'
    print ' -a <annotation_file>             An annotation file in GAF format.'
    print ' -m <matrix_file>                 Where the matrix file will be saved.'

valid_ontology_types = ('bp', 'mf', 'cc')
valid_similarity_types = ('res', 'lin', 'jc')
valid_si_types = ('casi', 'mica', 'grasm', 'agrasm', 'sf')

def process_and_validate_arguments():
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'ho:s:i:g:a:m:', ['help', 'ontology', 'similarity', 'shared-info',
                                                                  'graph', 'annotations', 'matrix-file'])
    except getopt.GetoptError as err:
        print str(err)
        print_usage()
        sys.exit(2)

    ontology = None
    sim_type = None
    si_type = None
    graph_file = None
    annotation_file = None
    matrix_file = None

    if len(opts) == 0:
        print_usage()
        sys.exit(1)

    for opt, arg in opts:
        if opt in ('-h', '-help', '--help'):
            print_usage()
            sys.exit(1)
        elif opt in ('-o', '--ontology'):
            ontology = arg
        elif opt in ('-s', '--similarity'):
            sim_type = arg
        elif opt in ('-i', '--shared-info'):
            si_type = arg
        elif opt in ('-g', '--graph'):
            graph_file = arg
        elif opt in ('-a', '--annotations'):
            annotation_file = arg
        elif opt in ('-m', '--matrix-file'):
            matrix_file = arg
        else:
            print_usage("Error: Option %s non recognized" % opt)
            sys.exit(1)

    if not ontology:
        print_usage('ERROR No Ontology: an ontology must be specified bp, mf, cc')
        sys.exit(1)
    elif ontology not in valid_ontology_types:
        print_usage('ERROR %s not a valid ontology: an ontology must be specified bp, mf, cc' % ontology)
        sys.exit(1)

    if not sim_type:
        print_usage('ERROR No Similarity Type: a similarity type must be specified %s' % str(valid_similarity_types))
        sys.exit(1)
    elif sim_type not in valid_similarity_types:
        print_usage('ERROR %s not a valid similarity type: a similarity type must be specified %s' %
                    (sim_type, str(valid_similarity_types)))
        sys.exit(1)

    if not si_type:
        print_usage('ERROR No Shared Information Type: a shared information type must be specified %s' %
                    str(valid_si_types))
        sys.exit(1)
    elif si_type not in valid_si_types:
        print_usage('ERROR %s not a valid similarity type: a similarity type must be specified %s' %
                    (si_type, str(valid_si_types)))
        sys.exit(1)

    if not graph_file:
        print_usage('ERROR No graph file: a GO graph file must be specified')
        sys.exit(1)

    if not annotation_file:
        print_usage('ERROR No annotation file: a GO annotaiton file must be specified')
        sys.exit(1)

    if not matrix_file:
        print_usage('ERROR No Matrix file: a matrix file must be specified')
        sys.exit(1)

    return ontology, sim_type, si_type, graph_file, annotation_file, matrix_file

def load_graph(filename):
    if filename.find('obo-xml') > 0:
        return ggtk.GoParser.parse(filename, 'xml')
    else:
        return ggtk.GoParser.parse(filename, 'obo')

def build_sim_method(sim_type, si_type, graph, annotations):
    ic_map = ggtk.TermMaps.TermInformationContentMap(graph, annotations)

    if si_type == 'casi':
        shared_info = ggtk.TermSimilarity.AncestorMeanSharedInformation(graph, ic_map)
    elif si_type == 'mica':
        shared_info = ggtk.TermSimilarity.MICASharedInformation(graph, ic_map)
    elif si_type == 'grasm':
        shared_info = ggtk.TermSimilarity.CoutoGraSMSharedInformation(graph, ic_map)
    elif si_type == 'agrasm':
        shared_info = ggtk.TermSimilarity.CoutoGraSMAdjustedSharedInformation(graph, ic_map)
    elif si_type == 'sf':
        shared_info = ggtk.TermSimilarity.FrontierSharedInformation(graph, ic_map)
    else:
        shared_info = ggtk.TermSimilarity.MICASharedInformation(graph, ic_map)

    if sim_type == 'res':
        similarity = ggtk.TermSimilarity.ModularResnik(shared_info)
    elif sim_type == 'lin':
        similarity = ggtk.TermSimilarity.ModularLin(shared_info)
    elif sim_type == 'jc':
        similarity = ggtk.TermSimilarity.ModularJiangConrath(shared_info)
    else:
        similarity = ggtk.TermSimilarity.ModularResnik(shared_info)

    return similarity


def main():
    ontology, sim_type, si_type, graph_file, annotation_file, matrix_file = process_and_validate_arguments()
    graph = load_graph(graph_file)
    annotations = ggtk.AnnotationParser.parse(annotation_file)

    similarity = build_sim_method(sim_type, si_type, graph, annotations)
    writer = ggtk.TermSimilarity.TermSimilarityWriter(graph, annotations)

    if ontology == 'bp':
        writer.writeSimilarityMatrixBP(similarity, matrix_file)
    elif ontology == 'mf':
        writer.writeSimilarityMatrixMF(similarity, matrix_file)
    elif ontology == 'cc':
        writer.writeSimilarityMatrixCC(similarity, matrix_file)

if __name__ == '__main__':
    main()

