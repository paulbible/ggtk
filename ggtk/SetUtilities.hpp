/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef SET_UTILITIES
#define SET_UTILITIES

#include <boost/unordered_set.hpp>
#include <boost/foreach.hpp>

//! The SetUtilities namespace provides useful opperations on generic boost::unordered_set
/*!
	SetUtilities provides useful operations on boost::unordered_set. 
	set_intersection is optimized to traverse the smaller set and test exisitence in the larger set.
*/
namespace SetUtilities{

	//!set UTILITY funciton to determine if a set contains an element
	template<typename Type>
	static bool
		set_contains(const boost::unordered_set<Type> &mySet, 
		               Type element)
	{
		return mySet.find(element) != mySet.end();
	}

	//!set UTILITY funciton convert a vector to a set
	template<typename Type>
	static boost::unordered_set<Type>
		convert_vector(const std::vector<Type> &myVec)
	{
		boost::unordered_set<Type> s(myVec.begin(),myVec.end());
		return s;
	}

	//!set OPERATION intersection for boost::unordered_set
	template<typename Type>
	static boost::unordered_set<Type>
		set_intersection(const boost::unordered_set<Type> &setA,
		                 const boost::unordered_set<Type> &setB)
	{
		//iterate the smaller set O(n)
		if(setA.size() <= setB.size()){
			boost::unordered_set<Type> intersectionSet;
			BOOST_FOREACH(const Type &element, setA){
				//find element in O(1)
				if(set_contains(setB,element)){
					intersectionSet.insert(element);
				}
			}
			return intersectionSet;
		}else{
			return set_intersection(setB,setA);
		}
	}

	//!set OPERATION union for boost::unordered_set
	template<typename Type>
	static boost::unordered_set<Type> 
		set_union(const boost::unordered_set<Type> &setA,
		          const boost::unordered_set<Type> &setB)
	{
		if(setA.size() <= setB.size()){
			boost::unordered_set<Type> unionSet = setB;
			unionSet.insert(setA.begin(),setA.end());
			return unionSet;
		}else{
			return set_union(setB,setA);
		}
	}

	//!set OPERATION difference A - B
	template<typename Type>
	static boost::unordered_set<Type>
		set_difference(const boost::unordered_set<Type> &setA,
		               const boost::unordered_set<Type> &setB)
	{
		boost::unordered_set<Type> differenceSet;
		BOOST_FOREACH(const Type &element,setA){
			if(!set_contains(setB,element)){
				differenceSet.insert(element);
			}
		}
		return differenceSet;
	}

};
#endif
