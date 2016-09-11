/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef PRECOMPUTED_MATRIX_TERM_SIMILARITY
#define PRECOMPUTED_MATRIX_TERM_SIMILARITY

#include <vector>

#include <ggtk/TermSimilarityInterface.hpp>

#include <boost/tokenizer.hpp>

//! A class to calculate similarity between go terms for 2 sets using a precomuted term similarity matrix.
/*! \class PrecomputedMatrixTermSimilarity
	This class allows the term similarity calculation to be decoupled
	 from term set (gene) similarity measure that use them.
	 Term similarity is loaded from a matrix file.
*/
class PrecomputedMatrixTermSimilarity: public TermSimilarityInterface{

public:
	
	//! A constructor
	/*!
		Parses a matrix file and creates the PrecomputedMatrixTermSimilarity object
	*/
	inline PrecomputedMatrixTermSimilarity(std::string matrix_file){
		std::ifstream in(matrix_file.c_str());
		//Tokenizer type
		typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
		boost::char_separator<char> tab_sep("\t","",boost::keep_empty_tokens);
		tokenizer::iterator it;
		std::string line;

		std::size_t line_count = 0;

		//first line
		getline(in,line);
		tokenizer tokens(line,tab_sep);
		it = tokens.begin();

		std::string firstTerm = *it;
		_termToIndex[firstTerm] = line_count;
		++line_count;
		++it;

		std::vector<double> firstRow;
		while(it != tokens.end()){
			std::string strval = *it;
			double val = atof(strval.c_str());
			firstRow.push_back(val);
			++it;
		}

		std::size_t nRows = firstRow.size();
		_matrix.reserve(nRows);
		_matrix.push_back(firstRow);

		while(in.good()){
			getline(in,line);
			tokenizer tokens(line,tab_sep);
			it = tokens.begin();
			if(it == tokens.end()){continue;}

			std::string term = *it;
			_termToIndex[term] = line_count;
			++line_count;
			++it;

			std::vector<double> row;
			row.reserve(nRows);
			while(it != tokens.end()){
				std::string strval = *it;
				double val = atof(strval.c_str());
				row.push_back(val);
				++it;
			}
			_matrix.push_back(row);
		}
		//std::cout << "rows " << _matrix.size() << std::endl;
		//std::cout << "cols " << _matrix.at(0).size() << std::endl;
		//std::cout << "terms " << _termToIndex.size() << std::endl;
	}

	//! A method for calculating term-to-term similarity for GO terms using a precomputed similarity matrix.
	/*!
		This method returns the term similarity as defined by the matrix.
	*/
	inline double calculateTermSimilarity(std::string goTermA, std::string goTermB){
		if(hasTerm(goTermA) && hasTerm(goTermB)){
			std::size_t i = _termToIndex[goTermA];
			std::size_t j = _termToIndex[goTermB];
			return _matrix[i][j];
		}else{
			return 0.0;
		}
	}

	//! A method for calculating term-to-term similarity for GO terms using a precomputed similarity matrix.
	/*!
		This method returns the similarity scaled between 0 and 1 [0,1] inclusive
	*/
	inline double calculateNormalizedTermSimilarity(std::string goTermA, std::string goTermB){
		return calculateTermSimilarity(goTermA,goTermB);
	}


	//! This method projects a set of terms into it the kernel space
	/*!
		This method treats the term similarity matrix as a kernel
		 and projects a set of terms into it.
	*/
	std::vector<double> projectTermSet(const std::vector<std::string> &terms){
		std::vector<double> projectedVec(_matrix.size(),0.0);
		std::vector<std::string>::const_iterator it;

		for(std::size_t col = 0; col < _matrix.size(); ++col){
			double sum = 0.0;
			for(it = terms.begin(); it != terms.end(); ++it){
				std::string prot = *it;
				if(_termToIndex.find(prot) != _termToIndex.end()){
					std::size_t row = _termToIndex[prot];
					sum += _matrix.at(row).at(col);
				}
			}
			projectedVec[col] = sum;
		}
		return projectedVec;
	}

private:
	inline bool hasTerm(const std::string &term){
		return _termToIndex.find(term) != _termToIndex.end();
	}

	boost::unordered_map<std::string, std::size_t> _termToIndex;
	std::vector<std::vector<double> >   _matrix;

	

};
#endif


