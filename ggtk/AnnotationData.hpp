/*=============================================================================
Copyright (c) 2016 Paul W. Bible

Distributed under the Boost Software License, Version 1.0. (See accompanying
file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef ANNOTATION_DATA
#define ANNOTATION_DATA

#include <ggtk/GoEnums.hpp>
#include <ggtk/GoGraph.hpp>

#include <fstream>
#include <vector>
#include <iostream> 
#include <map>
#include <string>

#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>


//! A class for storing information about genes annotated with go terms.
/*!
	This class hold all information about a set of annotations for genes annotated with go terms.
	 It holds a list of genes, a list of go terms, as well as mappings from a gene to a list of go terms,
	 and mappings from a go term to a list of annotated genes. This class allows querying go annotations
	 and their evidence codes.
*/
class AnnotationData{

public:
	/////////////////////////////////////////////////////////
	//  Lists of gene names and go terms used as mapping keys
	/////////////////////////////////////////////////////////
	//! A list of genes stored by the annotation data object.
	/*!
		This storage variable stores the gene names.
	*/
	std::vector<std::string> _genes;

	//! A list of go terms stored by the annotation data object.
	/*!
		This storage variable stores the go terms.
	*/
	std::vector<std::string> _goTerms;



	/////////////////////////////////
 	// A map of keys to index in list
	/////////////////////////////////
	//! A map from a gene strings to a gene index.
	/*!
		This map accespts gene strings and returns gene indices.
		  boost unordered_map ensures O(1) constant time find/has_key queries (hash table).
	*/
	boost::unordered_map<std::string,std::size_t> _stringToGene;

	//! A map from a go term strings to a go term index.
	/*!
		This map accespts go term strings and returns go term indices.
		  boost unordered_map ensures O(1) constant time find/has_key queries (hash table).
	*/
	boost::unordered_map<std::string,std::size_t> _stringToGo;
	////////////////////////////////////////////////////////////////////////////////
	// Main data storage objects 2d vectors storing gos for genes and genes for gos.
	////////////////////////////////////////////////////////////////////////////////
	//! A list of lists of genes, one for each go term.
	/*!
		This vector holds one entry for each go term. Each entry holds a list of genes
		  annotated to that go term.
	*/
	std::vector<std::vector<std::size_t> > _goToGenes;
	//! A list of lists of evidence codes, one for each go term. Parallel to _goToGenes.
	/*!
		This vector holds one entry for each go term. Each entry holds a list of evidence
		  codes for each gene annotated to that go term. It parallels the _goToGenes vectors
		  having the same size and dimensions for each element.
	*/
	std::vector<std::vector<GO::EvidenceCode> > _goToGenesEvidence;

	//! A list of lists of go terms, one for each gene.
	/*!
		This vector holds one entry for each gene. Each entry holds a list of go terms
		  annotated to that gene.
	*/
	std::vector<std::vector<std::size_t> > _geneToGos;
	//! A list of lists of evidence codes, one for each gene. Parallel to _geneToGos.
	/*!
		This vector holds one entry for each gene. Each entry holds a list of evidence
		  codes for each go term annotated to that gene. It parallels the _geneToGos vectors
		  having the same size and dimensions for each element.
	*/
	std::vector<std::vector<GO::EvidenceCode> > _geneToGosEvidence;


	//! Class constructor.
	/*!
		This constructor initialized each vector as an empty vector of the correct type.
	*/
	inline AnnotationData(){
		_genes   = std::vector<std::string>();
		_goTerms = std::vector<std::string>();

		_goToGenes         = std::vector<std::vector<std::size_t> >();
		_goToGenesEvidence = std::vector<std::vector<GO::EvidenceCode> >();

		_geneToGos = std::vector<std::vector<std::size_t> >();
		_geneToGosEvidence = std::vector<std::vector<GO::EvidenceCode> >();
	}//constructor

	//! class descructor
	/*!
		This destructor clears all maps and vectors.
	*/
	inline ~AnnotationData(){
		//Clear all containers on desctruction
		_genes.clear();
		_goTerms.clear();

		_stringToGene.clear();
		_stringToGo.clear();

		_goToGenes.clear();
		_goToGenesEvidence.clear();

		_geneToGos.clear();
		_geneToGosEvidence.clear();
	}//end destructor


	//! A Method to add annotations to the dataset.
	/*!
		This method adds annotations to the database. It takes a gene, a goTerm, and an evidence code.
		  This method checks existence and indexing to remove the burden from parser implementations.
	*/
	inline void addAssociation(const std::string &gene, const std::string &goTerm, const std::string &evidenceCode){

		//Index variables
		std::size_t geneIndex;
		std::size_t goIndex;

		//try{

		//first time finding gene
		if(_stringToGene.find(gene) == _stringToGene.end()){
			//set the index for gene (it will be inserted next, reason for _genes.size())
			_stringToGene[gene] = _genes.size();
			//add gene to the list
			try{
				_genes.push_back(gene);
			}catch(std::exception e){
				std::cout << e.what() << std::endl;
				std::cout << "push_back _gene" << std::endl;
				std::cin.get();
			}

			//initialize the vectors for go and evidence
			try{
				_geneToGos.push_back(std::vector<std::size_t>());
			}catch(std::exception e){
				std::cout << e.what() << std::endl;
				std::cout << "push_back _geneToGos" << std::endl;
				std::cout << "push_back _geneToGos" << _geneToGos.size() << std::endl;
				std::cin.get();
			}

			try{
				_geneToGosEvidence.push_back(std::vector<GO::EvidenceCode>());
			}catch(std::exception e){
				std::cout << e.what() << std::endl;
				std::cout << "push_back _geneToGosEvidence" << std::endl;
				std::cin.get();
			}


		}//end if, first finding gene
		//get the index in constant time
		geneIndex = _stringToGene[gene];


		/*
		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "add gene" << std::endl;
			std::cout << gene << " " << goTerm  << " " << evidenceCode << std::endl;
			std::cout << "size " << _genes.size() << std::endl;
		}
		*/
		
		try{

		//first time finding term
		if(_stringToGo.find(goTerm) == _stringToGo.end()){
			//get the index for go term, next to be inserted, use vec.size()
			_stringToGo[goTerm] = _goTerms.size();
			//add goTerm to list
			_goTerms.push_back(goTerm);


			//initialize the vectors for genes and evidence
			_goToGenes.push_back(std::vector<std::size_t>());
			_goToGenesEvidence.push_back(std::vector<GO::EvidenceCode>());

		}//end if, first finding goTerm
		//get the index in constant time
		goIndex = _stringToGo[goTerm];

		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "add term" << std::endl;
			std::cout << gene << " " << goTerm  << " " << evidenceCode << std::endl;
			std::cout << "size " << _goTerms.size() << std::endl;
		}



		try{

		//get the EvidenceCode enum from the string
		GO::EvidenceCode eCode = GO::evidenceStringToCode(evidenceCode);

		try{
		//add go term (index) to gene's list
		_geneToGos.at(geneIndex).push_back(goIndex);
		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "evidence _geneToGos" << std::endl;
			std::cin.get();
		}

		try{
		//add evidence code to gene's list, in parallel with go term
		_geneToGosEvidence.at(geneIndex).push_back(eCode);
		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "evidence _geneToGosEvidence" << std::endl;
			std::cin.get();
		}



		try{
		//add gene (index) to go's list
		_goToGenes.at(goIndex).push_back(geneIndex);
		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "evidence _goToGenes" << std::endl;
			std::cout << "size      " << _goToGenes.size() << std::endl;
			std::cout << "size sub  " << _goToGenes.at(goIndex).size() << std::endl;
			std::cin.get();
		}

		try{
		//add evidence code to go's list, in parallel with gene
		_goToGenesEvidence.at(goIndex).push_back(eCode);
		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "evidence _goToGenesEvidence" << std::endl;
			std::cout << "size      " <<  _goToGenesEvidence.size() << std::endl;
			std::cout << "size sub  " <<  _goToGenesEvidence.at(goIndex).size() << std::endl;
			std::cin.get();
		}


		}catch(std::exception e){
			std::cout << e.what() << std::endl;
			std::cout << "add evidence" << std::endl;
			std::cout << gene << " " << goTerm  << " " << evidenceCode << std::endl;
			std::cout << "size " << _goTerms.size() << std::endl;
			std::cin.get();
		}
	
	}//end method addAssciation


	//! This method tests the existence of a term in the database.
	/*!
		A helper method to check if a term exists in the database.
	*/
	inline bool hasGoTerm(const std::string &goTerm){
		return _stringToGo.find(goTerm) != _stringToGo.end();
	}


	//! This method tests the existence of a gene in the database.
	/*!
		A helper method to check if a gene exists in the database.
	*/
	inline bool hasGene(const std::string &gene){
		return _stringToGene.find(gene) != _stringToGene.end();
	}

	//! This method returns all the go terms in the database
	/*!
		A helper method to return all the GO terms in the databse
	*/
	inline std::vector<std::string> getAllGoTerms(){
		return _goTerms;
	}

	//! This method returns all genes in the database
	/*!
		A helper method to return all the genes in the databse
	*/
	inline std::vector<std::string> getAllGenes(){
		return _genes;
	}


	//! This method gets the go terms for a gene.
	/*!
		A helper method to return, for a gene, a list of go terms as a vector of strings.
	*/
	inline std::vector<std::string> getGoTermsForGene(const std::string &gene){
		//temparary storage variable
		std::vector<std::string> goTerms;

		//test if gene exists,prevent key error
		if(hasGene(gene)){
			std::size_t index = _stringToGene[gene];

			//get an iterator of the go indices.
			std::vector<std::size_t>::iterator iter = _geneToGos.at(index).begin();

			//move other the indices placeing the correct go in the list
			for(;iter != _geneToGos.at(index).end(); ++iter){
				goTerms.push_back(_goTerms.at(*iter));
			}

		}

		return goTerms;
		
	}//end method, getGoTermsForGene


	//! This method gets the go terms for a gene within the specified onotlogy.
	/*!
		A helper method to return a list of go terms as a set of strings for a gene
		given the sub ontology BP, MF, or CC.
	*/
	inline boost::unordered_set<std::string> getGoTermsForGeneByOntology(const std::string &gene, GO::Onto filterOntology, GoGraph *G){
		//temparary storage variable
		boost::unordered_set<std::string> goTerms;

		//test if gene exists,prevent key error
		if(hasGene(gene)){
			std::size_t index = _stringToGene[gene];

			//get an iterator of the go indices.
			std::vector<std::size_t>::iterator iter = _geneToGos.at(index).begin();

			//move other the indices placeing the correct go in the list
			for(;iter != _geneToGos.at(index).end(); ++iter){
				std::string term = _goTerms.at(*iter);
				if(G->getTermOntology(term) == filterOntology)
				goTerms.insert(term);
			}

		}

		return goTerms;
		
	}

	//! This method gets the biological process go terms for a gene.
	/*!
		A helper method to return a list of BP go terms for a gene.
	*/
	inline boost::unordered_set<std::string> getGoTermsForGeneBP(const std::string &gene, GoGraph *G){
		return getGoTermsForGeneByOntology(gene, GO::BP, G);
	}

	//! This method gets the molecular function go terms for a gene.
	/*!
		A helper method to return a list of MF go terms for a gene.
	*/
	inline boost::unordered_set<std::string> getGoTermsForGeneMF(const std::string &gene, GoGraph *G){
		return getGoTermsForGeneByOntology(gene, GO::MF, G);
	}

	//! This method gets the cellular component go terms for a gene.
	/*!
	A helper method to return a list of CC go terms for a gene.
	*/
	inline boost::unordered_set<std::string> getGoTermsForGeneCC(const std::string &gene, GoGraph *G){
		return getGoTermsForGeneByOntology(gene, GO::CC, G);
	}

	//! A method to get the evidence codes for a list of go terms.
	/*!
		This method returns the evidence codes for a list of go terms. It parallels the 
		  getGoTermsForGene method and is used for printing and testing.
	*/
	inline std::vector<std::string> getGoTermsEvidenceForGene(const std::string &gene){
		std::vector<std::string> eCodes;
		if(hasGene(gene)){
			std::size_t index = _stringToGene[gene];
			std::vector<GO::EvidenceCode>::iterator iter = _geneToGosEvidence.at(index).begin();
			for(;iter != _geneToGosEvidence.at(index).end(); ++iter){
				std::string code = GO::evidenceStringCodes[*iter];
				eCodes.push_back(code);
			}
		}
		return eCodes;
	}

	//! This method gets the genes for a go term.
	/*!
		A helper method to return, for a go term, a list of genes as a vector of strings.
	*/
	inline std::vector<std::string> getGenesForGoTerm(const std::string &goTerm){
		//temparary storage variable
		std::vector<std::string> genes;

		//test if gene exists,prevent key error
		if(hasGoTerm(goTerm)){
			std::size_t index = _stringToGo[goTerm];

			//get an iterator of the go indices.
			std::vector<std::size_t>::iterator iter = _goToGenes.at(index).begin();

			//move other the indices placeing the correct go in the list
			for(;iter != _goToGenes.at(index).end(); ++iter){
				genes.push_back(_genes.at(*iter));
			}

		}

		return genes;
	}//end method, getGenesForGoTerm

	//! This method adds the genes for a go term to a set.
	/*!
		A helper method to add genes associated to a term to a set of genes.
		  Used in enrichment calculation
	*/
	inline void addGenesForGoTerm(const std::string &goTerm,boost::unordered_set<std::string> &geneSet){
		//test if gene exists,prevent key error
		if(hasGoTerm(goTerm)){
			std::size_t index = _stringToGo[goTerm];

			//get an iterator of the go indices.
			std::vector<std::size_t>::iterator iter = _goToGenes.at(index).begin();

			//move other the indices placeing the correct go in the list
			for(;iter != _goToGenes.at(index).end(); ++iter){
				geneSet.insert(_genes.at(*iter));
			}
		}
	}

	//! A method to get the evidence codes for a list of genes.
	/*!
		This method returns the evidence codes for a list of genes. It parallels the 
		  getGenesForGoTerm method and is used for printing and testing.
	*/
	inline std::vector<std::string> getGenesEvidenceForGoTerm(const std::string &goTerm){
		std::vector<std::string> eCodes;
		if(hasGoTerm(goTerm)){
			std::size_t index = _stringToGo[goTerm];
			std::vector<GO::EvidenceCode>::iterator iter = _goToGenesEvidence.at(index).begin();
			for(;iter != _goToGenesEvidence.at(index).end(); ++iter){
				std::string code = GO::evidenceStringCodes[*iter];
				eCodes.push_back(code);
			}
		}
		return eCodes;
	}


	//! A method to get the number of annotations of a particular go term.
	/*!
		This method returns the number of annotations for a go term. Queries the data base
		  rather than extracting a vector. Used to calculate information content.
	*/
	inline std::size_t getNumAnnotationsForGoTerm(const std::string &goTerm){
		if (!hasGoTerm(goTerm)){
			return 0;
		}
		std::size_t index = _stringToGo[goTerm];
		return _goToGenes.at(index).size();
	}

	//! A method to get the number of annotations of a particular gene.
	/*!
		This method returns the number of annotations for a go term. Queries the data base
		  rather than extracting a vector.
	*/
	inline std::size_t getNumAnnotationsForGene(const std::string &gene){
		if (!hasGene(gene)){
			return 0;
		}
		std::size_t index = _stringToGene[gene];
		return _geneToGos.at(index).size();
	}

	//! A helper method to get the number of genes in the db
	/*!
		This method reutrns the size of the _genes vector.
	*/
	inline std::size_t getNumGenes(){
		return _genes.size();
	}


	//! A helper method to get the number of go terms in the db
	/*!
		This method reutrns the size of the _goTerms vector.
	*/
	inline std::size_t getNumGoTerms(){
		return _goTerms.size();
	}

	//!	A helper method to return only the terms of the give ontology.
	/*!
		Returns only those terms used that occur for the given ontology.
	*/
	inline std::vector<std::string> getOntologyTerms(GoGraph* graph, GO::Onto ontology){
		std::vector<std::string> ontologyTerms;
		//Use only terms in the annotation database, this will save on space and computation time.
		std::vector<std::string>::iterator it;
		for (it = _goTerms.begin(); it != _goTerms.end(); ++it){
			if (graph->getTermOntology(*it) == ontology){
				ontologyTerms.push_back(*it);
			}
		}
		return ontologyTerms;
	}

};
#endif

