/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ANNOTATION_PARSER_INTERFACE
#define ANNOTATION_PARSER_INTERFACE

#include <ggtk/AnnotationData.hpp>

/*! \class AnnotationParserInterface
	\brief An interface class to define annotation parsers

	This class defines the interface of an annotation parser. Pure virtual methods
	  require that parsers implement these methods.

*/
class AnnotationParserInterface{
public:
	//! A pure virtual method for parsing the file and returning an AnnotationData object.
	/*!
		This pure virtual method requires any parser to have a method that takes
		  a filename string and returns an AnnotationData object pointer.
	*/
	virtual AnnotationData* parseAnnotationFile(std::string fileName) = 0;

	//! A pure virtual method for checking if a file exists and is formatted correctly.
	/*!
		This pure virtual function delegates format checking to the implementing class.
	*/
	virtual bool isFileGood(const std::string &fileName) = 0;

	//! A pure virtual clone function for factory pattern
	/*!
		This pure virtual method returns an instance of this interface. This method
		  is used in a factory class to have the ability to decide the parser at runtime.
	*/
	virtual AnnotationParserInterface* clone() = 0;
};
#endif
