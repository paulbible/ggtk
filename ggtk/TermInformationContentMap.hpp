/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef TERM_INFORMATION_CONTENT_MAP
#define TERM_INFORMATION_CONTENT_MAP

#include <cmath>

#include <ggtk/GoGraph.hpp>
#include <ggtk/AnnotationData.hpp>
#include <ggtk/TermProbabilityMap.hpp>


/*! \class TermInformationContentMap
	\brief A class to calculate the information content of a GO term.

	This class provides a map that returns the information content of a GO term. This
	  class is used by Information Content methods.

*/
class TermInformationContentMap: public TermProbabilityMap{
public:
	//! A parameterized constructor
	/*!
		This constructor takes pointers to GoGraph and AnnotationData objects.
		  Only the parameterized construtor is allowed to ensure these objects are
		  created with valid parameters.
		  This constructor relies on the TermProbabilityMap.
	*/
	inline TermInformationContentMap(GoGraph* graph,AnnotationData* annoData)
	:TermProbabilityMap(graph,annoData)
	{
		//convert term probability to information content
		for(size_t i = 0; i < _probabilities.size(); ++i){
			_probabilities.at(i) = -std::log(_probabilities.at(i));
		}//end for, each probability value
	}

	//! Return a default value for a term that does not exist.
	/*!
	A value to return if the term is not found (does not exist in the map).
	Returns informaiton content 0. This may not be the ideal behavior.
	*/
	inline double badIdValue(){
		return 0.0;
	}

	//! A default constructor
	/*!
		This constructor creates an empty IC map. Should not be used.
	*/
	inline TermInformationContentMap(){}

};
#endif

