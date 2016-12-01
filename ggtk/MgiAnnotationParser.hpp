/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef MGI_ANNOTATION_PARSER
#define MGI_ANNOTATION_PARSER

#include <ggtk/AnnotationParserInterface.hpp>

#include <iostream>
#include <boost/tokenizer.hpp>

/*! \class MgiAnnotationParser
	\brief A class to parse an Mouse Genome Informatics go annotation file.

	This class will read an mgi annotation file and add those annoations to 
	  an AnnotationData class.
	  Available at: ftp://ftp.informatics.jax.org/pub/reports/index.html#go

	  MGI uses GAF format which is GOA.

	 Implements AnnotationParserInterface

*/
class MgiAnnotationParser : public GoaAnnotationParser{

public:
	//! A default constructor method for creating the parser
	/*!
		Creates the parser
	*/
	inline MgiAnnotationParser() : GoaAnnotationParser(){}

	//! A parameterized constructor method for creating the parser with a policy.
	/*!
		Creates the parser with a custom policy
	*/
	inline MgiAnnotationParser(EvidencePolicyInterface* policy) : GoaAnnotationParser(policy){}
};

#endif
