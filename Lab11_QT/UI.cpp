#include "UI.h"

void Console::UIAdd()noexcept {
	string name;
	string teacher;
	string type;
	string numClasses;
	cout << "Nume materie: ";
	getline(cin, name);

	cout << "Nume profesor: ";
	getline(cin, teacher);

	cout << "Tip (Obligatorie/Optionala/Facultativa): ";
	getline(cin, type);

	cout << "Numar ore: ";
	getline(cin, numClasses);
	unsigned int intNumClasses;
	try {
		intNumClasses = stoi(numClasses, nullptr, 10);
		service.addDisciplineService(name, teacher, type, intNumClasses);
	}
	catch (std::invalid_argument) {
		cout << "Numarul de ore nu este un input valid!\n";
	}
	catch (RepoException& ev) {
		cout << ev.getMessage() << endl;
	}
	catch (ValidationException& ev) {
		cout << ev.getMessage() << endl;
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg() << endl;
	}
	
}
void Console::UIDelete()noexcept {
	string name;
	cout << "Nume materie: ";
	getline(cin, name);
	try {
		service.deleteDisciplineService(name);
		cout << "Am sters materia " << name << endl;
	}
	catch (RepoException& ev) {
		cout << ev.getMessage() <<endl;
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg() << endl;
	}
}
void Console::UIUpdate()noexcept {
	string name;
	string teacher;
	string type;
	string numClasses;
	cout << "Nume materie: ";
	getline(cin, name);
	cout << "Nume profesor: ";
	getline(cin, teacher);

	cout << "Tip (Obligatorie/Optionala/Facultativa): ";
	getline(cin, type);

	cout << "Numar ore: ";
	getline(cin, numClasses);

	unsigned int intNumClasses;
	try {
		intNumClasses = stoi(numClasses, nullptr, 10);
		service.updateDisciplineService(name, teacher, type, intNumClasses);
	}
	catch (std::invalid_argument) {
		cout << "Numarul de ore nu este un input valid! \n";
	}
	catch (RepoException& ev) {
		cout << ev.getMessage() << endl;
	}
	catch (ValidationException& ev) {
		cout << ev.getMessage() << endl;
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg() << endl;
	}
}

void Console::UIFind() noexcept {
	string name;
	cout << "Nume materie: ";
	getline(cin, name);
	cout << endl;
	try {
		Discipline result = service.findDisciplineService(name);
		cout << result;
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg() << endl;
	}
}

void Console::UIFilterAfterNumClasses() noexcept {
	string numClasses;
	cout << "Numarul de ore: ";
	getline(cin, numClasses);
	try {
		unsigned int intNumClasses;
		intNumClasses = stoi(numClasses, nullptr, 10);
		VectorDis result = service.filterAfterNumClasses(intNumClasses);
		int cnt = 0;
		for (const auto&i : result) {
			cout <<++cnt<<". "<< i;
		}
	}
	catch (std::invalid_argument) {
		cout << "Numarul de ore nu este un input valid! \n";
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg();
	}
}
void Console::UIFilterAfterTeacher() noexcept {
	string teacher;
	cout << "Numele profesorului: ";
	getline(cin, teacher);
	try {
		VectorDis result = service.filterAfterTeacher(teacher);
		int cnt = 0;
		for (const auto& i : result) {
			cout << ++cnt << ". " << i;
		}
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg()<<endl;
	}
}

void Console::UIReportType() noexcept {
	map < string, VectorDis > result = service.reportType();
	vector<string> types = {"Obligatorie", "Optionala", "Facultativa"};
	for (int i = 0; i < 3; ++i)
	{
		int cnt = 0;
		cout << types[i] << endl;
		for (const auto& dsp : result[types[i]])
		{
			cout << ++cnt << ". " << dsp;
		}
	}
}
void Console::UISort() noexcept {
	VectorDis result;
	string type;
	while (true)
	{
		cout << "Sortare dupa:\n1.Nume(nume)\n2.Numar ore(ore)\n3.Profesor si tip(prof)\n4.Return(return)\n>>>";
		getline(cin, type);
		if (type == "nume")
			result = service.sortByName();
		else if (type == "ore")
			result = service.sortByNumClasses();
		else if (type == "prof")
			result = service.sortByTeacherAndType();
		else if (type == "return")
			return;
		else
			cout << "Tip incorect. Reincercati";
		if (result.size() != 0)
		{
			string mod;
			cout << "Crescator sau descrescator?\n>>";
			getline(cin, mod);
			if (mod != "desc" && mod != "cresc")
				cout << "Mod incorect!\n";
			else
			{
				if (mod == "desc")
					std::reverse(result.begin(), result.end());
				int cnt = 0;
				for (const auto& i : result)
					cout << ++cnt << ". " << i;
			}
		}

	}
}
void Console::UIMenuContract()noexcept {
	Contract contract{ service.getAll() };
	string cmd;
	string name;
	string numDis;
	string extension;
	while (true) {
		cout << "Meniu contracte\n1.Adauga disciplina(add)\n2.Adauga discipline random(random)\n3.Sterge contract(delete)\n4.Exporta contract(exp)\n5.Back(back)\n>>>";
		getline(cin, cmd);
		if (cmd == "add") {
			cout << "Numele materiei de adaugat: ";
			getline(cin, name);
			try {
				contract.addDisciplineContract(name);
				VectorDis all = contract.getAllContract();
				int cnt = 0;
				for (const auto& i : all) {
					cout << ++cnt << ". " << i;
				}
			}
			catch (RepoException& ev) {
				cout << ev.getMessage() << endl;
			}
		}
		else if (cmd == "random") {
			cout << "Numarul de materii din contract: ";
			getline(cin, numDis);
			try {
				unsigned int intNumDis;
				intNumDis = stoi(numDis, nullptr, 10);
				contract.deleteContract();
				contract.addRandomDisiplinesContract(intNumDis);
				VectorDis all = contract.getAllContract();
				int cnt = 0;
				for (const auto& i : all) {
					cout << ++cnt << ". " << i;
				}
			}
			catch (std::invalid_argument) {
				cout << "Input invalid! " << endl;
			}
		}
		else if (cmd == "delete") {
			contract.deleteContract();
			cout << "Contract gol" << endl;
		}
		else if (cmd == "exp") {
			cout << "Numele fisierului: ";
			getline(cin, name);
			cout << "HTML sau CSV?:";
			getline(cin, extension);
			cout << endl;
			if (extension != "html" && extension != "csv")
				cout << "Extensie invalida!";
			else {
				if (extension == "html")
					contract.exportContractHTML(name);
				else
					contract.exportContractCSV(name);
			}
		}
		else if (cmd == "back")
			return;
		else
			cout << "Comanda invalida!";
	}
}
void Console::UIGetAll() {
	int cnt = 0;
	try {
		VectorDis all = service.getAll();
		for (const auto& i : all) {
			cout << ++cnt << ". " << i;
		}
	}
	catch (RepoException& ev) {
		cout << ev.getMessage() << endl;
	}
	
}
void Console::UIUndo()noexcept {
	try {
		service.undo();
	}
	catch (ServiceException& ev) {
		cout << ev.getMsg()<<endl;
	}
}
void Console::addTeste() {
	try {
		service.addDisciplineService("Mate", "Popescu", "Obligatorie", 53);
		service.addDisciplineService("Rom", "Aurel", "Obligatorie", 41);
		service.addDisciplineService("Info", "Popescu", "Optionala", 32);
		service.addDisciplineService("ASC", "Ionescu", "Facultativa", 223);
		service.addDisciplineService("FP", "Xavier", "Obligatorie", 43);
		service.addDisciplineService("OOP", "Onescu", "Optionala", 33);
		service.addDisciplineService("SDA", "Popescu", "Facultativa", 5);
		service.addDisciplineService("OS", "Briciu", "Obligatorie", 433);
	}
	catch (RepoException& ev) {
		cout << ev.getMessage() << endl;
	}
}
	
void Console::run() noexcept {
	string cmd;
	while (true) {
		cout << ">>>";
		getline(cin, cmd);
		if (cmd == "help") {
			cout << "1.add-adauga disciplina\n2.delete-sterge disciplina\n3.update-modifica disciplina\n4.find-cauta disciplina\n5.report-raport dupa tip\n6.sort-sortare\n7.filter_num-filtrare discipline\n";
			cout << "8.filter_teacher-filtrare dupa profesor\n9.all-afisare toate materiile\n10.contract-meniu contract\n11.undo-Undo\n12.exit-iesire program\n13.test-adaga materii de test\n13.clear-curata consola" << endl;
		}
		else if (cmd == "add") {
			this->UIAdd();
		}
		else if (cmd == "delete") {
			this->UIDelete();
		}
		else if (cmd == "all") {
			this->UIGetAll();
		}
		else if (cmd == "update") {
			this->UIUpdate();
		}
		else if (cmd == "find") {
			this->UIFind();
		}
		else if (cmd == "report") {
			this->UIReportType();
		}
		else if (cmd == "sort") {
			this->UISort();
		}
		else if (cmd == "filter_teacher") {
			this->UIFilterAfterTeacher();
		}
		else if (cmd == "filter_num") {
			this->UIFilterAfterNumClasses();
		}
		else if (cmd == "contract") {
			this->UIMenuContract();
		}
		else if (cmd == "undo") {
			this->UIUndo();
		}
		else if (cmd == "test") {
			this->addTeste();
		}
		else if (cmd == "clear") {
			system("cls");
		}
		else if (cmd == "exit")
			exit(0);
		else
			cout << "Comanda invalida! \nPentru ajutor, incearca comanda 'help' \n";
		cout << endl;
	}
}
