#include "Contract.h"

void Contract::deleteContract() {
	contract.clear();
	notify();
};
const vector<Discipline>& Contract::getAllContract() {
	return contract;
}
void Contract::addDisciplineContract(const string& name) {
	const vector<Discipline>& v = repo;
	auto it = find_if(v.begin(), v.end(), [name](const Discipline& dsp) {
		return dsp.getName() == name;
		});
	if (it == v.end())
		throw RepoException("Nu exista o materie cu numele dat!");
	contract.push_back(*it);
	notify();
};
void Contract::addRandomDisiplinesContract(unsigned long long numDisciplines) {
	 vector<Discipline> v = repo;
	shuffle(v.begin(), v.end(), std::default_random_engine(std::random_device{}()));
	while (contract.size() < numDisciplines && v.size() > 0) {
		contract.push_back(v.back());
		v.pop_back();
	}
	notify();
};

void Contract::exportContractCSV(string file_name) {
	file_name = file_name + ".csv";
	std::ofstream fout(file_name, std::ios::out);
	fout << "Nume" << "," << "Profesor" << "," << "Tip" << "," << "Numar Ore" << std::endl;
	for (const auto& i : contract) {
		fout << i.getName() << "," << i.getTeacher() << "," << i.getType() << "," << i.getNumClasses() << std::endl;
	}
	fout.close();
}
void Contract::exportContractHTML(string file_name) {
	file_name = file_name + ".html";
	std::ofstream fout(file_name, std::ios::out);
	for (const auto& i : contract) {
		fout << i.getName() << "," << i.getTeacher() << "," << i.getType() << "," << i.getNumClasses() << "<br>";
	}
	fout.close();
}
