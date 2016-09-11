/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef JACCARD_SET_SIMILARITY
#define JACCARD_SET_SIMILARITY

#include <ggtk/SetUtilities.hpp>
#include <ggtk/TermSetSimilarityInterface.hpp>

#include <boost/unordered_set.hpp>

/*! \class JaccardSetSimilarity
	\brief A class to calculate jaccard similarity between 2 sets.

	This class calculates jaccard set similarity between two sets of terms.

*/
class JaccardSetSimilarity : public TermSetSimilarityInterface{

public:

	//! Constructor
	/*!
		Creates the JaccardSetSimilarity class.
	*/
	JaccardSetSimilarity(){
	}


	//! A method for calculating term set to term set similarity for GO terms;
	/*!
		This method returns the Jaccard set similarity.
	*/
	inline double calculateSimilarity(const boost::unordered_set<std::string> &termsA, const boost::unordered_set<std::string> &termsB){

		//return 0 if a set is empty
		if(termsA.size() == 0 || termsB.size() == 0){
			return 0.0;
		}

		//get iterators
		boost::unordered_set<std::string>::iterator shortSetIter;

		boost::unordered_set<std::string> _union = SetUtilities::set_union(termsA,termsB);
		boost::unordered_set<std::string> _intersection = SetUtilities::set_intersection(termsA,termsB);

		if(_union.size() == 0){
			return 0.0;
		}else{
			return (double)_intersection.size()/_union.size();
		}
	}

};
#endif
