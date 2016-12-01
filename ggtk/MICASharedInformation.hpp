/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef MICA_SHARED_INFORMATION
#define MICA_SHARED_INFORMATION

#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/SharedInformationInterface.hpp>
#include <ggtk/GoGraph.hpp>
#include <ggtk/SetUtilities.hpp>
#include <ggtk/Accumulators.hpp>

#include <boost/unordered_map.hpp>
#include <boost/accumulators/statistics/max.hpp>

/*! \class MICASharedInformation
	\brief A class to calculate shared infromation as the most informative common ancestor (MICA)

	This class calculates shared infromation using the most informative common ancestor (MICA).
	 The MICA is a term that is also known as the minimum subsumer.

	 This shared information method forms the basis of 3 inforamtion content measures
	 put forward by Lord el al.

    P. W. Lord, R. D. Stevens, A. Brass, and C. A. Goble, 
	 "Semantic similarity measures as tools for exploring the gene ontology,"
	 Pac Symp Biocomput, pp. 601-12, 2003.

*/
class MICASharedInformation : public SharedInformationInterface{

public:
	//! A constructor
	/*!
		Creates the MICASharedInformation class
	*/
	inline MICASharedInformation(GoGraph* goGraph,TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
	}

	//! A method for calculating the shared infromation between two concepts.
	/*!
		This method returns the shared information between two concepts.
	*/
	inline double sharedInformation(const std::string &termA,const std::string &termB){
		// return 0 for any terms not in the datbase
		if (!_icMap.hasTerm(termA) || !_icMap.hasTerm(termB)){
			return 0.0;
		}
		// return 0 for terms in different ontologies
		if (_goGraph->getTermOntology(termA) != _goGraph->getTermOntology(termB)){
			return 0.0;
		}

		Accumulators::MaxAccumulator myMax;

		boost::unordered_set<std::string> ancestorsA = _goGraph->getAncestorTerms(termA);
		ancestorsA.insert(termA);
		boost::unordered_set<std::string> ancestorsB = _goGraph->getAncestorTerms(termB);
		ancestorsB.insert(termB);

		boost::unordered_set<std::string> sharedAncestors = SetUtilities::set_intersection(ancestorsA,ancestorsB);

		boost::unordered_set<std::string>::iterator iter = sharedAncestors.begin();
		for(;iter != sharedAncestors.end(); ++iter){
			myMax(_icMap[*iter]);
		}

		return Accumulators::extractMax(myMax);
	}

	//! An interface method for returning the shared information of a single terms,or information content
	/*!
		This method privdes a mechanism for returing a term's infromation content.
	*/
	inline double sharedInformation(const std::string &term){
		// return 0 for any terms not in the datbase
		if (!_icMap.hasTerm(term)){
			return 0.0;
		}
		return _icMap[term];
	}

	//! An interface method for returning the maximum information content for a term
	/*!
		This method provides the absolute max information content within a corpus for normalization purposes.
	*/
	inline double maxInformationContent(const std::string &term){

		double maxIC;

		//select the correct ontology normalization factor
		GO::Onto ontoType = _goGraph->getTermOntology(term);
		if(ontoType == GO::BP){
			maxIC = -std::log(_icMap.getMinBP());
		}else if(ontoType == GO::MF){
			maxIC = -std::log(_icMap.getMinMF());
		}else{
			maxIC = -std::log(_icMap.getMinCC());
		}

		return maxIC;
	}

	//! An interface method for determining if a term can be found
	/*!
		Determines if the term can be found in the current map.
	*/
	inline bool hasTerm(const std::string &term){
		return _icMap.hasTerm(term);
	}

	//! An interface method for determining if the two terms are of like ontologies.
	/*!
	Determine if two terms are of the same ontology.
	*/
	bool isSameOntology(const std::string &termA, const std::string &termB){
		return _goGraph->getTermOntology(termA) == _goGraph->getTermOntology(termB);
	}

private:

	GoGraph* _goGraph;
	TermInformationContentMap _icMap;

};
#endif
