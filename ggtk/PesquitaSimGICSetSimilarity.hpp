/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PESQUITA_SIMGIC_SET_SIMILARITY
#define PESQUITA_SIMGIC_SET_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>
#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/SetUtilities.hpp>
#include <ggtk/GoGraph.hpp>


/*! \class PesquitaSimGICSetSimilarity
\brief A class to calculate Pesquita's SimGIC similarity between sets of go terms.

Pesquita, C., Faria, D., Bastos, H., Falcao, A., & Couto, F. (2007, July).
Evaluating GO-based semantic similarity measures. In Proc. 10th Annual
Bio-Ontologies Meeting (Vol. 37, No. 40, p. 38).

*/
class PesquitaSimGICSetSimilarity : public TermSetSimilarityInterface{

public:
	//! Constructor
	/*!
	Creates the PesquitaSimGICSetSimilarity class assigning the GoGraph private memeber.
	*/
	inline PesquitaSimGICSetSimilarity(GoGraph* graph, const TermInformationContentMap &icMap){
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
		boost::unordered_set<std::string> union_set = SetUtilities::set_union(inducedTermSetA, inducedTermSetB);
		boost::unordered_set<std::string> intersection_set = SetUtilities::set_intersection(inducedTermSetA, inducedTermSetB);

		double union_sum = 0.0;
		double intersection_sum = 0.0;
		boost::unordered_set<std::string>::iterator it, end;
		// calculate sum for union set
		it = union_set.begin();
		end = union_set.end();
		for (; it != end; ++it){
			union_sum += _icMap[*it];
		}
		// Calculate sum for intersection set
		it = intersection_set.begin();
		end = intersection_set.end();
		for (; it != end; ++it){
			intersection_sum += _icMap[*it];
		}

		//if the union is 0, return 0. No division by 0.
		if (union_sum == 0.0){
			return 0.0;
		}
		else{
			return intersection_sum / union_sum;
		}
	}

private:

	//! Pointer to the GoGraph object
	/*!
	A reference to GO graph to be used.
	*/
	GoGraph* _graph;

	//! The information content map
	/*!
	An information content map
	*/
	TermInformationContentMap _icMap;


	//! A method for calculating the extended term set. The set of all terms in the induced subgraph of the ontology
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
			// add the new terms to the set using union and the ancestors from the go graph
			inducedSet = SetUtilities::set_union(inducedSet, _graph->getAncestorTerms(term));
			inducedSet.insert(term);
		}
		return inducedSet;
	}
};
#endif
