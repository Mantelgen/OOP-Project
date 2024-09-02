#pragma once
#include "Service.h"
#include "Contract.h"
#include <iostream>
using std::cin;
using std::cout;

class Console {
private:
	Service& service;
public:
	//Constructor cu parametru
	Console(Service& service) :service{ service } {};
	//Constructor de copiere
	Console(const Console& cons) = delete;
	//Destructor
	~Console() = default;

	//Functie de adaugare a unei discipline
	void UIAdd() noexcept;
	//Functie de stergere a unei discipline
	void UIDelete() noexcept;
	//Functie de modificare a unei discipline
	void UIUpdate() noexcept;
	//Functie de cautare a unei discipline
	void UIFind() noexcept;

	//Functie de filtrare a disciplinelor dupa nr de ore
	void UIFilterAfterNumClasses() noexcept;
	//Functie de filtrare a disciplinelor dupa numele profesorului
	void UIFilterAfterTeacher() noexcept;

	//Functie de realizare a unui raport dupa tip
	void UIReportType() noexcept;
	//Functie de inglobeaza toate tipurile de sortari
	void UISort() noexcept;
	//Meniul pentru realizarea unui contract
	void UIMenuContract()noexcept;
	//Functie pentru obtinerea tuturor disciplinelor
	void UIGetAll();
	//Functie pentru undo
	void UIUndo()noexcept;
	//Functie de adaugare a unor dicipline random de test
	void addTeste();
	//Meniul principal
	void run()noexcept;
};
