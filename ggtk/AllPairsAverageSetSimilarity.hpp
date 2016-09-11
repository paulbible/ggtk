/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ALL_PAIRS_AVERAGE_SIMILARITY
#define ALL_PAIRS_AVERAGE_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>
#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/Accumulators.hpp>

/*! \class AllPairsAverageSetSimilarity
	\brief A class to calculate the average similarity between all pairs of go terms for 2 sets.

	This class defines the all pairs average similarity getween two sets of terms.
	Put forth by Lord et al.

	P. W. Lord, R. D. Stevens, A. Brass, and C. A. Goble, "Investigating semantic similarity
	measures across the Gene Ontology: the relationship between sequence and annotation,"
	Bioinformatics, vol. 19, pp. 1275-83, Jul 1 2003.

*/
class AllPairsAverageSetSimilarity : public TermSetSimilarityInterface{
public:
	//! Constructor
	/*!
		Creates the AllPairsAverageSetSimilarity class assigning the similarity measure private memeber.
	*/
	AllPairsAverageSetSimilarity(TermSimilarityInterface* simMeasure){
		_similarity = simMeasure;
	}

	//! A method for calculating term set to term set similarity for GO terms;
	/*!
		This method returns the Relevance similarity.
	*/
	inline double calculateSimilarity(const boost::unordered_set<std::string> &termsA, const boost::unordered_set<std::string> &termsB){
		//return 0 if a set is empty
		if(termsA.size() == 0 || termsB.size() == 0){
			return 0.0;
		}

		//get mean accumulator
		Accumulators::MeanAccumulator simMean;

		//get iterators
		boost::unordered_set<std::string>::iterator aTermIter;
		boost::unordered_set<std::string>::iterator bTermIter;
		//iterate A set
		for(aTermIter = termsA.begin(); aTermIter != termsA.end(); ++aTermIter){
			//get term from A set
			std::string aTerm = *aTermIter;
			//iterate B terms
			for(bTermIter = termsB.begin(); bTermIter != termsB.end(); ++bTermIter){
				//get the term from B set
				std::string bTerm = *bTermIter;
				double sim = _similarity->calculateNormalizedTermSimilarity(aTerm,bTerm);
				//std::cout << aTerm << " " << bTerm << " " << sim << std::endl;

				//add to accumulator
				simMean(sim);
			}
		}
		//return the mean from the accumulator
		return Accumulators::extractMean(simMean);
	}

private:
	//! Pointer to the actual similarity measure
	/*!
		This object will actually calculate the similarity between pairs of terms.
	*/
	TermSimilarityInterface* _similarity;
};
#endif
