#pragma once
#include "Discipline.h"
#include <vector>
#include <map>
using std::vector;
using std::map;

class RepoException {
private:
	string message;
public:
	//Constructor pentru exceptie
	//Input: message - mesajul exceptiei
	RepoException(const string& message) :message{ message } {};

	//Operator pentru afisare
	friend ostream& operator <<(ostream& out, const RepoException& re) {
		out << re.message;
		return out;
	};

	//Getter pentru mesajul exceptiei
	//Output: message - mesajul exceptiei
	string getMessage() const noexcept { return message; };
};
class AbstractRepository {
public:
	//Constructor default
	AbstractRepository() = default;
	//Destructor default
	virtual ~AbstractRepository() = default;
	/*
		Adauga o disciplina in lista
	*Input: dsp - disciplina de adaugat
	*Output: -
	*Adauga o disciplina in lista
	*Exceptie: RepoException - daca disciplina exista deja in lista
	*/
	virtual void addDiscipline(const Discipline& dsp) = 0;
	/*
		Sterge o disciplina din lista
	*Input: name - numele disciplinei de sters
	* Output: -
	* Sterge o disciplina din lista
	* Exceptie: RepoException - daca disciplina nu exista in lista
	*/
	virtual void deleteDiscipline(const string& name) = 0;
	/*
		Modifica o disciplina din lista
	*Input: dsp - disciplina de modificat
	*Output: -
	* Modifica o disciplina din lista
	* Exceptie: RepoException - daca disciplina nu exista in lista
	*/
	virtual void updateDiscipline(const Discipline& dsp) = 0;
	/*
			Returneaza toate disciplinele din lista
	*Input: -
	* Output: vector<Discipline> - lista cu toate disciplinele
	* Returneaza toate disciplinele din lista
	* Exceptie: -
	*/
	virtual vector<Discipline> getAll() const = 0;
};

class VectorRepository :public AbstractRepository {
private:
	vector<Discipline> repoDisciplines;
public:
	//Constructor default
	VectorRepository() = default;
	//Destructor default
	~VectorRepository() = default;
	//Adauga o disciplina in lista
	void addDiscipline(const Discipline& dsp) override;
	//Sterge o disciplina din lista
	void deleteDiscipline(const string& name) override;
	//Modifica o disciplina din lista
	void updateDiscipline(const Discipline& dsp) override;
	//Returneaza toate disciplinele din lista
	vector<Discipline> getAll() const  override;
};


class MapRepository :public AbstractRepository {
private:
	map<string, Discipline> repoDisciplines;
	double prob;
public:
	//Constructor cu parametri pentru MapRepository
	MapRepository(const double& probl) :prob{ probl } {};
	//Destructor default
	~MapRepository() = default;
	//Adauga o disciplina in lista
	//Exceptie: RepoException - daca probabilitatea creata random este mai mare decat prob
	void addDiscipline(const Discipline& dsp) override;
	//Sterge o disciplina din lista
	//Exceptie: RepoException - daca probabilitatea creata random este mai mare decat prob
	void deleteDiscipline(const string& name) override;
	//Modifica o disciplina din lista
	//Exceptie: RepoException - daca probabilitatea creata random este mai mare decat prob
	void updateDiscipline(const Discipline& dsp) override;
	//Returneaza toate disciplinele din lista
	//Exceptie: RepoException - daca probabilitatea creata random este mai mare decat prob
	vector<Discipline> getAll() const override;
};

class RepoFile :public VectorRepository {
private:
	string fileName;
	void load_from_file();
	void write_to_file();
public:
	explicit RepoFile(string fileName) :VectorRepository(), fileName{ fileName } {
		load_from_file();
	}
	void addDiscipline(const Discipline& dsp) override
	{
		VectorRepository::addDiscipline(dsp);
		write_to_file();
	}
	void deleteDiscipline(const string& name) override
	{
		VectorRepository::deleteDiscipline(name);
		write_to_file();
	}
	void updateDiscipline(const Discipline& dsp) override {
		VectorRepository::updateDiscipline(dsp);
		write_to_file();
	}
	//Returneaza toate disciplinele din lista
	//Exceptie: RepoException - daca probabilitatea creata random este mai mare decat prob
	vector<Discipline> getAll() const override {
		return VectorRepository::getAll();
	}
};
