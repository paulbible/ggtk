'''
  Copyright (c) 2016 Paul W. Bible

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================*/
'''
"""
EnrichmentTools Module
This module defines free functions that allow enrichment p-values 
to be calculated. These funcitons can serve as the foundation
for more sophisticated enrichment anlayis.
"""
import enrichment_tools
import app_utilities

def getDescendantGenes(go_graph, anno_data, go_term):
    """
    This method calculates the set of the genes annotated
    with a given term or transatively with a child of that term.
    """
    return app_utilities.setToVec(enrichment_tools.getDescendantGenes(go_graph.graph, anno_data.data, go_term))
    
def oneSidedRawPvalue_hyper(sample, pop_success, population, test_value):
    """
    This method calculates p-value of a hypergeometice test give 4 values.
    
    The sample size,         n
    The population success   K
    The the population size  N
    The test value           k

    Answers the question:
    "What is probability of seeing value of k or more successes
    in a sample of size n, given that the population of size N 
    contains K total successes."
    """
    return enrichment_tools.oneSidedRawPvalue_hyper(sample, pop_success, population, test_value)

def enrichmentSignificance(go_graph, anno_data, genes, go_term):
    """
    This method performs a hypergeometic test of enrichment for a term
    given a set of genes that serves as the sample. The population is
    taken as all genes in the annotation database.
    """
    gene_set = app_utilities.vecToSet(genes)
    return enrichment_tools.enrichmentSignificance(go_graph.graph, anno_data.data, gene_set, go_term)

