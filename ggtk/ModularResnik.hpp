/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef MODULAR_RESNIK
#define MODULAR_RESNIK

#include <ggtk/TermSimilarityInterface.hpp>
#include <ggtk/SharedInformationInterface.hpp>

/*! \class ModularResnik
	\brief A class to calculate resnik similarity between 2 terms using a shared information interface

	This class calculates Resnik similarity.
	Philip Resnik (1995). "Using information content to evaluate semantic similarity in a taxonomy". 
	  In Chris S. Mellish (Ed.). Proceedings of the 14th international joint conference on Artificial intelligence (IJCAI'95)

    P. W. Lord, R. D. Stevens, A. Brass, and C. A. Goble, 
	 "Semantic similarity measures as tools for exploring the gene ontology,"
	 Pac Symp Biocomput, pp. 601-12, 2003.

	maximun information content of all shared ancestors
	IC(MICA)

*/
class ModularResnik: public TermSimilarityInterface{

public:
	
	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline ModularResnik(SharedInformationInterface *sharedInformationCalculator){
		_siCalculator = sharedInformationCalculator;
	}

	//! A method for calculating term-to-term similarity for GO terms using Resnik similarity
	/*!
		This method returns the Resnik similarity or the information content of the most informative common ancestor.
	*/
	inline double calculateTermSimilarity(std::string goTermA, std::string goTermB){
		if (!_siCalculator->hasTerm(goTermA) || !_siCalculator->hasTerm(goTermB)){
			return 0.0;
		}
		if (!_siCalculator->isSameOntology(goTermA, goTermB)){
			return 0.0;
		}
		return _siCalculator->sharedInformation(goTermA,goTermB);
	}


	//! A method for calculating term-to-term similarity for GO terms using Normalized Resnik similarity
	/*!
		This method returns the Resnik similarity divided by the maximum possible similarity
	*/
	inline double calculateNormalizedTermSimilarity(std::string goTermA, std::string goTermB){
		if (!_siCalculator->hasTerm(goTermA) || !_siCalculator->hasTerm(goTermB)){
			return 0.0;
		}
		if (!_siCalculator->isSameOntology(goTermA, goTermB)){
			return 0.0;
		}
		double sharedInformation = _siCalculator->sharedInformation(goTermA,goTermB);
		double maxInformation    = _siCalculator->maxInformationContent(goTermA);
		return sharedInformation/maxInformation;
	}

	//! A constructor
	/*!
		Creates the default(empty) StandardRelationshipPolicy
	*/
	inline void setSharedInformationCalculator(SharedInformationInterface *newSharedInformationCalulator){
		_siCalculator = newSharedInformationCalulator;
	}

private:

	//! private SharedInformationInterface member used for calculations
	SharedInformationInterface *_siCalculator;

};
#endif
