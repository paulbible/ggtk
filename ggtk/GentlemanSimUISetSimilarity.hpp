/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GENTLEMAN_UI_SIMILARITY
#define GENTLEMAN_UI_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>


/*! \class GentlemanUISimilarity
	\brief A class to calculate Gentleman's UI similarity between go terms for 2 sets.

	This is a stub.

*/
class GentlemanUISimilarity : public TermSetSimilarityInterface{

public:
	//! Constructor
	/*!
		Creates the GentlemanUISimilarity class assigning the similarity measure private memeber.
	*/
	inline GentlemanUISimilarity(TermSimilarityInterface* simMeasure){
		_similarity = simMeasure;
	}


	//! A method for calculating term set to term set similarity for GO terms;
	/*!
		This method returns the best match average similarity.
	*/
	inline double calculateSimilarity(boost::unordered_set<std::string> termsA, boost::unordered_set<std::string> termsB){

		//get mean accumulator
		MeanAccumulator simMean;

		//get iterators
		boost::unordered_set<std::string>::iterator aTermIter;
		boost::unordered_set<std::string>::iterator bTermIter;


		//Have to calculate the best match for term in A to terms in B

		//average for best matches
		MeanAccumulator meanA;

		//iterate A set
		for(aTermIter = termsA.begin(); aTermIter != termsA.end(); ++aTermIter){

			//get term from A set
			std::string aTerm = *aTermIter;


			//get best match value
			MaxAccumulator maxForTermA;

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
			meanA(boost::accumulators::max(maxForTermA));
		}

		//Have to calculate the best match for term in B to terms in A
		// then take the average of both so the relationship is symmetric

		//average for best matches
		MeanAccumulator meanB;

		//iterate A set
		for(bTermIter = termsB.begin(); bTermIter != termsB.end(); ++bTermIter){

			//get term from A set
			std::string bTerm = *bTermIter;

			//get best match value
			MaxAccumulator maxForTermB;

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
			meanB(boost::accumulators::max(maxForTermB));
		}

		//return the avearage of the 2 means from our accumulator
		return (boost::accumulators::mean(meanA) + boost::accumulators::mean(meanB))/2.0;
	}

private:

	//! Pointer to the actual similarity measure
	/*!
		This object will actually calculate the similarity between pairs of terms.
	*/
	TermSimilarityInterface* _similarity;

	//! typedef of a boost accumulator calculating the mean of double values
	/*!
		A boost accumulator to calculate mean. This is hidden in a typedef to
		  promote readabilbity
	*/
	typedef boost::accumulators::accumulator_set< double, boost::accumulators::stats<
			boost::accumulators::tag::mean> > MeanAccumulator;

	//! typedef of a boost accumulator calculating the max of double values
	/*!
		A boost accumulator to calculate max. This is hidden in a typedef to
		  promote readabilbity
	*/
	typedef boost::accumulators::accumulator_set< double, boost::accumulators::stats<
			boost::accumulators::tag::max> > MaxAccumulator;

};
#endif
