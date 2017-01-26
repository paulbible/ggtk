#!/bin/env python
import sys
import getopt
import ggtk
import ggtk.TermSimilarity
from ggtk.TermMaps import TermInformationContentMap
from ggtk.TermSetSimilarity import SimUISetSimilarity
from ggtk.TermSetSimilarity import SimGICSetSimilarity
from ggtk.TermSetSimilarity import SimDICSetSimilarity
from ggtk.TermSetSimilarity import SimUICSetSimilarity

sim_type_set = {'ui', 'gic', 'dic', 'uic'}


def print_usage(msg=''):
    if len(msg) != 0:
        print msg
    print 'usage: calculate_gene_similarity_matrix_simUI.py -o ontology -e entity_file -g graph_file -a annotation_file' \
          ' -m output_file -k output_file'
    print
    print 'This scripts writes the gene similarity matrix for a list of entities based on a' \
          ' PrecomputedMatrixTermSimilarity'
    print
    print ' -h                               Print this help information'
    print ' -o <ontology>                    One of {bp, mf, cc}'
    print ' -e <entity_file>                 An entity file. Any tab delimited file with ids in the first column'
    print ' -g <graph_file>                  A graph-file (go-basic.obo-xml)'
    print ' -a <annotation_file>             An annotation file in GAF format.'
    print ' -t <sim_type>                    The type of similarity method to use. One of the following:'
    print '                                    ui: the SimUI method by Gentleman et al. 2006 (Similar to Jaccard)'
    print '                                    gic: the SimGIC method by Pesquita et al. 2007 (IC weighted SimUI)'
    print '                                    dic: the SimDIC method by Mazandu et al. 2014 (Variation of SimGIC)'
    print '                                    uic: the SimUIC method by Mazandu et al. 2014 (Variation of SimGIC)'
    print ' -k <output_ile>                  The output similarity matrix (kernel) for the genes.'

valid_ontology_types = ('bp', 'mf', 'cc')
valid_similarity_types = ('res', 'lin', 'jc')
valid_si_types = ('casi', 'mica', 'grasm', 'agrasm', 'sf')


def process_and_validate_arguments():
    try:
        opts, args = getopt.getopt(sys.argv[1:], 'ho:e:g:a:t:k:', ['help', 'ontology', 'entities',
                                                                   'graph', 'annotations', 'type', 'output'])
    except getopt.GetoptError as err:
        print str(err)
        print_usage()
        sys.exit(2)

    ontology = None
    entity_file = None
    graph_file = None
    annotation_file = None
    sim_type = None
    output_file = None

    if len(opts) == 0:
        print_usage()
        sys.exit(1)

    for opt, arg in opts:
        if opt in ('-h', '-help', '--help'):
            print_usage()
            sys.exit(1)
        elif opt in ('-o', '--ontology'):
            ontology = arg
        elif opt in ('-e', '--entities'):
            entity_file = arg
        elif opt in ('-g', '--graph'):
            graph_file = arg
        elif opt in ('-a', '--annotations'):
            annotation_file = arg
        elif opt in ('-t', '--type'):
            sim_type = arg
        elif opt in ('-k', '--output'):
            output_file = arg
        else:
            print_usage("Error: Option %s non recognized" % opt)
            sys.exit(1)

    if not ontology:
        print_usage('ERROR No Ontology: an ontology must be specified bp, mf, cc')
        sys.exit(1)
    elif ontology not in valid_ontology_types:
        print_usage('ERROR %s not a valid ontology: an ontology must be specified bp, mf, cc' % ontology)
        sys.exit(1)

    if not entity_file:
        print_usage('ERROR No entity file: an entity file of gene identifiers must be specified.')
        sys.exit(1)

    if not graph_file:
        print_usage('ERROR No graph file: a GO graph file must be specified')
        sys.exit(1)

    if not annotation_file:
        print_usage('ERROR No annotation file: a GO annotation file must be specified')
        sys.exit(1)

    if not sim_type:
        print_usage('ERROR No Similarity type: Please specify the similarity type with \'-t <sim_type>\'')
        sys.exit(1)
    elif sim_type not in sim_type_set:
        print_usage('ERROR Similarity type \'%s\': The similarity type must be one of %s' % (sim_type, sim_type_set))
        sys.exit(1)

    if not output_file:
        print_usage('ERROR No output file: an output kernel file must be specified, -k <output_file>')
        sys.exit(1)

    return ontology, entity_file, graph_file, annotation_file, sim_type, output_file


def load_graph(filename):
    if filename.find('obo-xml') > 0:
        return ggtk.GoParser.parse(filename, 'xml')
    else:
        return ggtk.GoParser.parse(filename, 'obo')


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


def parse_entity_file(filename):
    entities = []
    with open(filename) as f:
        for line in f:
            entities.append(line.strip().split('\t')[0])
    return entities


def make_matrix(size):
    matrix = []
    for i in range(size):
        matrix.append([0 for j in range(size)])
    return matrix


def write_table(entities, table, filename):
    def vec_to_string(vec):
        return [str(val) for val in vec]
    with open(filename, 'w') as fout:
        for i in range(len(entities)):
            outs = [entities[i]]
            outs.extend(vec_to_string(table[i]))
            fout.write('\t'.join(outs) + '\n')


def main():
    ontology, entity_file, graph_file, annotation_file, sim_type, output_file = process_and_validate_arguments()

    graph = load_graph(graph_file)
    annotations = ggtk.AnnotationParser.parse(annotation_file)
    similarity = get_similarity_calculator(sim_type, graph, annotations)

    entities = list(set(parse_entity_file(entity_file)))
    data_matrix = make_matrix(len(entities))

    for i in range(len(entities)):
        gene_a = entities[i]
        terms_a = get_terms_for_gene(gene_a, ontology, graph, annotations)
        for j in range(i, len(entities)):
            gene_b = entities[j]
            terms_b = get_terms_for_gene(gene_b, ontology, graph, annotations)
            sim_value = similarity.calculateSimilarity(terms_a, terms_b)
            data_matrix[i][j] = sim_value
            data_matrix[j][i] = sim_value

    write_table(entities, data_matrix, output_file)

if __name__ == '__main__':
    main()
