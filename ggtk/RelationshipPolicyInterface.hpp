/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef RELATIONSHIP_POLICY_INTERFACE
#define RELATIONSHIP_POLICY_INTERFACE

#include <ggtk/GoEnums.hpp>

/*! \class RelationshipPolicyInterface
	\brief An interface to check relationships between GO terms

	This is interface is used to create parsers which will only use a specific set
	  of relationship when parsing a GO graph file.
*/
class RelationshipPolicyInterface{
public:
	//! A pure virtual meethod to test if a relationship is allowed
	/*!
		This pure virtual method requires any subclass to imlement an isAllowed
		  method to enforce the relationship pollicy.
	*/
	virtual bool isAllowed(GO::Relationship relationship) = 0;
};
#endif
