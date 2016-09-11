/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef STANDARD_RELATIONSHIP_POLICY
#define STANDARD_RELATIONSHIP_POLICY

#include <ggtk/RelationshipPolicyInterface.hpp>
#include <boost/unordered_map.hpp>

/*! \class StandardRelationshipPolicy
	\brief A class to allow only a set of relationships

	A class to allow only certain relationships in the go graph. It uses a set of 
	enums to restric the types of relationships considered in a graph.

*/
class StandardRelationshipPolicy: public RelationshipPolicyInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline StandardRelationshipPolicy(){
		_relationshipMap = boost::unordered_map<GO::Relationship,bool>();
		_relationshipMap[GO::IS_A] = true;
		_relationshipMap[GO::PART_OF] = true;
	}

	//! A parameterized constructor
	/*!
		Creats the StandardRelationshipPolicy using a list(vector) of relationships to allow
	*/
	inline StandardRelationshipPolicy(std::vector<GO::Relationship> relationships){
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


private:
	//! a map of relationships to bool
    /*! maps a relationship to a bool. Boost unordered map give constant time find. */
	boost::unordered_map<GO::Relationship,bool> _relationshipMap;

};
#endif
