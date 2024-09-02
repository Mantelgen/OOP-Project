#pragma once
#include "Repository.h"
#include "Observer.h"
#include <random>
#include <fstream>
#include <chrono>
#include <iterator>
using std::find_if;
using std::shuffle;

class Contract:public Subject {
private:
	vector<Discipline> contract;
	vector<Discipline> repo;
public:
	//Constructor implicit
	Contract() = default;
	//Constructor pentru contract cu parametru
	Contract(vector<Discipline> repo): repo{ repo } {};
	//Destructor
	~Contract() = default;
	//Constructor de copiere
	Contract(const Contract& ct) = default;
	/*
	* Functie de stergere a contractului
	*/
	void deleteContract();
	/*
	* Functie de adaugare a unei discipline in contract
	* name - numele disciplinei de adaugat
	* arunca RepoException daca nu exista o disciplina cu numele dat
	*/
	void addDisciplineContract  (const string& name);
	/*
	* Functie de adaugare a unui numar random de discipline in contract(sau adauga toate disciplinele daca sunt mai putine)
	* numDisciplines - numarul de discipline de adaugat
	*/
	void addRandomDisiplinesContract  (unsigned long long numDisciplines);
	/*
	* Functie de export a contractului in format CSV
	* file_name - numele fisierului in care se exporta contractul
	*/
	void exportContractCSV(string file_name);
	/*
	* Functie de export a contractului in format HTML
	* file_name - numele fisierului in care se exporta contractul
	*/
	void exportContractHTML(string file_name);
	/*
	* Functie care returneaza toate disciplinele din contract
	* returneaza un vector de discipline care reprezinta contractul
	*/
	const vector<Discipline>& getAllContract();

};
