/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ALLOWED_SET_RELATIONSHIP_POLICY
#define ALLOWED_SET_RELATIONSHIP_POLICY

#include <vector>
#include <ggtk/GoEnums.hpp>
#include <ggtk/RelationshipPolicyInterface.hpp>
#include <boost/unordered_map.hpp>

/*! \class AllowedSetRelationshipPolicy
	\brief A class to allow only a set of relationships

	A class to allow only certain relationships in the go graph. It uses a set of 
	enums to restric the types of relationships considered in a graph.

*/
class AllowedSetRelationshipPolicy: public RelationshipPolicyInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) AllowedSetRelationshipPolicy
	*/
	inline AllowedSetRelationshipPolicy(){
		_relationshipMap = boost::unordered_map<GO::Relationship,bool>();
	}

	//! A parameterized constructor
	/*!
		Creats the AllowedSetRelationshipPolicy using a list(vector) of relationships to allow
	*/
	inline AllowedSetRelationshipPolicy(std::vector<GO::Relationship> relationships){
		_relationshipMap = boost::unordered_map<GO::Relationship,bool>();
		for(std::size_t i = 0; i < relationships.size();++i){
			_relationshipMap[relationships.at(i)] = true;
		}
	}

	//! a method to test if a relatinoship is allowed or not
	/*!
		tests if the relationship is allowed. Overridden to fulfill the RelationshipPolicyInterface
	*/
	inline bool isAllowed(GO::Relationship relationship){
		return _relationshipMap.find(relationship) != _relationshipMap.end();
	}


	//! a method to add a relationship to the set of relationships allowed
	/*!
		adds a relationship to the set of relationships allowed by setting its mapped value to true
	*/
	inline void addRelationship(GO::Relationship relationship){
		_relationshipMap[relationship] = true;
	}

	//! a method to add a relationship to the set of relationships allowed
	/*!
	adds a relationship to the set of relationships allowed by setting its mapped value to true
	*/
	inline void addRelationship(const std::string &relString){
		GO::Relationship relationship = GO::relationshipStringToCode(relString);
		if (relationship != GO::REL_ERROR){
			_relationshipMap[relationship] = true;
		}
	}


	//! a method to determine if the Policy is empty
	/*!
		Determines if the Policy is empty
	*/
	inline bool isEmpty(){
		return _relationshipMap.size() == 0;
	}


private:
	//! a map of relationships to boo
    /*! maps a relationship to a bool. Boost unordered map give constant time find. */
	boost::unordered_map<GO::Relationship,bool> _relationshipMap;

};
#endif
