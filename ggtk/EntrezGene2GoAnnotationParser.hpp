/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ENTREZ_GENE2GO_ANNOTATION_PARSER
#define ENTREZ_GENE2GO_ANNOTATION_PARSER

#include <ggtk/AnnotationParserInterface.hpp>
#include <iostream>
#include <boost/tokenizer.hpp>


/*! \class EntrezGene2GoAnnotationParser
	\brief A class to parse an Entrez gene2go annotation file.

	This class will read an Entrez gene2go file and add those annoations to 
	  an AnnotationData class.
	  Available at: ftp://ftp.ncbi.nih.gov/gene/DATA/

	 Implements AnnotationParserInterface

*/
class EntrezGene2GoAnnotationParser: public AnnotationParserInterface{

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
			getline(in,line);
			if(line[0]=='#'){continue;}

			//split line
			tokenizer tokens(line,tab_sep);
			//set iterator to first token
			it = tokens.begin();

			//always check if empty (must have in linux)
			if(it == tokens.end()){continue;}
			//iterator at 0

			//temp storage variables
			std::string taxon,geneName,goTerm,evidenceCode;

			//iterator at 0
			//set taxon
			taxon = *it;

			//only use annotations for the specified taxonomy
			//if(taxon.compare(taxonomy) != 0){continue;}

			std::advance(it,1);
			//iterator at 1
			//set gene id
			geneName = *it;

			std::advance(it,1);
			//iterator at 2
			//set go term
			goTerm = *it;

			std::advance(it,1);
			//iterator at 3
			//set evidence code
			evidenceCode = *it;

			//add gene to go association to the database, if the evidence is allowed
			if (_policy->isAllowed(GO::evidenceStringToCode(evidenceCode))){
				//add gene to go association to the database
				annoData->addAssociation(geneName, goTerm, evidenceCode);
			}
		}
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
		boost::char_separator<char> tab_sep("\t", "", boost::keep_empty_tokens);
		tokenizer::iterator it;
		std::string line;

		std::size_t count = 0;

		//main loop, each line
		while (in.good() && count < 5){
			//get next line in 'in' file stream
			getline(in, line);
			if (line[0] == '#'){ continue; }

			//split line
			tokenizer tokens(line, tab_sep);
			//set iterator to first token
			it = tokens.begin();

			//always check if empty (must have in linux)
			if (it == tokens.end()){ continue; }
			//iterator at 0

			//temp storage variables
			std::string taxon, geneName, goTerm, evidenceCode;
			taxon = *it;
			if (taxon.size() == 0){ return false; }

			std::advance(it, 1);
			geneName = *it;
			if (geneName.size() == 0){ return false; }
			
			std::advance(it, 1);
			goTerm = *it;
			if (goTerm.size() == 0){ return false; }           // disallow empty go
			if (goTerm.substr(0, 3) != "GO:"){ return false; } // disallow bad go term

			std::advance(it, 1);
			evidenceCode = *it;
			if (evidenceCode.size() == 0){ return false; }
			if (GO::evidenceStringToCode(evidenceCode) == GO::ECODE_ERROR){ return false; }

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


	//! An interface method for creating a new instance of the parser.
	/*!
		This method returns a new instance of the class. This method partially
		  fulfills the interface contract.
	*/
	inline AnnotationParserInterface* clone(){
		return new EntrezGene2GoAnnotationParser();
	}//end method, AnnotationParserInterface


	//! A parameterized constructor method for creating the parser with a policy.
	/*!
		Creates the parser
	*/
	inline EntrezGene2GoAnnotationParser(EvidencePolicyInterface* policy){
		_policy = policy;
	}


	//! A default constructor method for creating the parser with the default policy.
	/*!
		Creates the parser with the default evidence policy, everything is allowed.
	*/
	inline EntrezGene2GoAnnotationParser(){
		_policy = new DisallowedSetEvidencePolicy();
	}


private:
	EvidencePolicyInterface* _policy;

};
#endif
