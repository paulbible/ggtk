#==============================================================================
#  Copyright (c) 2016 Paul W. Bible
#
#  Distributed under the Boost Software License, Version 1.0. (See accompanying
#  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#==============================================================================
"""
The _AnnotationData module encapsulates the AnnotationData class
"""

import app_utilities
import go_enums

class AnnotationData:
    """
    AnnotationData class, a more friendly python wrapper for the C++ AnnotationData class.
    This class should not be instatiated by the user. It is returned by AnnotationParser functions.
    The AnnotationData serves as a database that connects biological entities to GO annotations.
    """
    def __init__(self, anno_data_swig_proxy):
	self.data = anno_data_swig_proxy

    def getNumGenes(self):
        """
        Return the number of genes referenced in the annotaiton database.
        """
        return self.data.getNumGenes()

    def getNumGoTerms(self):
        """
        Return the number of GO terms referenced in the annotaiton database.
        """
        return self.data.getNumGoTerms()

    def hasGene(self, gene_name):
        """
        Determine if the gene exists in the database.
        """
        return self.data.hasGene(gene_name)

    def hasGoTerm(self, go_term):
        """
        Determine if the GO term exists in the datbase.
        """
        return self.data.hasGoTerm(go_term)

    def getAllGoTerms(self):
        """
        Returns all the GO terms with annotations in the database.
        """
        return self.data.getAllGoTerms()

    def getAllGenes(self):
        """
        Returns all genes in the database.
        """
        return self.data.getAllGenes()

    def getNumAnnotationsForGene(self, gene_name):
        """
        Return the number of GO terms annotated to a gene.
        """
        return self.data.getNumAnnotationsForGene(gene_name)

    def getNumAnnotationsForGoTerm(self, go_term):
        """
        Return the number of genes annotated annotated with a GO term.
        """
        return self.data.getNumAnnotationsForGoTerm(go_term)

    def getGoTermsForGene(self, gene_name):
        """
        Return a list of GO terms annotated to the given gene.
        """
        return self.data.getGoTermsForGene(gene_name)

    def getGenesForGoTerm(self, go_term):
        """
        Return a list of genes annotated with the given gene.
        """
        return self.data.getGenesForGoTerm(go_term)

    def getGoTermsEvidenceForGene(self, gene_name):
        """
        Return a list of evidence types corresponding to the annotation of each GO term.
        The list is the same length as the returned GO term list.
        """
        return self.data.getGoTermsEvidenceForGene(gene_name)

    def getGenesEvidenceForGoTerm(self, go_term):
        """
        Return a list of evidence types corresponding to the annotation of each gene to this term.
        The list is the same length as the returned gene list.
        """
        return self.data.getGenesEvidenceForGoTerm(go_term)

    def getGoTermsForGeneBP(self, gene_name, go_graph):
        """
        Return a list of biological process GO terms for a gene.
        """
        return app_utilities.setToVec(self.data.getGoTermsForGeneBP(gene_name, go_graph.graph))

    def getGoTermsForGeneMF(self, gene_name, go_graph):
        """
        Return a list of molecular function GO terms for a gene.
        """
        return app_utilities.setToVec(self.data.getGoTermsForGeneMF(gene_name, go_graph.graph))

    def getGoTermsForGeneCC(self, gene_name, go_graph):
        """
        Return a list of cellular component GO terms for a gene.
        """
        return app_utilities.setToVec(self.data.getGoTermsForGeneCC(gene_name, go_graph.graph))














