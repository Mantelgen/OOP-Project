#include "Repository.h"
#include <time.h>
#include <iomanip>
#include <random>
#include<fstream>
#include<sstream>
//VECTOR REPOSITORY

void VectorRepository::addDiscipline(const Discipline& dsp) {
	for (auto& d : repoDisciplines)
		if (d.getName() == dsp.getName())
			throw RepoException("Disciplina exista deja in lista");
	repoDisciplines.push_back(dsp);
};
void VectorRepository::deleteDiscipline(const string& name) {
	if (repoDisciplines.size() == 0)
		throw RepoException("Lista este goala");
	for (std::vector<Discipline>::iterator it = repoDisciplines.begin(); it != repoDisciplines.end(); ++it)
		if (it->getName() == name) {
			repoDisciplines.erase(it);
			return;
		}
	throw RepoException("Disciplina nu exista in lista");
};
void VectorRepository::updateDiscipline(const Discipline& dsp) {
	for (auto& d : repoDisciplines)
		if (d.getName() == dsp.getName()) {
			d = dsp;
			return;
		}
	throw RepoException("Disciplina nu exista in lista");
};
vector<Discipline> VectorRepository::getAll() const {
	return repoDisciplines;
};

//MAP REPOSITORY

void MapRepository::addDiscipline(const Discipline& dsp) {
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0, 1);

	double random = dist(rnd);
	//cout << std::fixed << std::setprecision(10) << random << endl;
	if (random >= prob)
		throw RepoException("Nu s-a putut efectua operatia. AYAE. Probabilitatea:" + std::to_string(random));
	if (repoDisciplines.find(dsp.getName()) != repoDisciplines.end())
		throw RepoException("Disciplina exista deja in lista");
	repoDisciplines.insert(std::pair<string, Discipline>(dsp.getName(), dsp));
};
void MapRepository::deleteDiscipline(const string& name) {
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0, 1);

	double random = dist(rnd);
	//cout << std::fixed << std::setprecision(10) << random << endl;
	if (random >= prob)
		throw RepoException("Nu s-a putut efectua operatia. AYAE. Probabilitatea:" + std::to_string(random));
	if (repoDisciplines.size() == 0)
		throw RepoException("Lista este goala");
	if (repoDisciplines.find(name) == repoDisciplines.end())
		throw RepoException("Disciplina nu exista in lista");
	repoDisciplines.erase(name);
};
void MapRepository::updateDiscipline(const Discipline& dsp) {
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0, 1);

	double random = dist(rnd);
	//cout << std::fixed << std::setprecision(10) << random << endl;
	if (random >= prob)
		throw RepoException("Nu s-a putut efectua operatia. AYAE. Probabilitatea:" + std::to_string(random));
	if (repoDisciplines.find(dsp.getName()) == repoDisciplines.end())
		throw RepoException("Disciplina nu exista in lista");
	repoDisciplines[dsp.getName()] = dsp;
};
vector<Discipline> MapRepository::getAll() const {
	std::default_random_engine rnd{ std::random_device{}() };
	std::uniform_real_distribution<double> dist(0, 1);

	double random = dist(rnd);
	//cout << std::fixed << std::setprecision(10) << random << endl;
	if (random >= prob)
		throw RepoException("Nu s-a putut efectua operatia. AYAE. Probabilitatea:" + std::to_string(random));
	vector<Discipline> all;
	for (auto& d : repoDisciplines)
		all.push_back(d.second);
	return all;
};

void RepoFile::load_from_file() {
	std::ifstream in(fileName);
	if (!in.is_open()) throw RepoException("Eroare la deschiderea fisierului!!!");

	std::string line;
	while (std::getline(in, line)) {
		std::istringstream iss(line);
		std::string curent;
		int item_no =0;
		std::string name, teacher, type;
		unsigned int numClasses=0;

		while (std::getline(iss, curent, ','))
		{

			if (item_no == 0) name = curent;
			if (item_no == 1) teacher = curent;
			if (item_no == 2) type = curent;
			if (item_no == 3) numClasses = stoi(curent);
			item_no++;
		}
		Discipline o{ name, teacher, type, numClasses };
		VectorRepository::addDiscipline(o);
	}
	in.close();
}
void RepoFile::write_to_file() {
	std::ofstream out(fileName);
	if (!out.is_open())throw RepoException("Eroare la deschiderea fisierului!!!");

	for (auto& o : VectorRepository::getAll()) {
		out << o.getName() << ",";
		out << o.getTeacher() << ",";
		out << o.getType() << ",";
		out << o.getNumClasses();
		out << std::endl;
	}
	out.close();
}
