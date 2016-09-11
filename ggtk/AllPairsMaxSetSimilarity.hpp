/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ALL_PAIRS_MAX_SIMILARITY
#define ALL_PAIRS_MAX_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>
#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/Accumulators.hpp>

/*! \class AllPairsMaxSetSimilarity
	\brief A class to calculate the max similarity between all pairs of go terms for 2 sets.

	This class defines the all pairs max similarity between two sets of terms.
	Used by Sevilla et al.
	
	J. L. Sevilla, V. Segura, A. Podhorski, E. Guruceaga, J. M. Mato, 
	 L. A. Martinez-Cruz, et al., "Correlation between gene expression and
	 GO semantic similarity," IEEE/ACM Trans Comput Biol Bioinform, 
	 vol. 2, pp. 330-8, Oct-Dec 2005.

*/
class AllPairsMaxSetSimilarity : public TermSetSimilarityInterface{


public:

	//! Constructor
	/*!
		Creates the AllPairsMaxSetSimilarity class assigning the similarity measure private memeber.
	*/
	AllPairsMaxSetSimilarity(TermSimilarityInterface* simMeasure){
		_similarity = simMeasure;
	}


	//! A method for calculating term set to term set similarity for GO terms;
	/*!
		This method returns the all pairs max similarity.
	*/
	inline double calculateSimilarity(const boost::unordered_set<std::string> &termsA, const boost::unordered_set<std::string> &termsB){

		//return 0 if a set is empty
		if(termsA.size() == 0 || termsB.size() == 0){
			return 0.0;
		}

		//get mean accumulator
		Accumulators::MaxAccumulator simMax;

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
				simMax(sim);
			}
		}
		//return the mean from the accumulator
		return Accumulators::extractMax(simMax);
	}

private:
	//! Pointer to the actual similarity measure
	/*!
		This object will actually calculate the similarity between pairs of terms.
	*/
	TermSimilarityInterface* _similarity;
};
#endif
