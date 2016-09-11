/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ALLOWED_RELATIONSHIP_OBO_GO_PARSER
#define ALLOWED_RELATIONSHIP_OBO_GO_PARSER

#include <ggtk/GoParserInterface.hpp>
#include <ggtk/GoEnums.hpp>
#include <ggtk/RelationshipPolicyInterface.hpp>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>


/*! \class AllowedRelationshipOboGoParser
	\brief A class to parse only a specified set of relationships

	This class will read a Gene Ontology OBO file and add only those relationship
	 which are specified to the graph. The most important method of this class if the
	 parseGoFile which takes the file name as a parameter.

	 Implements GoParserInterface

*/
class AllowedRelationshipOboGoParser : public GoParserInterface{

public:


	//! Method to parse the go file, should be an OBO file
	/*!
		This method will read a Gene Ontology OBO file and add only those relationship
		 which are specified to the graph.

	*/
	inline GoGraph* parseGoFile(std::string filename){
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

		//graph object to be returned
		GoGraph* graph = new GoGraph();

		std::ifstream in(filename.c_str());
		std::string line;

		//at first line
		std::getline(in,line);

		//advance to first term
		while(in.good() && line != "[Term]"){
			std::getline(in,line);
			boost::trim(line);
		}

		//std::cout << "at terms" << std::endl;
		while(in.good()){
			//parse a term

			//temp data
			std::string term,name,description,ontology;
			bool isObsolete = false;

			//vector to hold go accession ids of related terms.
			std::vector<std::string> relatedTerms;
			std::vector<std::string> relatedTermRelationship;
			
			//std::cout << "parsing attributes" << std::endl;
			while(in.good() && line != ""){

				std::getline(in,line);

				if(line == ""){continue;}


				std::string attr,value;
				splitWith(line,":",attr,value);

				//std::cout << "attr: " << attr << " value: " << value << std::endl;
				if(attr == "id"){
					//go accession id
					term = value;

				}else if(attr == "name"){
					//go natural language name/title
					name = value;

				}else if(attr == "namespace"){
					//go ontology, BP,MF,CC
					ontology = value;

				}else if(attr == "def"){
					//go term definition, long form description
					description = value;

				}else if(attr == "is_a"){
					//is_a relationship
					std::string relatedTerm,desc;

					splitWith(value,"!",relatedTerm,desc);

					//add related term to vector for adding later
					relatedTerms.push_back(relatedTerm);

					//add attr as relationship, attr must = "is_a" here
					relatedTermRelationship.push_back(attr);
				}else if(attr == "is_obsolete"){
					//if obsolete set flag.
					isObsolete = true;

				}else if(attr == "relationship"){
					std::string type,toTerm,desc,temp;

					//std::cout << "relationship" << std::endl;
					//std::cout << value << std::endl;
					//extract relationship
					splitWith(value," ",type,desc);
					//extract term to which related
					splitWith(desc,"!",toTerm,temp);

					//add all types of relationships
					relatedTerms.push_back(toTerm);

					relatedTermRelationship.push_back(type);
				}
			}
			
			//post process
			//std::cout << term << std::endl;
			//std::cout << name << std::endl;
			//std::cout << description << std::endl;
			//std::cout << ontology << std::endl;

			
			if(!isObsolete){
				//add the term to the graph term
				graph->insertTerm(term,name,description,ontology);

				//loop over all related terms
				for(std::size_t i = 0; i < relatedTerms.size(); ++i){

					//create a temp variable for readability
					std::string relatedTerm = relatedTerms.at(i);
					//std::cout << relatedTerm << "\t";
					
					//create a temp variable for readability
					std::string relationship = relatedTermRelationship.at(i);
					//std::cout << relationship << std::endl;

					GO::Relationship relationsihpType = GO::relationshipStringToCode(relationship);
					if(!relationshipPolicy->isAllowed(relationsihpType)){continue;}

					//insert related terms, there are just stubs to be overwritten later on
					graph->insertTerm(relatedTerm,"name","description","ontology");

					//insert edge
					graph->insertRelationship(term,relatedTerm,relationship);

				}//end for, each related term
			}

			//std::cin.get();
			//advance to next term
			while(in.good() && line != "[Term]"){
				std::getline(in,line);
				boost::trim(line);
			}
			//std::cin.get();
		}

		//call to initialize the graph's vertex to index maps
		graph->initMaps();
	
		//return the graph pointer
		return graph;
	}


	//! A method to test if a file fits the accepted format
	/*!
		Returns true if the file matches accepted format, false otherwise
	*/
	inline bool isFileGood(const std::string &filename){
		std::ifstream in(filename.c_str());
		if (!in.good()){
			return false;
		}

		std::string line;
		std::getline(in, line);

		while (in.good() && line != "[Term]"){
			std::getline(in, line);
			boost::trim(line);
		}

		if (!in.good()){
			return false;
		}

		//parse 3 terms
		std::size_t count = 0;
		while (in.good() && count < 3){

			while (in.good() && line != ""){
				std::getline(in, line);
				if (line == ""){ continue;} // skip any empty lines at the end of input

				std::string attr, value;
				splitWith(line, ":", attr, value);
				if (value == "" || value == ""){
					return false; //if any attributes are empyt return false.
				}
			}

			//Next term
			while (in.good() && line != "[Term]"){
				std::getline(in, line);
				boost::trim(line);
			}
			count += 1;
		}

		if (count < 3 || !in.good()){
			return false;
		}else{
			return true;
		}
	}


	//! a helper method
	/*!
		splits strings on the given string pattern, splitStr.
	*/
	inline void splitWith(const std::string &instr,const std::string &splitStr,
								std::string &attr,       std::string &value)
	{
		size_t div = instr.find(splitStr);
		if(div != std::string::npos){
			attr = instr.substr(0,div);
			value = instr.substr(div+1);
			boost::trim(attr);
			boost::trim(value);
		}
	}



	//! a method to create a new instance of this class for use in a factory
	/*!
		creats a new pointer to the parser, used by the factory for go parsers.
	*/
	inline GoParserInterface* clone(){
		return new AllowedRelationshipOboGoParser(relationshipPolicy);
	}


	//! a method to set the policy
	/*!
		sets the policy of the parser
	*/
	inline void setPolicy(RelationshipPolicyInterface* policy){
		relationshipPolicy = policy;
	}


	//! A parameterized constructor
	/*!
		constructor that sets the policy
	*/
	inline AllowedRelationshipOboGoParser(RelationshipPolicyInterface* policy){
		setPolicy(policy);
	}


private:
	//! A RelationshipPolicyInterface
    /*! This RelationshipPolicyInterface holds the relationships to be allowed during parsing */
	RelationshipPolicyInterface* relationshipPolicy;


};
#endif
