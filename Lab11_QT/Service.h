#pragma once
#include "Repository.h"
#include "Validator.h"
#include "Undo.h"
#include <iterator>
typedef vector<Discipline> VectorDis;

class ServiceException {
private:
	string msg;
public:
	//constructor cu parametru
	//mesajul de eroare va fi retinut in string-ul msg
	ServiceException(const string& msg) :msg{ msg } {};

	//Functie care returneaza mesajul de eroare
	string getMsg() { return msg; };
};


class Service {
private:
	AbstractRepository* repo;
	//VectorRepository repo;
	//MapRepository repo;
	vector<std::unique_ptr<UndoAction>> undoActions;
	Validator& vl;
public:
	//constructor cu parametri
	//repo - repository-ul de discipline
	//vl - validatorul de discipline
	Service(AbstractRepository* repo, Validator& vl) :repo{ repo }, vl{ vl } {};

	//Constructor de copiere
	Service(const Service& ot) = delete;
	//Destructor
	~Service() = default;

	/*
		 Functie care adauga o disciplina in repository
	* Input: name - numele disciplinei, teacher - numele profesorului, type - tipul disciplinei, numClasses - numarul de ore
	* Output: -
	* Exceptii: ServiceException daca disciplina nu este valida
	* Adauga si valideaza disciplina in repository
	*/
	void addDisciplineService(const string& name, const string& teacher, const string& type, const unsigned int numClasses);
	/*
	  Functie care sterge o disciplina din repository
	* Input: name - numele disciplinei de sters
	* Output: -
	* Exceptii: ServiceException daca disciplina nu exista
	* Sterge disciplina din repository
	*/
	void deleteDisciplineService(const string& name);
	/*
	 Functie care modifica o disciplina din repository care are acelasi nume cu parametrul name
	* Input: name - numele disciplinei de modificat, teacher - noul nume al profesorului, type - noul tip al disciplinei, numClasses - noul numar de ore
	* Output: -
	* Exceptii: ServiceException daca disciplina nu exista
	* Modifica disciplina din repository(numele nu se modifica)
	*/
	void updateDisciplineService(const string& name, const string& teacher, const string& type, const unsigned int numClasses);
	/*
	* Functie de cautare dupa nume
	* Input: name - numele disciplinei cautate
	* Output: disciplina cu numele name
	* Exceptii: ServiceException daca disciplina nu exista
	*/
	const Discipline findDisciplineService(const string& name) const;


	/*
	* Functie de filtrare dupa nr de ore
	* Input: numClasses - nr de ore dupa care se filtreaza
	* Output: vector cu disciplinele care au nr de ore egal cu numClasses
	*/
	VectorDis filterAfterNumClasses(const unsigned int numClasses) const;
	/*
	* Functie de filtrare dupa numeele profesorului
	* Input: teacher - numele profesorului dupa care se filtreaza
	* Output: vector cu disciplinele care au numele profesorului egal cu teacher
	*/
	VectorDis filterAfterTeacher(const string& teacher) const;
	/*
	* Functie de sortare dupa nume
	*/
	VectorDis sortByName() const noexcept;
	/*
	* Functie de sortare dupa numarul de ore
	*/
	VectorDis sortByNumClasses() const noexcept;
	/*
	* Functie de sortare dupa nume si tip
	*/
	VectorDis sortByTeacherAndType() const noexcept;

	/*
	* Functie care returneaza toate disciplinele
	* Output: vector cu toate disciplinele
	*/
	VectorDis getAll() { return repo->getAll(); };
	/*
	* Functie de undo
	* Output: -
	* Exceptii: ServiceException daca nu se poate face undo
	*/
	void undo();
	/*
	* Functie care realizeaza raportul de tipuri de discipline
	* Output: map cu tipurile de discipline si numarul de discipline de fiecare tip
	*/
	std::map<string, VectorDis> reportType() const noexcept;

};
