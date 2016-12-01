/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ENRICHMENT_TOOLS
#define ENRICHMENT_TOOLS

#include <stdlib.h>

#include <ggtk/AnnotationData.hpp>
#include <ggtk/GoGraph.hpp>
#include <ggtk/SetUtilities.hpp>

#include <boost/math/distributions.hpp>
#include <boost/unordered_map.hpp>

//! The EnrichmentTools namespace provides simple functions for calulating GO term enrichment.
/*!
	This namespace defines free functions that allow enrichment p-values to be calculated.
	These funcitons can serve as the foundation for more sophisticated enrichment anlayis.
*/
namespace EnrichmentTools{

	//! A method for determining which genes are annotated with the given term or a child of that term.
	/*!
		This method calculates the set of the genes annotated with a given term or transatively with a child of that term.
	*/
	inline boost::unordered_set<std::string> getDescendantGenes(GoGraph *go, AnnotationData *data, const std::string &term){
		boost::unordered_set<std::string> descendants = go->getDescendantTerms(term);
		descendants.insert(term);

		boost::unordered_set<std::string>::iterator si;
		boost::unordered_set<std::string> genes;

		for(si = descendants.begin(); si != descendants.end(); ++si){
			std::string currentTerm = *si;
			//std::cout << *si << " " << go->getTermName(*si) << std::endl;
			data->addGenesForGoTerm(currentTerm,genes);
		}
		//std::cout << genes.size() << std::endl;

		return genes;
	};

	//! A method for calculating the result of a hypergeometic test.
	/*!
		This method calculates p-value of a hypergeometice test give 4 values.
		The sample size,         n
		The population success   K
		The the population size  N
		The test value           k

		Answers the question:
		"What is probability of seeing value of k or more successes
		  in a sample of size n, given that the population of size N 
		  contains K total successes."
	*/
	inline double oneSidedRawPvalue_hyper(size_t sample, size_t success,size_t population,size_t test_value){
		double sum = 0.0;
		boost::math::hypergeometric dist(sample,success,population);
		for(size_t i = test_value; i <= sample && i <= success; ++i){
			double prob = boost::math::pdf(dist,i);
			sum += prob;
		}
		return sum;
	};


	//! A method to calculate the enrichment of a specific term in a sample of genes.
	/*!
		This method performs a hypergeometic test of enrichment for a term given
		a set of genes that serves as the sample. The population is taken as all genes
		in the annotation database.
	*/
	inline double enrichmentSignificance(GoGraph *go, AnnotationData *data,
											boost::unordered_set<std::string> &genes,
											const std::string &term)
	{
		boost::unordered_set<std::string> termGenes = getDescendantGenes(go, data, term);
		boost::unordered_set<std::string> sharedGenes = SetUtilities::set_intersection(genes,termGenes);

		if(sharedGenes.size() == 0){
			return 1.0;
		}
		
		size_t sampleSize = genes.size();
		size_t sampleWithTerm = sharedGenes.size();
		size_t populationWithTerm = termGenes.size();
		size_t populationSize = data->getNumGenes();

		return oneSidedRawPvalue_hyper(sampleSize,populationWithTerm,populationSize,sampleWithTerm);
	};


};
#endif
