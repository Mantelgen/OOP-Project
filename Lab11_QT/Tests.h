#pragma once
#include "Discipline.h"
#include "Validator.h"
#include "Repository.h"
#include "Service.h"
#include "Contract.h"
class Tests {
public:
	//Teste pentru clasa Discipline
	static void testDiscipline();
	//Teste pentru clasa Validator
	static void testValidator();
	//Teste pentru clasa VectorRepository
	static void testVectorRepository();
	//Teste pentru clasa MapRepository
	static void testMapRepository();
	//Teste pentru clasa Service
	static void testService();
	//Teste pentru clasa Undo
	static void testUndo();
	//Teste pentru clasa Contract
	static void testContract();
	//Teste pentru toate clasele
	static void testRepoFile();
	static void testAll() {
		testDiscipline();
		testValidator();
		testVectorRepository();
		testMapRepository();
		testService();
		testUndo();
		testContract();
		testRepoFile();
	};
};
