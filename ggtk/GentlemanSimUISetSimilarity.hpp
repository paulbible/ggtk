/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GENTLEMAN_SIMUI_SET_SIMILARITY
#define GENTLEMAN_SIMUI_SET_SIMILARITY

#include <ggtk/TermSetSimilarityInterface.hpp>
#include <ggtk/SetUtilities.hpp>
#include <ggtk/GoGraph.hpp>


/*! \class GentlemanSimUISetSimilarity
	\brief A class to calculate Gentleman's UI similarity between go terms for 2 sets.

	Gentlman R. Visualizing and Distances Using GO. URL http://www.bioconductor.org/docs/vignettes.html.

*/
class GentlemanSimUISetSimilarity : public TermSetSimilarityInterface{

public:
	//! Constructor
	/*!
		Creates the GentlemanUISimilarity class assigning the GoGraph private memeber.
	*/
	inline GentlemanSimUISetSimilarity(GoGraph* graph){
		_graph = graph;
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

		//if the union is 0, return 0. No division by 0.
		if (union_set.size() == 0){
			return 0.0;
		}
		else{
			return (double)intersection_set.size() / union_set.size();
		}
	}

private:

	//! Pointer to the GoGraph object
	/*!
		A reference to GO graph to be used.
	*/
	GoGraph* _graph;


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
