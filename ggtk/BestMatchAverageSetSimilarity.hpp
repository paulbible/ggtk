/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BEST_MATCH_AVERAGE_SIMILARITY
#define BEST_MATCH_AVERAGE_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>
#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/Accumulators.hpp>

/*! \class BestMatchAverageSetSimilarity
	\brief A class to calculate the best match average similarity between go terms for 2 sets.

	This class defines the best match average similarity getween two sets of terms.
	Used by Couto et al.

	F. M. Couto, M. J. Silva, and P. M. Coutinho, "Measuring semantic similarity
	between Gene Ontology terms," Data & Knowledge Engineering, vol. 61, 
	pp. 137-152, Apr 2007.
*/
class BestMatchAverageSetSimilarity : public TermSetSimilarityInterface{

public:
	//! Constructor
	/*!
		Creates the BestMatchAverageSetSimilarity class assigning the similarity measure private memeber.
	*/
	BestMatchAverageSetSimilarity(TermSimilarityInterface* simMeasure){
		_similarity = simMeasure;
	}

	//! A method for calculating term set to term set similarity for GO terms;
	/*!
		This method returns the best match average similarity.
	*/
	inline double calculateSimilarity(const boost::unordered_set<std::string> &termsA, const boost::unordered_set<std::string> &termsB){

		//return 0 if a set is empty
		if(termsA.size() == 0 || termsB.size() == 0){
			return 0.0;
		}

		//get mean accumulator
		Accumulators::MeanAccumulator simMean;

		//average for best matches
		Accumulators::MeanAccumulator meanA;

		//Have to calculate the best match for term in A to terms in B
		//get iterators
		boost::unordered_set<std::string>::iterator aTermIter;
		boost::unordered_set<std::string>::iterator bTermIter;
		//iterate A set
		for(aTermIter = termsA.begin(); aTermIter != termsA.end(); ++aTermIter){
			//get term from A set
			std::string aTerm = *aTermIter;
			//get best match value
			Accumulators::MaxAccumulator maxForTermA;
			//iterate B terms
			for(bTermIter = termsB.begin(); bTermIter != termsB.end(); ++bTermIter){
				//get the term from B set
				std::string bTerm = *bTermIter;
				double sim = _similarity->calculateNormalizedTermSimilarity(aTerm,bTerm);
				//std::cout << aTerm << " " << bTerm << " " << sim << std::endl;

				//add to accumulator
				maxForTermA(sim);
			}
			//add to accumulator
			meanA(Accumulators::extractMax(maxForTermA));
		}

		//std::cout << "--" << std::endl;

		//Have to calculate the best match for term in B to terms in A
		// then take the average of both so the relationship is symmetric
		//average for best matches
		Accumulators::MeanAccumulator meanB;
		//iterate A set
		for(bTermIter = termsB.begin(); bTermIter != termsB.end(); ++bTermIter){
			//get term from A set
			std::string bTerm = *bTermIter;
			//get best match value
			Accumulators::MaxAccumulator maxForTermB;
			//iterate B terms
			for(aTermIter = termsA.begin(); aTermIter != termsA.end(); ++aTermIter){
				//get the term from B set
				std::string aTerm = *aTermIter;
				double sim = _similarity->calculateNormalizedTermSimilarity(aTerm,bTerm);
				//std::cout << aTerm << " " << bTerm << " " << sim << std::endl;

				//add to accumulator
				maxForTermB(sim);
			}
			//add to accumulator
			meanB(Accumulators::extractMax(maxForTermB));
		}

		//return the avearage of the 2 means from our accumulator
		return (Accumulators::extractMean(meanA) + Accumulators::extractMean(meanB))/2.0;
	}

private:
	//! Pointer to the actual similarity measure
	/*!
		This object will actually calculate the similarity between pairs of terms.
	*/
	TermSimilarityInterface* _similarity;
};
#endif
