/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef MAZANDU_SIMUIC_SET_SIMILARITY
#define MAZANDU_SIMUIC_SET_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>
#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/SetUtilities.hpp>
#include <ggtk/Accumulators.hpp>
#include <ggtk/GoGraph.hpp>


/*! \class MazanduSimUICSetSimilarity
\brief A class to calculate Mazandu and Mulder's SimUIC similarity between 2 sets of go terms.

A separate measure from their SimDIC.

Mazandu, G. K., & Mulder, N. J. (2014). Information content-based Gene Ontology functional
similarity measures: which one to use for a given biological data type?. PloS one, 9(12), e113859

*/
class MazanduSimUICSetSimilarity : public TermSetSimilarityInterface{

public:
	//! Constructor
	/*!
	Creates the MazanduSimUICSetSimilarity class assigning the GoGraph private memeber.
	*/
	inline MazanduSimUICSetSimilarity(GoGraph* graph, const TermInformationContentMap &icMap){
		_graph = graph;
		_icMap = icMap;
	}


	//! A method for calculating term set to term set similarity for GO terms;
	/*!
	This method returns the best match average similarity.
	*/
	inline double calculateSimilarity(const boost::unordered_set<std::string> &termsA, const boost::unordered_set<std::string> &termsB){
		// Get the induced set of terms for each set
		boost::unordered_set<std::string> inducedTermSetA = getExtendedTermSet(termsA);
		boost::unordered_set<std::string> inducedTermSetB = getExtendedTermSet(termsB);
		// Calculate union and intersection
		boost::unordered_set<std::string> intersection_set = SetUtilities::set_intersection(inducedTermSetA, inducedTermSetB);

		double intersection_sum = calcICSum(intersection_set);
		double setA_sum = calcICSum(inducedTermSetA);
		double setB_sum = calcICSum(inducedTermSetB);


		//if the union is 0, return 0. No division by 0.
		if (setA_sum + setB_sum == 0.0){
			return 0.0;
		}
		else{
			if (setA_sum > setB_sum){
				return intersection_sum / setA_sum;
			}
			else{
				return intersection_sum / setB_sum;
			}
			
		}
	}

private:

	//! Pointer to the GoGraph object.
	/*!
	A reference to GO graph to be used.
	*/
	GoGraph* _graph;

	//! The information content map.
	/*!
	An information content map.
	*/
	TermInformationContentMap _icMap;


	//! A method for calculating the extended term set. The set of all terms in the induced subgraph of the ontology.
	/*!
	This method returns the extended term set of a set of terms. Basically the set of terms and all thier ancestors.
	*/
	inline boost::unordered_set<std::string> getExtendedTermSet(const boost::unordered_set<std::string> &terms){
		boost::unordered_set<std::string> inducedSet;
		boost::unordered_set<std::string>::iterator it, end;
		it = terms.begin();
		end = terms.end();
		for (; it != end; ++it){
			std::string term = *it;
			// add the new terms to the set using union and the ancestors from the go graph.
			inducedSet = SetUtilities::set_union(inducedSet, _graph->getAncestorTerms(term));
			inducedSet.insert(term);
		}
		return inducedSet;
	}

	//! A method for calculating the sum of information content of the terms in a set.
	/*!
		This method calculates the sum of information content of the terms in a set.
	*/
	inline double calcICSum(const boost::unordered_set<std::string> &terms){
		boost::unordered_set<std::string>::iterator it, end;
		it = terms.begin();
		end = terms.end();
		double sum = 0;
		for (; it != end; ++it){
			sum += _icMap[*it];
		}
		return sum;
	}
};
#endif
