/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GO_PARSER_FACTORY
#define GO_PARSER_FACTORY

#include <ggtk/GoParserInterface.hpp>

#include <vector>
#include <string>


/*! \class GoParserFactory
	\brief A class to return an instance of GoParserInterface at runtime based on an argument.

	This class holds a set of parser classes. When queried using the getParser method, it
	  returns an instance of GoParserInterface based on a string key. This allows
	  parsers to be easily added to a larger system and switched at runtime.

*/
class GoParserFactory{

private:
	//! A list of strings which correspond to parsers
	/*!
		This list holds the names of parsers added to the factory. These are the
		  keys used to query a parser.
	*/
	std::vector<std::string> _names;

	//! A list of parsers which are currently held in the factory.
	/*!
		This list holds the instances of GoParserInterface that can be returned.
	*/
	std::vector<GoParserInterface*> _parsers;

public:

	//! Class constructor
	/*!
		This constructor initializes the private lists to empty vectors.
	*/
	inline GoParserFactory(){
		//initialize vectors
		_names   = std::vector<std::string>();
		_parsers = std::vector<GoParserInterface*>();
	}//end Constructor

	//! Class destructor
	/*!
		This destructor clears the names vector. It also deletes each parser pointer explicitly.
		  Finally it clears the parser list.
	*/
	inline ~GoParserFactory(){
		//clear vectors
		_names.clear();

		//explicitly delete internal pointers
		for(std::size_t i = 0; i < _parsers.size();++i){
			delete _parsers.at(i);
		}
		_parsers.clear();

	}//end destructor


	//! A Method to add a parser to the factory.
	/*!
		This method adds a pointer to a parser and a string to the factory.
		  This string is used to query the appropriate parser.
	*/
	inline void addParser(std::string name,GoParserInterface* parser){
		_names.push_back(name);
		_parsers.push_back(parser);
	}//end method addParser


	//! A method to return a parser based on a query string.
	/*!
		If the string supplied matches one of the keys in the database, the
		 appropriate parser will be returned. If not, a NULL pointer is returned.
		 The calling environment must check against NULL before using.
	*/
	inline GoParserInterface* getParser(std::string name){
		//check for the string
		for(std::size_t i = 0; i < _names.size(); ++i){
			if(_names.at(i).compare(name) == 0){
				return _parsers.at(i)->clone();
			}
		}
		//if not found return null
		return NULL;
	}//end method getParser

};
#endif