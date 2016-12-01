/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GAF_ANNOTATION_PARSER
#define GAF_ANNOTATION_PARSER

#include <ggtk/GoaAnnotationParser.hpp>

/*! \class GafAnnotationParser
\brief A class to parse a GO Annotation File (GAF, Format 2.0).

This class will read a GAF file and return an AnnotationData object pointer.
Defined at: http://geneontology.org/page/go-annotation-file-format-20

Implements AnnotationParserInterface.

For now, the important aspects of the GAF file and GOA file are the same.
The GafAnnotationParser inherits all functionality from GoaAnnotationParser. This may change in the future.
*/
class GafAnnotationParser : public GoaAnnotationParser{

public:
	//! A default constructor method for creating the parser
	/*!
		Creates the parser
	*/
	inline GafAnnotationParser() : GoaAnnotationParser(){}

	//! A parameterized constructor method for creating the parser with a policy.
	/*!
		Creates the parser with a custom policy
	*/
	inline GafAnnotationParser(EvidencePolicyInterface* policy) : GoaAnnotationParser(policy){}

};

#endif
