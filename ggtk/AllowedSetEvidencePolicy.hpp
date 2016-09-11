/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ALLOWED_SET_EVIDENCE_POLICY
#define ALLOWED_SET_EVIDENCE_POLICY

#include <vector>
#include <ggtk/GoEnums.hpp>
#include <ggtk/EvidencePolicyInterface.hpp>
#include <boost/unordered_map.hpp>

/*! \class AllowedSetEvidencePolicy
	\brief A class to allow only a set of evidence codes for annotations

	A class to allow only certain evidence codes in the go graph. It uses a set of 
	enums to restric the types of evidence codes considered for annotations.

*/
class AllowedSetEvidencePolicy: public EvidencePolicyInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) AllowedSetEvidencePolicy
	*/
	inline AllowedSetEvidencePolicy(){
		_evidenceMap = boost::unordered_map<GO::EvidenceCode,bool>();
	}

	//! A parameterized constructor
	/*!
		Creats the AllowedSetEvidencePolicy using a list(vector) of evidence codes to allow
	*/
	inline AllowedSetEvidencePolicy(std::vector<GO::EvidenceCode> evidenceCodes){
		_evidenceMap = boost::unordered_map<GO::EvidenceCode,bool>();
		for(std::size_t i = 0; i < evidenceCodes.size();++i){
			_evidenceMap[evidenceCodes.at(i)] = true;
		}
	}

	//! a method to test if an eviddence code is allowed or not
	/*!
		tests if the evidence is allowed. Overridden to fulfill the EvidencePolicyInterface
	*/
	inline bool isAllowed(GO::EvidenceCode evidenceCode){
		return _evidenceMap.find(evidenceCode) != _evidenceMap.end();
	}


	//! a method to add a evidence to the set of evidence codes allowed
	/*!
		adds a evidence to the set of evidence codes allowed by setting its mapped value to true
	*/
	inline void addEvidence(GO::EvidenceCode evidenceCode){
		_evidenceMap[evidenceCode] = true;
	}

	//! a method to add a evidence to the set of evidence codes allowed
	/*!
		adds a evidence to the set of evidence codes allowed by setting its mapped value to true
	*/
	inline void addEvidence(const std::string &stringCode){
		GO::EvidenceCode evidenceCode = GO::evidenceStringToCode(stringCode);
		if (evidenceCode != GO::ECODE_ERROR){
			_evidenceMap[evidenceCode] = true;
		}
	}


	//! a method to determine if the Policy is empty
	/*!
		Determines if the Policy is empty
	*/
	inline bool isEmpty(){
		return _evidenceMap.size() == 0;
	}


private:
	//! a map of evidence codes to bool
    /*! maps an evidence code to a bool. Boost unordered map give constant time find. */
	boost::unordered_map<GO::EvidenceCode,bool> _evidenceMap;

};
#endif
