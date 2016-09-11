/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GOA_ANNOTATION_PARSER
#define GOA_ANNOTATION_PARSER

#include <ggtk/AnnotationParserInterface.hpp>
#include <ggtk/EvidencePolicyInterface.hpp>
#include <ggtk/DisallowedSetEvidencePolicy.hpp>

#include <iostream>
#include <boost/tokenizer.hpp>


/*! \class GoaAnnotationParser
	\brief A class to parse a Uniprot Gene Ontolog Annotation (GOA) file.

	This class will read a GOA file an return an AnnotationData object pointer.
	  Defined at: http://www.ebi.ac.uk/GOA

	 Implements AnnotationParserInterface

*/
class GoaAnnotationParser: public AnnotationParserInterface{

public:

	//! An interface method for parsing an annotation file.
	/*!
		This method takes a filename as in put and returns a pointer to an
		  AnnotationData object. This method fulfills part of the interface contract.
	*/
	inline AnnotationData* parseAnnotationFile(std::string filename){
		AnnotationData* annoData = new AnnotationData();

		//open afile stream
		std::ifstream in(filename.c_str());

		//Tokenizer type
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

		//declares a tab separator variable
		boost::char_separator<char> tab_sep("\t","",boost::keep_empty_tokens);

		//An iterator for the tokens
		tokenizer::iterator it;

		//string variable for each line
		std::string line;

		//main loop, each line
		while(in.good()){
			//get next line in 'in' file stream
			std::getline(in,line);

			//split line
			tokenizer tokens(line,tab_sep);
			//set iterator to first token
			it = tokens.begin();

			//always check if empty (must have in linux)
			if(it == tokens.end()){continue;}
			//iterator at 0

			//skip comments if line is not empty and starts with !
			if(line.at(0) == '!'){continue;}


			std::string database,geneName,qualifierStr,goStr,evidenceCode,ontology;

			//database,first field
			database = *it;

			std::advance(it,1);
			//iterator at 1
			geneName = *it;


			std::advance(it,2);
			//iterator at 3
			qualifierStr = *it;


			std::advance(it,1);
			//iterator at 4
			goStr = *it;


			std::advance(it,2);
			//iterator at 6
			evidenceCode = *it;


			std::advance(it,2);
			//iterator at 8
			ontology = *it;


			if(_policy->isAllowed(GO::evidenceStringToCode(evidenceCode))){
				//add gene to go association to the database
				annoData->addAssociation(geneName,goStr,evidenceCode);
			}

		}//end while, each line
		in.close();

		return annoData;
	}


	//! A method for checking if a file exists and is formatted correctly.
	/*!
		This function checks that the file exists and its format can be recognized.
	*/
	inline bool isFileGood(const std::string &fileName){
		std::ifstream in(fileName.c_str());
		if (!in.good()){
			return false;
		}

		//Tokenizer type
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		//declares a tab separator variable
		boost::char_separator<char> tab_sep("\t", "", boost::keep_empty_tokens);
		tokenizer::iterator it;

		std::size_t count = 0;
		std::string line;

		while (in.good() && count < 5){
			//get next line in 'in' file stream
			std::getline(in, line);

			//split line
			tokenizer tokens(line, tab_sep);
			//set iterator to first token
			it = tokens.begin();

			//always check if empty (must have in linux)
			if (it == tokens.end()){ continue; }

			//skip comments if line is not empty and starts with !
			if (line.at(0) == '!'){ continue; }


			std::string database, geneName, qualifierStr, goString, evidenceCode, ontology;
			std::size_t i = 0;
			for (; it != tokens.end(); ++it){
				switch (i)
				{
					case 0:
						database = *it;
						if (database.size() == 0){ return false; }
						break;
					case 1:
						geneName = *it;
						if (geneName.size() == 0){ return false; }
						break;
					case 3:
						qualifierStr = *it;
						break;
					case 4:
						goString = *it;
						if (goString.size() == 0){ return false; }           // disallow empty go
						if (goString.substr(0, 3) != "GO:"){ return false; } // disallow bad go term
						break;
					case 6:
						evidenceCode = *it;
						if (evidenceCode.size() == 0){ return false; }
						if (GO::evidenceStringToCode(evidenceCode) == GO::ECODE_ERROR){ return false;}
						break;
					case 8:
						ontology = *it;
						if (ontology.size() == 0){ return false; }
						break;
					default:
						break;
				}
				++i;
			}

			++count;
		}
		in.close();


		if (count < 5){
			return false;
		}
		else{
			return true;
		}
	}


	//! A parameterized constructor method for creating the parser with a policy.
	/*!
		Creates the parser
	*/
	inline GoaAnnotationParser(EvidencePolicyInterface* policy){
		_policy = policy;
	}


	//! A default constructor method for creating the parser with a policy.
	/*!
		Creates the parser
	*/
	inline GoaAnnotationParser(){
		_policy = new DisallowedSetEvidencePolicy();
	}


	//! An interface method for creating a new instance of the parser.
	/*!
		This method returns a new instance of the class. This method partially
		  fulfills the interface contract.
	*/
	inline AnnotationParserInterface* clone(){
		return new GoaAnnotationParser(_policy);
	}//end method, AnnotationParserInterface

private:
	EvidencePolicyInterface* _policy;

};
#endif
