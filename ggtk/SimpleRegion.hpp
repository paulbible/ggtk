/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef SIMPLE_REGION
#define SIMPLE_REGION

#include <string>
#include <ctype.h>
#include <iostream>

#include <sstream>

/*!
	Fairly portable conversion from string to number
*/
template <typename T>
std::string NumberToString ( T Number )
{
	std::ostringstream ss;
	ss << Number;
	return ss.str();
};


/*!	A Region class to be used with NCList
	This class is used to represent region and genome data.
*/
class SimpleRegion{

public:
	/*! a generic id for the region
	*/
	size_t _id;

	/*! the start coordinate for the region
	*/
	size_t _start;

	/*! the end coordinate for the region
	*/
	size_t _end;

	/*!	Default constructor
		Initializes a simple region.
	*/
	inline SimpleRegion(){
		_id = 0;
		_start = 0;
		_end = 0;
	}

	/*!	Parameterized constructor
		 Allows the creation of a regions with user specified values
	*/
	inline SimpleRegion(const size_t id, const size_t start, const size_t end){
		_id = id;
		_start = start;
		_end = end;
	}

	/*!	Calculates the midpoint of a region
		Simple mid point of a region. (end - start)/2
	*/
	inline
	const size_t midpoint() const{
		return _start + ((_end - _start)/2);
	}

	/*!	Simple distance between two regions.
		Calculates the distance between two regions by calculating the distance between their midpoints.
	*/
	inline
	int distance(const SimpleRegion &rhs){
		int myMid =  (int)midpoint();
		int rhsMid = (int)rhs.midpoint();

		return myMid - rhsMid;
	}


	/*! contains test with SimpleRegion objects.
		Does the region contain rhs?
	*/
	inline
	bool contains(const SimpleRegion &rhs){
		return (_start <= rhs._start)
			&& (_end >= rhs._end);
	}

	/*! Tests the contains relationship with a start end pair
		Does the region contain the start end pair?
	*/
	inline
	bool contains(const std::pair<size_t,size_t> &rhs){
		return (_start <= rhs.first)
			&& (_end >= rhs.second);
	}

	/*! Tests the contains relationship with start and end coordinates
		Does the region contain the interval between start and end?
	*/
	inline
	bool contains(const size_t rhs_start,const size_t rhs_end){
		return (_start <= rhs_start)
			&& (_end >= rhs_end);
	}

	/*! Tests the contains relationship with a single point
		Does the region contain the point coordinate?
	*/
	inline
	bool contains(const size_t point){
		return (_start <= point)
			&& (_end >= point);
	}

	/*! Tests the overlap relationship with a region
		Does the region overlap the rhs region?
	*/
	inline
	bool overlaps(const SimpleRegion &rhs){
		if(_start > rhs._end){
			return false;
		}else if(_end < rhs._start){
			return false;
		}else{
			return true;
		}
	}

	/*! Tests the overlap relationship with a start end pair
		Does the region overlap the start end pair?
	*/
	inline
	bool overlaps(const std::pair<size_t,size_t> &rhs){
		if(_start > rhs.second){
			return false;
		}else if(_end < rhs.first){
			return false;
		}else{
			return true;
		}
	}

	/*! Tests the overlap relationship with start and end coordinates
		Does the region overlap the interval defines by start and end?
	*/
	inline
	bool overlaps(const size_t rhs_start,const size_t rhs_end){
		if(_start > rhs_end){
			return false;
		}else if(_end < rhs_start){
			return false;
		}else{
			return true;
		}
	}

	/*! accessor for start coordinate
		returns the interval's start coordinate
	*/
	inline
	size_t getStart(){
		return _start;
	}

	/*! accessor for end coordinate
		returns the interval's end coordinate
	*/
	inline
	size_t getEnd(){
		return _end;
	}

	/*! accessor for the id
		returns the interval's id
	*/
	inline size_t getId(){
		return _id;
	}
};

/*! EXPERIMENTAL: GenomicRegion class inheriting from SimpleRegion
	Adds a few vaibles to SimpleRegion for use in modeling genomic regions.
	This class is experimental and will be updated at some point in the future.
*/
class GenomicRegion : public SimpleRegion{
public:
	/*! a character representing the chromosome
	*/
	char _chrom;

	/*! the name or accession of the region
	*/
	std::string _name;

	/*! a description for the region
	*/
	std::string _desc;

	/*! a parameterized constructor for the genomic region.
	*/
	inline GenomicRegion(const std::string chrom,
		                 const size_t start, 
						 const size_t end,
						 const size_t id,
						 std::string name, 
						 std::string desc) 
						 : SimpleRegion(id,start,end)
	{

		size_t i = chrom.find("r");
		if(chrom.size() == i + 2){
			_chrom = chrom.at(i+1);
		}else{
			std::string tail = chrom.substr(i+1);
			size_t offset = atoi(tail.c_str()) - 9;
			int char_start = (int)'9';
			int useChar = char_start + offset;
			_chrom = (char)useChar;

		}

		_name = name;
		_desc = desc;
	}

	/*! a simple parametrized constructor for the genomic region
	*/
	inline GenomicRegion(const size_t id,
		                 const size_t start, 
						 const size_t end)
						 : SimpleRegion(id,start,end)
	{
	}

	/*! a default constructor for the genomic region
	*/
	inline GenomicRegion():SimpleRegion(){
		_chrom = '\0';
		_name = "";
		_desc = "";
	}

	/*! returns the chromosome for the genomic region
	*/
	inline std::string getChrom(){
		std::string ch = "chr";

		int start_char = (int)'9';

		if(_chrom == 'M' || _chrom == 'X' ||_chrom == 'Y' 
			|| _chrom == 'm' || _chrom == 'x' || _chrom == 'y')
		{
			ch += _chrom;
		}else if((int)_chrom <= start_char){
			ch += _chrom;
		}else{
			size_t value = 9 + ((int)_chrom - start_char);
			ch += NumberToString(value);
		}

		return ch;
	}

	/*! accessor for the genomic region's name
	*/
	inline std::string getName(){
		return _name;
	}

	/*! accessor for the genomic region's description
	*/
	inline std::string getDesc(){
		return _desc;
	}
};


/*! "less than" (<) operator for simple regions
	This overloaded operator allows comparisons and sorting for regions.
*/
inline
bool operator<(const SimpleRegion &lhs, const SimpleRegion &rhs){

	if(lhs._start == rhs._start){
		return lhs._end - lhs._start > rhs._end - rhs._start;
	}

	return lhs._start < rhs._start;
}

/*! "greater than" (>) operator for simple regions
	This overloaded operator allows comparisons and sorting for regions.
*/
inline
bool operator>(const SimpleRegion &lhs,const SimpleRegion &rhs){

	if(lhs._start == rhs._start){
		return rhs._end - rhs._start > lhs._end - lhs._start;
	}

	return lhs._start > rhs._start;
}

#endif
