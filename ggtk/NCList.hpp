/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef NCLIST
#define NCLIST

#include <iostream>                         // for std::cout
#include <iterator>
#include <utility>
#include <vector>
#include <map>
#include <math.h>
#include <string>

#include <ggtk/SimpleRegion.hpp>


/*! \class NCList ggtk/NCList.hpp
\brief  A container class for quickly finding intersections of genomic intervals

This class prepresents an implementation of Nested Containment Lists by Alekseyenko and Lee.

Alekseyenko AV and Lee CJ. Nested Containment List (NCList): a new algorithm for accelerating 
 interval query of genome alignment and interval databases. Bioinformatics. 2007 
 Jun 1;23(11):1386-93. Epub 2007 Jan 18.

*/
class NCList{

	public:
	/*!
		Data structure NCNode, NCList = List of NCNodes
	*/
	class NCNode{

	  public:
		/*!
			Top level region interval.
		*/
		GenomicRegion _region;

		/*!
			List of all regions completely contained by the top level regions interval.
		*/		
		NCList* _containments;

		/*! Node Constructor
			Most of the work done by NCList Constructor
		*/
		NCNode(GenomicRegion region,std::vector<GenomicRegion> &containments){
			_region = region;

			if(containments.size() == 0){
				_containments = NULL;
			}else{
				_containments = new NCList(containments);
			}
		};
		

		
		/*! contains a Genomic Region
			Overloaded methods to check for containment or overlap

			Contianment
			|----------------------------|
				|------------------|
		*/
		inline
		bool contains(const GenomicRegion g){
			return _region.contains(g);
		}

		/*! contains a start end pair
		*/
		inline
		bool contains(const std::pair<size_t,size_t> p){
			return _region.contains(p);
		}

		/*! contains start and end interval
		*/
		inline
		bool contains(const size_t start, const size_t end){
			return _region.contains(start,end);
		}

		/*! contains a single coordinate
		*/
		inline
		bool contains(const size_t point){
			return _region.contains(point);
		}

		/*! overlaps a genomic region

			Overlap
				|----------------------|
			|---------|    or       |-----------|
		*/
		inline
		bool overlaps(const GenomicRegion g){
			return _region.overlaps(g);
		}

		/*! overlaps a start end pair
		*/
		inline
		bool overlaps(const std::pair<size_t,size_t> p){
			return _region.overlaps(p);
		}

		/*! overlaps a start and end interval
		*/
		inline
		bool overlaps(const size_t start, const size_t end){
			return _region.overlaps(start,end);
		}

		/*! get the current region
		*/
		GenomicRegion getRegion(){
			return _region;
		}

	};


	/*!
		Constructor for NCList that performs the work of sorting and inserting intevals
		into the NCNodes.
	*/
	inline
	NCList(std::vector<GenomicRegion> &regions){

		_items = std::vector<NCNode>();
		//reserve genes.size(), good guess to the number of nodes needed.
		_items.reserve(regions.size());
		_totalFeatures = regions.size();

		//sort by the start position of the gene, biased by gene size.
		std::sort(regions.begin(),regions.end());

		std::vector<GenomicRegion>::iterator rItr;

		if(regions.size() != 0){

			//temporary count of genes added to a sub list
			size_t addCount = 0;
			//temporary storage for all regions that are contained by another region.
			std::vector<GenomicRegion> tempList;

			//current region being examined.
			GenomicRegion currentRegion;
			
			//iterate each region in the list as we create the NCList
			std::vector<GenomicRegion>::iterator currentPtr = regions.end();
			for(rItr = regions.begin();rItr != regions.end();++rItr){
				if(currentPtr == regions.end()){
					//guarantee currentPtr is the first gene at the beginning
					currentPtr = rItr;
					currentRegion = *currentPtr;
				}
				else{
					GenomicRegion rtemp = *rItr;
					if(currentRegion.contains(rtemp)){
						//continue adding regions contained by currentRegion to the templist
						// these will be added later
						++addCount;
						tempList.push_back(rtemp);
						
					}else{
						//the next region is not contained by currentRegion,
						// add all Regions in the list to an NCNode and
						// add it to the list
						NCNode n = NCNode(currentRegion,tempList);
						_items.push_back(n);

						currentPtr = rItr;
						currentRegion = rtemp;
						tempList.clear();
						addCount = 0;
					}
				}
			}

			//Add a Node to the list if it is empty,
			// if not empty add all regions in the tempList to the last node.
			if(_items.empty() || !_items.at(_items.size()-1).contains(currentRegion)){
				_items.push_back(NCNode(currentRegion,tempList));
			}
		}
	}

	///////////////////////////////
	//Utility methods for searching

	/*!
		Get the list index of the overlapped region
	*/
	inline
	size_t getOverlapIndex(const GenomicRegion r){
		size_t i = 0;
		size_t k = _items.size()-1;

		//use binary search to find the best index for the gene or region
		while(i < k){
			size_t j = (i+k)/2;
			NCNode cNode = _items.at(j);

			if(cNode.contains(r)){
				return j;
			}else{
				if(r._start < cNode._region._start){
					k = j;
				}else{
					i = j+1;
				}
			}
		}
		//return the index in the list
		return i;
	}

	/*!
		Get the list index of the overlapped start end pair
	*/
	inline
	size_t getOverlapIndex(const std::pair<size_t,size_t> p){
		size_t i = 0;
		size_t k = _items.size()-1;

		//use binary search to find the correct index for the region
		while(i < k){
			size_t j = (i+k)/2;
			NCNode cNode = _items.at(j);

			if(cNode.contains(p)){
				return j;
			}else{
				if(p.first < cNode._region._start){
					k = j;
				}else{
					i = j+1;
				}
			}
		}
		return i;
	}


	/*!
		Get the list index of the overlapped start end interval
	*/
	inline
	size_t getOverlapIndex(const size_t start, const size_t end){
		size_t i = 0;
		size_t k = _items.size()-1;

		//use binary search to find the correct index for the region
		while(i < k){
			size_t j = (i+k)/2;
			NCNode cNode = _items.at(j);

			if(cNode.contains(start,end)){
				return j;
			}else{
				if(start < cNode._region._start){
					k = j;
				}else{
					i = j+1;
				}
			}
		}
		return i;
	}

	/*!
		Get the list index of the overlapped coordinate
	*/
	inline
	size_t getOverlapIndex(const size_t point){
		size_t i = 0;
		size_t k = _items.size()-1;

		//use binary search to find the correct index for the region
		while(i < k){
			size_t j = (i+k)/2;
			NCNode cNode = _items.at(j);

			if(cNode.contains(point)){
				return j;
			}else{
				if(point < cNode._region._start){
					k = j;
				}else{
					i = j+1;
				}
			}
		}
		return i;
	}


	/*!
		A method to return all genes as a vector
	*/
	inline
	std::vector<GenomicRegion> getFeatures(){

		std::vector<GenomicRegion> features;

		for(size_t i = 0; i < _items.size(); ++i){
			//add all genes to the vector
			features.push_back(_items.at(i)._region);

			//if a node's containment list in not empty, add its regions as well
			if(_items.at(i)._containments != NULL && _items.at(i)._containments->size() >0){
				std::vector<GenomicRegion> contents = _items.at(i)._containments->getFeatures();
				features.insert(features.end(),contents.begin(),contents.end());
			}
		}
		return features;
	}

	/*!
		Method to return all genes in a given range
	*/
	std::vector<GenomicRegion> getFeaturesInRange(const GenomicRegion r){

		//Find the start and end indexes in the NCList based on the given gene.
		size_t s = getOverlapIndex(r._start);
		size_t e = getOverlapIndex(r._end);

		std::vector<GenomicRegion> list;
		for(size_t i = s; i <= e; ++i){
			NCNode cNode = _items.at(i);
			if(!cNode.overlaps(r)){
				continue;
			}
			//add the top level region
			list.push_back(cNode._region);

			//add all genes in the containment list.
			if(cNode._containments != NULL && cNode._containments->size() > 0){
				std::vector<GenomicRegion> add = cNode._containments->getFeatures();
				list.insert(list.end(),add.begin(),add.end());
			}
		}
		return list;
	}


	/*!
		Method to return all genes between a start end pair
	*/
	std::vector<GenomicRegion> getFeaturesInRange(const std::pair<size_t,size_t> p){
		//Find the start and end indexes in the NCList based on the given gene.
		size_t s = getOverlapIndex(p.first);
		size_t e = getOverlapIndex(p.second);

		std::vector<GenomicRegion> list;
		for(size_t i = s; i <= e; ++i){
			NCNode cNode = _items.at(i);
			if(!cNode.overlaps(p)){
				continue;
			}
			//add the top level region
			list.push_back(cNode._region);

			//add all genes in the containment list.
			if(cNode._containments != NULL && cNode._containments->size() > 0){
				std::vector<GenomicRegion> add = cNode._containments->getFeatures();
				list.insert(list.end(),add.begin(),add.end());
			}
		}
		return list;
	}


	/*!
		Method to return all genes between a start end interval
	*/
	inline
	std::vector<GenomicRegion> getFeaturesInRange(const size_t start, const size_t end){
		//Find the start and end indexes in the NCList based on the given gene.
		size_t s = getOverlapIndex(start);
		size_t e = getOverlapIndex(end);

		std::vector<GenomicRegion> list;
		for(size_t i = s; i <= e; ++i){
			NCNode cNode = _items.at(i);
			if(!cNode.overlaps(start,end)){
				continue;
			}
			//add the top level region
			list.push_back(cNode._region);

			//add all genes in the containment list.
			if(cNode._containments != NULL && cNode._containments->size() > 0){
				std::vector<GenomicRegion> add = cNode._containments->getFeatures();
				list.insert(list.end(),add.begin(),add.end());
			}
		}
		return list;
	}

	/*!
		Method to return all genes at a particular index in the list
	*/
	inline
	std::vector<GenomicRegion> getFeaturesAt(const size_t index){
	
		std::vector<GenomicRegion> regions;

		if(_items.at(index)._containments != NULL){
			regions = _items.at(index)._containments->getFeatures();
		}
		regions.insert(regions.begin(), _items.at(index).getRegion());
		return regions;
	}

	/*!
		size returns number of top level nodes
	*/
	inline
	size_t size(){
		return _items.size();
	}

	/*!
		numFeatures returns number of all genes/features
	*/
	inline
	size_t numFeatures(){
		return _totalFeatures;
	}

	/*!
		return the vector of NCNodes
	*/
	inline
	std::vector<NCNode> getNodes(){
		return _items;
	}


	/*!
		returns the top level region at an index i
	*/
	inline
	GenomicRegion getRegionAt(size_t i){
		if(i >= 0 && i < _items.size()){
			return _items.at(i).getRegion();
		}else{
			return GenomicRegion();
		}
	}

	/*!
		List of NCNodes as a vector
	*/
	std::vector<NCNode> _items;

private:
	/*!
		total number of genes/regions
	*/
	size_t _totalFeatures;
};
#endif
