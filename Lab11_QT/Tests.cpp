#include "Tests.h"
#include <assert.h>

void Tests::testDiscipline() {
	Discipline dsp{ "ASC","Mihai","Optional", 23 };
	Discipline dsp2;
	dsp2 = dsp;
	assert(dsp == dsp2);
	assert(!(dsp != dsp2));

	assert(dsp.getName() == "ASC");
	assert(dsp.getTeacher() == "Mihai");
	assert(dsp.getType() == "Optional");
	assert(dsp.getNumClasses() == 23);

	assert(dsp.setName("POO") == "POO");
	assert(dsp.setTeacher("Mihai") == "Mihai");
	assert(dsp.setType("Obligatoriu") == "Obligatoriu");
	assert(dsp.setNumClasses(24) == 24);

	cout << dsp;

};

void Tests::testValidator() {
	Discipline dsp{ "","","",0 };
	Validator vl;

	try {
		vl.validateDiscipline(dsp);
	}
	catch (ValidationException& ve) {

		cout << ve.getMessage();
	}
	Discipline dsp2{ "2","2","2",0 };
	try {
		vl.validateDiscipline(dsp2);
	}
	catch (ValidationException) {
		assert(true);
	}
	Discipline dsp1{ "ASC","Mihai","Optionala", 23 };
	vl.validateDiscipline(dsp1);
};

void Tests::testVectorRepository() {
	VectorRepository vr;
	Discipline dsp{ "ASC","Mihai","Optionala", 23 };
	Discipline dsp2{ "POO","Mihai","Obligatorie", 24 };
	Discipline dsp3{ "ASC","Mihai","Obligatorie", 24 };
	try {
		vr.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	vr.addDiscipline(dsp);
	try
	{
		vr.addDiscipline(dsp);
	}
	catch (RepoException ev)
	{
		assert(true);
	}

	try {
		vr.updateDiscipline(dsp2);
	}
	catch (RepoException ev) {
		assert(true);
	}
	vr.updateDiscipline(dsp3);
	vr.addDiscipline(dsp2);
	assert(vr.getAll().size() == 2);
	vr.deleteDiscipline("ASC");
	assert(vr.getAll().size() == 1);
	try {
		vr.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
		cout << ev.getMessage();
	}
	vr.deleteDiscipline("POO");
	assert(vr.getAll().size() == 0);
};

void Tests::testMapRepository() {
	MapRepository vr{ 10000000 };
	Discipline dsp{ "ASC","Mihai","Optionala", 23 };
	Discipline dsp2{ "POO","Mihai","Obligatorie", 24 };
	Discipline dsp3{ "ASC","Mihai","Obligatorie", 24 };
	try {
		vr.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	vr.addDiscipline(dsp);
	try
	{
		vr.addDiscipline(dsp);
	}
	catch (RepoException ev)
	{
		assert(true);
	}

	try {
		vr.updateDiscipline(dsp2);
	}
	catch (RepoException ev) {
		assert(true);
	}

	vr.updateDiscipline(dsp3);
	vr.addDiscipline(dsp2);
	vr.deleteDiscipline("ASC");
	assert(vr.getAll().size() == 1);

	try {
		vr.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	vr.deleteDiscipline("POO");
	assert(vr.getAll().size() == 0);


	MapRepository vr2{ 0 };
	try {
		vr2.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	try
	{
		vr2.addDiscipline(dsp);
	}
	catch (RepoException ev)
	{
		assert(true);
	}
	try
	{
		vr2.addDiscipline(dsp);
	}
	catch (RepoException ev)
	{
		assert(true);
	}

	try {
		vr2.updateDiscipline(dsp2);
	}
	catch (RepoException ev) {
		assert(true);
	}
	try {
		vr2.updateDiscipline(dsp3);
	}
	catch (RepoException ev) {
		assert(true);
	}
	try {
		vr2.addDiscipline(dsp2);
	}
	catch (RepoException ev) {
		assert(true);
	}

	try {
		vr2.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	try {
		vr2.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	try {
		vr2.deleteDiscipline("POO");
	}
	catch (RepoException ev) {
		assert(true);
	}
	try {
		vr2.getAll();
	}
	catch (RepoException ev) {
		assert(true);
	}

};
void Tests::testRepoFile() {
	RepoFile vr{ "teste.txt" };
	Discipline dsp{ "ASC","Mihai","Optionala", 23 };
	Discipline dsp2{ "POO","Mihai","Obligatorie", 24 };
	Discipline dsp3{ "ASC","Mihai","Obligatorie", 24 };
	try {
		vr.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
	}
	vr.addDiscipline(dsp);
	try
	{
		vr.addDiscipline(dsp);
	}
	catch (RepoException ev)
	{
		assert(true);
	}

	try {
		vr.updateDiscipline(dsp2);
	}
	catch (RepoException ev) {
		assert(true);
	}
	vr.updateDiscipline(dsp3);
	vr.addDiscipline(dsp2);
	assert(vr.getAll().size() == 2);
	vr.deleteDiscipline("ASC");
	assert(vr.getAll().size() == 1);
	try {
		vr.deleteDiscipline("ASC");
	}
	catch (RepoException ev) {
		assert(true);
		cout << ev.getMessage();
	}
	vr.deleteDiscipline("POO");
	assert(vr.getAll().size() == 0);
}
void Tests::testService() {
	VectorRepository vr;
	Discipline dsp{ "ASC","Mihai","Optionala", 23 };
	Discipline dsp2{ "POO","Mihai","Obligatorie", 24 };
	Discipline dsp3{ "ASC","Mihai","Obligatorie", 30 };
	Validator val;
	Service sv{ &vr,val };
	sv.addDisciplineService("ASC", "Mihai", "Optionala", 23);
	try {
		sv.addDisciplineService("ASC", "Mihai", "Optionala", 23);
	}
	catch (RepoException ev) {
		assert(true);
	}
	try {
		sv.addDisciplineService("OOP", "Ion", "", 0);
	}
	catch (ValidationException ev) {
		assert(true);
	}
	assert(sv.getAll().size() == 1);
	assert(sv.findDisciplineService("ASC") == dsp);
	try {
		sv.findDisciplineService("POO");
	}
	catch (ServiceException ev) {
		assert(true);
		cout << ev.getMsg();
	}
	try {
		sv.updateDisciplineService("POO", "Mihai", "Obligatorie", 24);
	}
	catch (ServiceException ev) {
		assert(true);
	}
	sv.updateDisciplineService("ASC", "Mihai", "Obligatorie", 30);
	sv.addDisciplineService("POO", "Ionut", "Obligatorie", 24);
	sv.addDisciplineService("FP", "Ionut", "Obligatorie", 12);
	sv.addDisciplineService("Os", "Mihai", "Facultativa", 23);
	VectorDis rez;
	try {
		rez = sv.filterAfterNumClasses(5);
	}
	catch (ServiceException ev) {
		assert(true);
	}
	rez = sv.filterAfterNumClasses(24);
	assert(rez.size() == 3);
	try {
		rez = sv.filterAfterTeacher("Mircea");
	}
	catch (ServiceException ev) {
		assert(true);
	}
	rez = sv.filterAfterTeacher("Ionut");
	assert(rez.size() == 2);
	rez = sv.sortByName();
	assert(rez[1].getName() < rez[2].getName());
	rez = sv.sortByNumClasses();
	assert(rez[0].getNumClasses() < rez[1].getNumClasses() && rez[1].getNumClasses() < rez[2].getNumClasses());
	rez = sv.sortByTeacherAndType();
	assert(rez[2].getTeacher() == rez[3].getTeacher() && rez[2].getType() < rez[3].getType());

	map<string, VectorDis> rez2 = sv.reportType();
	assert(rez2["Obligatorie"].size() == 3);
	assert(rez2["Facultativa"].size() == 1);

	sv.deleteDisciplineService("ASC");
};
void Tests::testUndo() {
	VectorRepository vr;
	Validator val;
	Service sv{ &vr,val };
	Discipline dsp{ "POO", "Ionut", "Obligatorie", 24 };
	sv.addDisciplineService("POO", "Ionut", "Obligatorie", 24);
	sv.updateDisciplineService("POO", "Ionut", "Obligatorie", 25);
	sv.deleteDisciplineService("POO");
	sv.undo();
	assert(sv.getAll().size() == 1);
	sv.undo();
	assert(sv.getAll()[0] == dsp);
	sv.undo();
	assert(sv.getAll().size() == 0);
	try {
		sv.undo();
	}
	catch (ServiceException ev) {
		assert(true);
	}

};
void Tests::testContract() {
	VectorRepository vr;
	Discipline dsp{ "ASC","Mihai","Optionala", 23 };
	Discipline dsp2{ "POO","Mihai","Obligatorie", 24 };
	Discipline dsp3{ "FP","Mihai","Facultativa", 30 };
	vr.addDiscipline(dsp);
	vr.addDiscipline(dsp2);
	vr.addDiscipline(dsp3);
	Contract t;
	Contract ct{ vr.getAll() };
	ct.addDisciplineContract("ASC");
	try {
		ct.addDisciplineContract("Gogu");
	}
	catch (RepoException ev) {
		assert(true);
	}
	ct.deleteContract();
	ct.addRandomDisiplinesContract(2);
	assert(ct.getAllContract().size() == 2);
	ct.exportContractCSV("test");
	ct.exportContractHTML("test");
};
