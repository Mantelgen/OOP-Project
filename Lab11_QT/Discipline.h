#pragma once
#include <iostream>
#include <string>
using std::cout;
using std::string;
using std::ostream;
using std::endl;

class Discipline {
private:
	string name;
	string teacher;
	string type;
	unsigned int numClasses=0;
public:
	//Constructor implicit
	Discipline() = default;
	//Constructor cu parametri
	Discipline(const string& name, const string& teacher, const string& type, const unsigned int numClasses) :name{ name }, teacher{ teacher }, type{ type }, numClasses{ numClasses } {};
	//Constructor de copiere
	Discipline(const Discipline& d) :name{ d.name }, teacher{ d.teacher }, type{ d.type }, numClasses{ d.numClasses } {
		//cout << "Copy created" << endl;
	};
	//Destructor
	~Discipline() = default;

	//Getter pentru Nume/Profesor/Tip/Nr de ore
	string getName() const noexcept { return name; };
	string getTeacher() const noexcept { return teacher; };
	string getType() const noexcept { return type; };
	unsigned int getNumClasses() const noexcept { return numClasses; };

	/*Setter pentru Nume / Profesor / Tip / Nr de ore
	* pre: noile valori ale campurilor respcective
	* return: noua valoare a campului respectiv
	*/
	string setName(const string& newName) noexcept;
	string setTeacher(const string& newTeacher) noexcept;
	string setType(const string& newType) noexcept;
	unsigned int setNumClasses(const unsigned int newNumClassess) noexcept;
	
	//Operatori de atribuire si comparare
	/* Operator de atribuire
	*pre: d - disciplina care se atribuie
	*post: disciplina curenta are aceleasi valori ca si d
	*/
	Discipline& operator =(const Discipline& d); 
	/* Operator de egalitate
	*pre: d - disciplina care se compara cu disciplina curenta
	*post: true, daca toate campurile sunt egale, false in caz contrar
	*/
	bool operator ==(const Discipline& d) const noexcept; 
	/*
	* Operator de diferenta
	* pre: d - disciplina care se compara cu disciplina curenta
	* post: true, daca cel putin un camp este diferit, false in caz contrar
	*/
	bool operator !=(const Discipline& d) const noexcept;

	//Operator de afisare 
	friend ostream& operator <<(ostream& out, const Discipline& d) {
		out << "Disciplina: " << d.getName() << ", " << d.getTeacher() << ", " << d.getType() << ", " << d.getNumClasses() << endl;
		return out;
	};

};
