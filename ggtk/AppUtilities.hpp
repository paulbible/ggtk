/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef APP_UTILITIES
#define APP_UTILITIES

#include <iostream>                         // for std::cout
#include <fstream>
#include <vector>
#include <map>

#include <boost/tokenizer.hpp>
#include <boost/unordered_set.hpp>

//! The AppUtilities namespace provides utility functions that facilitate application creation and integration.
/*!
	This namespace defines free functions that aid in constructing applicaitons using this tool kit.
	The main use for this name space is to construct and check the validity of paramaters used as intput
	to GO applicaitons and to provide certain container converstion (vector -> set etc.).
*/
namespace AppUtilities{

	//! A method for parsing a parameter file
	/*!
		This method parses a tab delimited parameter file and returns a map of parameters.
	*/
	inline void parseParamFile(const std::string fname,std::map<std::string,std::string> &paramMap){
		std::ifstream in(fname.c_str());
		std::string line;

		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> tab_sep("\t","");
		tokenizer::iterator it;

		while(in.good()){
			getline(in,line);

			//split tokens with tab,put iterator at first token start
			tokenizer tokens(line,tab_sep);
			it = tokens.begin();
			if(it == tokens.end()){continue;}

			std::string key = *it;
			++it;
			std::string value = *it;
			paramMap[key] = value;
		}
		in.close();
	}

	//! A method for checking the parameters loaded in a map
	/*!
		This method checks the existence of specific keys in the parameter map.
		If all specified keys exist, true is returned. Otherwise false is returned
		and specific error messages are placed int the message parameter.
	*/
	inline bool checkParams(const std::map<std::string,std::string> &paramMap,
		                    const std::vector<std::string> &params,
							std::string &message)
	{
		bool isValid = true;
		for(size_t i = 0; i < params.size(); ++i){
			if(paramMap.find(params.at(i)) == paramMap.end()){
				isValid = false;
				message.append("Paramter " + params.at(i) + " is missing.\n");
			}
		}
		return isValid;
	}

	//! A method for extracting a comma separated string of paramters
	/*!
		This method checks provides an easy method for inputing a list of madatory params
		 to be checked with checkParams
	*/
	inline std::vector<std::string> paramList(std::string param_str){
		//extract params and place in a vector
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> comma_sep(",","");
		tokenizer::iterator it;

		std::vector<std::string> params;

		tokenizer tokens(param_str,comma_sep);
		for(it = tokens.begin(); it != tokens.end(); ++it){
			params.push_back(*it);
		}
		return params;
	}

	//! A method for parsing a simple single column file
	/*!
		This method parses a simple single column file.
	*/
	inline std::vector<std::string> parseSimpleFile(const std::string fname){
		std::ifstream in(fname.c_str());
		std::vector<std::string> strs;
		std::string line;
		while(in.good()){
			getline(in,line);
			if(line.size() > 0){
				strs.push_back(line);
			}
		}
		in.close();
		return strs;
	}

	//! A method to split a string and return the nth element
	/*!
		This method splits a string by the given character and return the element at n.
	*/
	inline std::string splitTake(const std::string &name, const char &sep, const size_t &n){
		
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

		boost::char_separator<char> arb_sep(&sep,"");
		//split string
		tokenizer tokens(name,arb_sep);
		tokenizer::iterator it;
		it = tokens.begin();
		if(it == tokens.end()){return "";}

		size_t c = 0;
		while(c < n && it != tokens.end()){
			++it;
			++c;
		}

		if(it == tokens.end()){
			return "";
		}else{
			return *it;
		}
	}

	//! A method to split a string and return the nth element
	/*!
		This method splits a string by the given character and return the element at n.
	*/
	inline std::vector< std::string > setToVec(const boost::unordered_set< std::string > &uset){
		std::vector<std::string> vec;
		vec.reserve(uset.size());
		boost::unordered_set<std::string>::iterator it;
		it = uset.begin();
		for(;it != uset.end(); ++it){
			vec.push_back(*it);
		}
		return vec;
	}

	//! A method to split a string and return the nth element
	/*!
	This method splits a string by the given character and return the element at n.
	*/
	inline boost::unordered_set< std::string > vecToSet(const std::vector< std::string > &vec){
		boost::unordered_set< std::string > uset;
		std::vector<std::string>::const_iterator it;
		it = vec.begin();
		for (; it != vec.end(); ++it){
			uset.insert(*it);
		}
		return uset;
	}

};
#endif
