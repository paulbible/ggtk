/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef SHARED_INFORMATION_INTERFACE
#define SHARED_INFORMATION_INTERFACE

#include <string>

/*! \class SharedInformationInterface
	\brief An interface class to define shared information calculations

	This class defines the interface  for shared information calculations. Pure virtual methods
	  require that shared information methods implement these.

*/
class SharedInformationInterface{
public:
	//! A pure virtual method for returning the shared information of two terms
	/*!
		This pure virtual method requires any shared information class to implement this method.
	*/
	virtual double sharedInformation(const std::string &termA, const std::string &termB) = 0;

	//! A pure virtual method for returning the shared information of a single terms,or information content
	/*!
		This pure virtual method privdes a mechanism for returing a term's infromation content.
	*/
	virtual double sharedInformation(const std::string &term) = 0;

	//! A pure virtual method for returning the maximum information content for a term
	/*!
		This pure virtual method requires any shared information class to implement this method.
		This method provides the absolute max information content with in a corpus for normalization purposes.
	*/
	virtual double maxInformationContent(const std::string &term) = 0;

	//! A pure virtual method for determining if a term can be found.
	/*!
		This pure virtual method requires any shared information class to implement this method.
		This method provides a method for client classes to determine if a term can be found by the method.
	*/
	virtual bool hasTerm(const std::string &term) = 0;

	//! A pure virtual method for determining if the two terms are of like ontologies.
	/*!
		This pure virtual method requires any shared information class to implement this method.
		This method provides a method for client classes to determine if two terms are of the same ontology.
	*/
	virtual bool isSameOntology(const std::string &termA, const std::string &termB) = 0;

	
};
#endif
