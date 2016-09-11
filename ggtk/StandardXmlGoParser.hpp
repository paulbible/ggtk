/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef STANDARD_XML_GO_PARSER
#define STANDARD_XML_GO_PARSER

#include <ggtk/GoParserInterface.hpp>
#include <ggtk/GoEnums.hpp>
#include <ggtk/RelationshipPolicyInterface.hpp>
#include <ggtk/StandardRelationshipPolicy.hpp>
#include <ggtk/AllowedRelationshipXmlGoParser.hpp>

#include <vector>
#include <string>

#include <ggtk/xml/rapidxml_utils.hpp>
#include <ggtk/xml/rapidxml.hpp>

#include <boost/tokenizer.hpp>


/*! \class StandardXmlGoParser
	\brief A class to parse only is_a or part_of relationships

	 Implements GoParserInterface

*/
class StandardXmlGoParser : public GoParserInterface{

public:


	//! Method to parse the go file, should be an XML file
	/*!
		This method will read a Gene Ontology XML file and add only those relationship
		 which are specified to the graph.

	*/
	inline GoGraph* parseGoFile(std::string filename){
		return _parser->parseGoFile(filename);
	}//end method parseGoFile

	//! A method to test if a file fits the accepted format
	/*!
	Returns true if the file matches accepted format, false otherwise
	*/
	inline bool isFileGood(const std::string &filename){
		return _parser->isFileGood(filename);
	}

	//! a method to create a new instance of this class for use in a factory
	/*!
		creats a new pointer to the parser, used by the factory for go parsers.
	*/
	inline GoParserInterface* clone(){
		return new StandardXmlGoParser();
	}//end method clone

	//! A parameterized constructor
	/*!
		constructor that sets the policy
	*/
	inline StandardXmlGoParser(){
		_policy = new StandardRelationshipPolicy();
		_parser = new AllowedRelationshipXmlGoParser(_policy);

	}//end parameterized constructor, StandardXmlGoParser


private:
	AllowedRelationshipXmlGoParser* _parser;
	StandardRelationshipPolicy* _policy;

};
#endif
