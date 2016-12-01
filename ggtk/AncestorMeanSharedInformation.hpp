/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ANCESTOR_MEAN_SHARED_INFORMATION
#define ANCESTOR_MEAN_SHARED_INFORMATION

#include <ggtk/TermInformationContentMap.hpp>
#include <ggtk/SharedInformationInterface.hpp>
#include <ggtk/GoGraph.hpp>
#include <ggtk/SetUtilities.hpp>
#include <ggtk/Accumulators.hpp>


#include <boost/accumulators/statistics/max.hpp>

/*! \class AncestorMeanSharedInformation
	\brief A class to calculate shared infromation as the average information conent of all common ancestors

	This class calculates shared infromation by averaging the information content of all common ancestors.

	 This shared information method is used a baseline for comparison and may not be meaningful.

*/
class AncestorMeanSharedInformation : public SharedInformationInterface{

public:
	//! A constructor
	/*!
		Creates the AncestorMeanSharedInformation class
	*/
	inline AncestorMeanSharedInformation(GoGraph* goGraph,TermInformationContentMap &icMap){
		_goGraph = goGraph;
		_icMap = icMap;
	}

	//! A method for calculating the shared infromation between two concepts.
	/*!
		This method returns the shared information between two concepts.
	*/
	inline double sharedInformation(const std::string &termA, const std::string &termB){
		// return 0 for any terms not in the datbase
		if (!_icMap.hasTerm(termA) || !_icMap.hasTerm(termB)){
			return 0.0;
		}
		// return 0 for terms in different ontologies
		if (!isSameOntology(termA, termB)){
			return 0.0;
		}

		Accumulators::MeanAccumulator meanIC;

		boost::unordered_set<std::string> ancestorsA = _goGraph->getAncestorTerms(termA);
		ancestorsA.insert(termA);
		boost::unordered_set<std::string> ancestorsB = _goGraph->getAncestorTerms(termB);
		ancestorsB.insert(termB);

		boost::unordered_set<std::string> sharedAncestors = SetUtilities::set_intersection(ancestorsA,ancestorsB);

		boost::unordered_set<std::string>::iterator iter = sharedAncestors.begin();
		for(;iter != sharedAncestors.end(); ++iter){
			meanIC(_icMap[*iter]);
		}

		return Accumulators::extractMean(meanIC);
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
