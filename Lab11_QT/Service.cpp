#include "Service.h"
#include <algorithm>
using std::copy_if;
using std::distance;
using std::sort;
using std::map;

void Service::addDisciplineService(const string& name, const string& teacher, const string& type, const unsigned int numClasses) {
	Discipline dsp{ name, teacher, type, numClasses };
	vl.validateDiscipline(dsp);
	repo->addDiscipline(dsp);
	undoActions.push_back(std::make_unique<UndoAdd>(repo, dsp));
};

void Service::deleteDisciplineService(const string& name) {
	undoActions.push_back(std::make_unique<UndoDelete>(repo, findDisciplineService(name)));
	repo->deleteDiscipline(name);
};

void Service::updateDisciplineService(const string& name, const string& teacher, const string& type, const unsigned int numClasses) {
	Discipline dsp{ name, teacher, type, numClasses };
	vl.validateDiscipline(dsp);
	undoActions.push_back(std::make_unique<UndoUpdate>(repo, findDisciplineService(name)));
	repo->updateDiscipline(dsp);
};

const Discipline Service::findDisciplineService(const string& name) const {
	const VectorDis& all = repo->getAll();
	auto it = std::find_if(all.begin(), all.end(), [name](const Discipline& dsp) {return dsp.getName() == name; });
	if (it == all.end())
		throw ServiceException("Disciplina nu exista!");
	return *it;
}

VectorDis Service::filterAfterNumClasses(const unsigned int numClasses) const {
	const VectorDis& all = repo->getAll();
	VectorDis result(all.size());
	auto it = copy_if(all.begin(), all.end(), result.begin(), [numClasses](const Discipline& i) {
		return i.getNumClasses() <= numClasses;
		});
	result.resize(distance(result.begin(), it));
	if (result.size() == 0)
		throw ServiceException("Nu exista disipline cu nr de ore mai mici decat numarul cerut!");
	return result;
};
VectorDis Service::filterAfterTeacher(const string& teacher)const {
	const VectorDis& all = repo->getAll();
	VectorDis result(all.size());
	auto it = copy_if(all.begin(), all.end(), result.begin(), [teacher](const Discipline& i) {
		return i.getTeacher() == teacher;
		});
	result.resize(distance(result.begin(), it));
	if (result.size() == 0)
		throw ServiceException("Nu exista discipline cu profesorul cerut! ");
	return result;
};


VectorDis Service::sortByName() const noexcept {
	VectorDis all = repo->getAll();
	sort(all.begin(), all.end(), [](const Discipline& a, const Discipline& b) {
		return a.getName() < b.getName();
		});
	return all;
};
VectorDis Service::sortByNumClasses()const noexcept {
	VectorDis all = repo->getAll();
	sort(all.begin(), all.end(), [](const Discipline& a, const Discipline& b) {
		return a.getNumClasses() < b.getNumClasses();
		});
	return all;
};
VectorDis Service::sortByTeacherAndType()const noexcept {
	VectorDis all = repo->getAll();
	sort(all.begin(), all.end(), [](const Discipline& a, const Discipline& b) {
		return (a.getTeacher() < b.getTeacher()) || (a.getTeacher() == b.getTeacher() && a.getType() < b.getType());
		});
	return all;
}

map<string, VectorDis>Service::reportType() const noexcept {
	map<string, VectorDis>report;
	VectorDis result = repo->getAll();
	for (auto& i : result) {
		report[i.getType()].push_back(i);
	}
	return report;
}

void Service::undo() {
	if (undoActions.empty())
		throw ServiceException("Nu avem la ce da undo!");
	undoActions.back()->doUndo();
	undoActions.pop_back();
}
