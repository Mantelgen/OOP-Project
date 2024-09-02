#pragma once
#include "Discipline.h"
#include <vector>
using std::vector;
class ValidationException {
private:
	vector<string> message;
public:
	//constructor cu parametru
	//mesajul de eroare va fi retinut in lista de mesaje
	ValidationException(const vector<string>& message) :message{ message } {};
	//Functie care returneaza mesajul de eroare(din vector de erori in format de string)
	string getMessage() const noexcept { 
		string fullMsg = "";
		for (const string e : message) {
			fullMsg += e + '\n';
		}
		return fullMsg;
	};
};

class Validator {
public:
	/*
	* Functie care valideaza o disciplina
	* d - disciplina de validat
	* arunca ValidationException daca disciplina nu este valida
	*/
	static void validateDiscipline(const Discipline& d) {
		vector<string> errors;
		if (d.getName().size() == 0)
			errors.push_back("Numele disciplinei nu poate fi vid");
		if (d.getName().find_first_of("0123456789?!.") != string::npos)
			errors.push_back("Numele nu poate contine caractere ilegale");
		if (d.getTeacher().size() == 0)
			errors.push_back("Numele profesorului nu poate fi vid");
		if (d.getTeacher().find_first_of("0123456789?!.") != string::npos)
			errors.push_back("Numele profesorului nu poate contine caractere ilegale");
		if (d.getType() != "Obligatorie" && d.getType() != "Optionala" && d.getType() != "Facultativa")
			errors.push_back("Tipul disciplinei nu este valid");
		if (d.getNumClasses() <= 0)
			errors.push_back("Numarul de ore nu poate fi negativ sau nul");
		if (errors.size() > 0)
			throw ValidationException{ errors };
		return;
	};
};
