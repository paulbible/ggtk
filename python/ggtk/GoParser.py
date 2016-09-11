'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
"""
The GoParsers module provides a means for parsing different type of Gene Ontology graphs.
"""
import go_parsers
import _GoGraph
from exceptions import IOError, ValueError

def parse(fname, format, relationships=None):
    """
    Parse a Gene Ontology file. Format values are 'obo' and 'xml'.

    If no relationships are give, only the standard is_a and part_of relationshiips will be used.

    Adding a list of relationship strings allows the user
    to select the desired set of relationships to be parsed.

    If relationships is given as a list, the parse will restrict relationships to only those given
    in the list. Should this subset of relationships result in a graph with more or less than
    3 components (BP, MF, CC), an error will be raised.

    Allowed relationship strings are:
    {'is_a',
    'part_of',
    'regulates',
    'positively_regulates',
    'negatively_regulates'}
    """
    if relationships:
        asrp = go_parsers.AllowedSetRelationshipPolicy()
        for val in relationships:
            asrp.addRelationship(val)
        if asrp.isEmpty():
            raise ValueError('GGTK Invalid Relationships: No valid relationships in the set.')
        
        if format == 'obo':
            p = go_parsers.AllowedRelationshipOboGoParser(asrp)
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            graph_proxy = p.parseGoFile(fname)
            num_components = graph_proxy.getNumComponents()
            if num_components != 3:
                raise ValueError('GGTK Relationships Error: 3 graph components expected. %i found.' % num_components)
            return _GoGraph.GoGraph(graph_proxy)

        elif format == 'xml':
            p = go_parsers.AllowedRelationshipXmlGoParser(asrp)
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            graph_proxy =  p.parseGoFile(fname)
            num_components = graph_proxy.getNumComponents()
            if num_components != 3:
                raise ValueError('GGTK Relationships Error: 3 graph components expected. %i found.' % num_components)
            return _GoGraph.GoGraph(graph_proxy)

    else:
        if format == 'obo':
            p = go_parsers.StandardOboGoParser()
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            graph_proxy = p.parseGoFile(fname)
            return _GoGraph.GoGraph(graph_proxy)
        elif format == 'xml':
            p = go_parsers.StandardXmlGoParser()
            if not p.isFileGood(fname):
                raise IOError('GGTK File Error: File not found or incorrectly formatted.')
            graph_proxy =  p.parseGoFile(fname)
            return _GoGraph.GoGraph(graph_proxy)
        else:
            raise ValueError('GGTK Parser Not Defined: No parser of type %s is defined.' % format)

