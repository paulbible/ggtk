/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef GO_ENUMS
#define GO_ENUMS

#include <string>

//! Number of ontologies, 3 + 1 error code
#define NUM_ONTOLOGIES 4

//! Number of evidence codes, 22 + 1 error code
#define NUM_EVIDENCES 23

//! Number of relationships codes, 5 + 1 error code
#define NUM_RELATIONSHIPS 6


//! GO namespaces
/*!
	This namespace is a set of static variables related to go terms and relationships.
*/
namespace GO{

	//! function that returns strings representing the root ontology term biological_process
	inline std::string getRootTermBP(){
		return "GO:0008150";
	}

	//! function that returns strings representing the root ontology term molecular_function
	inline std::string getRootTermMF(){
		return "GO:0003674";
	}
	
	//! function that returns strings representing the root ontology term cellular_component
	inline std::string getRootTermCC(){
		return "GO:0005575";
	}

	//! Ontology enum type
	/*!
		This enum defines a type for sub-ontologies.
	*/
	enum Onto{
		BP=0,
		MF=1,
		CC=2,
		ONTO_ERROR=3
	};

	//! Ontology enum strings
	/*!
		These are string representations of the sub-ontologies. Take from obo go files.
	*/
	static std::string ontologyStringCodes[NUM_ONTOLOGIES] = {
		"biological_process",
		"molecular_function",
		"cellular_component",
		"ONTOLOGY_ERROR"
	};

	//! A method for returning the ontology code based on string
	/*!
		This method takes a string and returns the proper enum
	*/
	inline Onto ontologyStringToCode(std::string code){
		std::size_t i = 0;
		for(; i < NUM_ONTOLOGIES - 1; ++i){
			//return the index if matching, cast as enum
			if(code.compare(ontologyStringCodes[i]) == 0){
				return static_cast<Onto>(i);
			}
		}
		//return error enum if not found
		return static_cast<Onto>(i);
	}

	//! A method for returning a human readable string from the ontology code
	/*!
		This method takes an ontology enum value and returns a string
	*/
	inline std::string ontologyToString(const Onto &o){
		if (o < GO::BP || o >= GO::ONTO_ERROR){
			return ontologyStringCodes[GO::ONTO_ERROR];
		}else{
			return ontologyStringCodes[o];
		}
	}

	//! Evcidence Code enum type
	/*!
		This enum defines a type for evidence codes.
		 Defined at http://www.geneontology.org/GO.evidence.shtml
	*/
	enum EvidenceCode{
		//experimental
		EXP=0,
		IDA=1,
		IPI=2,
		IMP=3,
		IGI=4,
		IEP=5,

		//computationally assisted
		ISS=6,
		ISO=7,
		ISA=8,
		ISM=9,
		IGC=10,
		IBA=11,
		IBD=12,
		IKR=13,
		IRD=14,
		RCA=15,

		//author statement
		TAS=16,
		NAS=17,

		//Curator statement
		IC=18,
		ND=19,

		//automatically assigned
		IEA=20,

		//obsolete evidence code
		NR=21,
		ECODE_ERROR=22
	};


	//! Relationship code enum strings
	/*!
		These are string representations of the evidence codes for an annotation.
	*/
	static std::string evidenceStringCodes[NUM_EVIDENCES] = {

		//experimental
		"EXP",
		"IDA",
		"IPI",
		"IMP",
		"IGI",
		"IEP",

		//computationally assisted
		"ISS",
		"ISO",
		"ISA",
		"ISM",
		"IGC",
		"IBA",
		"IBD",
		"IKR",
		"IRD",
		"RCA",

		//author statement
		"TAS",
		"NAS",

		//Curator statement
		"IC",
		"ND",

		//automatically assigned
		"IEA",

		//obsolete evidence code
		"NR",

		//Error code
		"EVIDENCE_CODE_ERROR"
	};

	//! A method for converting evidence code strings to enums
	/*!
		This method takes a string representing the evidence code and converts it to an enum.
	*/
	inline EvidenceCode evidenceStringToCode(std::string code){
		std::size_t i = 0;
		for(; i < NUM_EVIDENCES - 1; ++i){
			//return the index if matching, cast as enum
			if(code.compare(evidenceStringCodes[i]) == 0){
				return static_cast<EvidenceCode>(i);
			}
		}
		//return evidence error if not found
		return static_cast<EvidenceCode>(i);
	}

	//! A method for returning a human readable string from an evidence code
	/*!
		This method takes an evidence code enum value and returns a string
	*/
	inline std::string evidenceToString(const EvidenceCode &evidence){
		return evidenceStringCodes[evidence];
	}


	//! Relationship codes enum
	/*!
		This enum represents the relationship codes for ontology edges.
	*/
	enum Relationship{
		IS_A=0,
		PART_OF=1,
		REGULATES=2,
		POSITIVELY_REGULATES=3,
		NEGATIVELY_REGULATES=4,
		REL_ERROR=5
	};


	//! Relationship code enum strings
	/*!
		These strings represent the enum codes for each relationship.
	*/
	static std::string relationshipStringCodes[NUM_RELATIONSHIPS] = {
		"is_a",
		"part_of",
		"regulates",
		"positively_regulates",
		"negatively_regulates",
		"RELATIONSHIP_ERROR"
	};

	//! A method to convert relationship codes from string to enum
	/*!
		This method converts the string representation of a relationship to an enum.
	*/
	inline Relationship relationshipStringToCode(std::string code){
		std::size_t i = 0;
		for(; i < NUM_RELATIONSHIPS - 1; ++i){
			//return the index if matching, cast as enum
			if(code.compare(relationshipStringCodes[i]) == 0){
				return static_cast<Relationship>(i);
			}
		}
		//return error code if not found
		return static_cast<Relationship>(i);
	}

	//! A method for returning a human readable string from a Relationship
	/*!
		This method takes an evidence code enum pointer value and returns a string
	*/
	inline std::string relationshipToString(const Relationship &relationship){
		return relationshipStringCodes[relationship];
	}
}
#endif
