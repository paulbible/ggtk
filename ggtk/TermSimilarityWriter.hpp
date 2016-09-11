/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef TERM_SIMILARITY_WRITER
#define TERM_SIMILARITY_WRITER

#include <vector>
#include <string>
#include <iostream>

#include <ggtk/GoEnums.hpp>
#include <ggtk/GoGraph.hpp>
#include <ggtk/AnnotationData.hpp>
#include <ggtk/TermSimilarityInterface.hpp>

//! A class write a term similarity matrix to file. Companion to PrecomputedMatrixTermSimilarity
/*! \class TermSimilarityWriter
	This class writes a term similarity matrix to file by first calculating all similarity values
	  between pairs of terms. This class will be use to write matrices 
	  read by PrecomputedMatrixTermSimilarity.
*/
class TermSimilarityWriter{


public:
	//! Parameterized constructor
	/*!
		A simple parameterized constructor.
		This class take an instance of the GO Graph.
	*/
	inline TermSimilarityWriter(GoGraph* goGraph, AnnotationData* annoData){
		_goGraph = goGraph;
		_annoData = annoData;
	}


	//! A method to write a term similarity matrix
	/*!
		Calculates and writes the similarity matrix to file.
		Calculates the similarity between all pairs of terms.
		The complexity is O(N^2) * O(Term Pair Calculation Cost).
		O(Term Pair Calculation Cost) is usually near constant time,
		 but some method will be extremely slow and require other methods
	*/
	inline void writeSimilarityMatrix(TermSimilarityInterface* termSim, std::string fileName, long ontology_code){
		GO::Onto ontology = static_cast<GO::Onto>(ontology_code);
		std::vector<std::string> ontologyTerms = _annoData->getOntologyTerms(_goGraph, ontology);

		// Initialze a matrix
		std::size_t nTerms = ontologyTerms.size();
		std::vector<std::vector<double> > matrix;
		matrix.reserve(nTerms);
		for (std::size_t i = 0; i < nTerms; ++i){
			matrix.push_back(std::vector<double>());
			for (std::size_t j = 0; j < nTerms; ++j){
				matrix[i].push_back(0.0);
			}
		}

		// --- Main Calculation ---
		for (std::size_t i = 0; i < nTerms; ++i){
			std::string termA = ontologyTerms.at(i);
			matrix[i][i] = termSim->calculateNormalizedTermSimilarity(termA, termA);
			for (std::size_t j = i + 1; j < nTerms; ++j){
				std::string termB = ontologyTerms.at(j);
				double value = termSim->calculateNormalizedTermSimilarity(termA, termB);
				//cout << termA << "\t" << termB << "\t" << value << endl;
				matrix[i][j] = value;
				matrix[j][i] = value;
			}
		}

		// write the matrix
		writeMatrix(fileName, matrix, ontologyTerms);
	}

	//! A method to write a term similarity matrix for Biological Process
	/*!
		Calcualtes and writes the biological process term similarity matrix
	*/
	inline void writeSimilarityMatrixBP(TermSimilarityInterface* termSim, std::string fileName){
		writeSimilarityMatrix(termSim, fileName, GO::BP);
	}

	//! A method to write a term similarity matrix for Molecular Function
	/*!
		Calcualtes and writes the molecular function term similarity matrix
	*/
	inline void writeSimilarityMatrixMF(TermSimilarityInterface* termSim, std::string fileName){
		writeSimilarityMatrix(termSim, fileName, GO::MF);
	}

	//! A method to write a term similarity matrix for Cellular Component
	/*!
	Calcualtes and writes the cellular component term similarity matrix
	*/
	inline void writeSimilarityMatrixCC(TermSimilarityInterface* termSim, std::string fileName){
		writeSimilarityMatrix(termSim, fileName, GO::CC);
	}

private:

	//! A method to write a matrix to file
	/*!
		writes the matrix to file.
	*/
	inline void writeMatrix(std::string fname, const std::vector<std::vector<double> > &matrix, const std::vector<std::string> &terms){
		std::ofstream out(fname.c_str());
		std::size_t matrix_size = matrix.size();
		for (std::size_t i = 0; i < matrix_size; ++i){
			std::string termA = terms.at(i);
			out << termA;
			for (std::size_t j = 0; j < matrix_size; ++j){
				out << "\t" << matrix[i][j];
			}
			out << std::endl;
		}
		out.close();
	}

	//! A pointer to the gene ontology graph
	GoGraph* _goGraph;
	//! A pointer to the annotation database
	AnnotationData* _annoData;
};
#endif