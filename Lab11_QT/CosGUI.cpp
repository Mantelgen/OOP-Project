#include "CosGUI.h"

void ContractGUI::initializeGUIComponents() {

	QWidget* centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);

	QHBoxLayout* lyMain = new QHBoxLayout(centralWidget);

	setLayout(lyMain);


	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editName = new QLineEdit;
	editNrRandom = new QLineEdit;
	btnAddDiscipline = new QPushButton("Adauga materia");
	btnAddDisciplineRandom = new QPushButton("Adauga materii");
	lyForm->addRow(lblName, editName);
	lyForm->addWidget(btnAddDiscipline);
	lyForm->addRow(lblNr, editNrRandom);
	lyForm->addWidget(btnAddDisciplineRandom);

	lyLeft->addWidget(form);

	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);
	this->listDisciplines = new QListWidget;

	editFile = new QLineEdit;
	btnExport = new QPushButton("Export");
	QWidget* form2 = new QWidget;
	QFormLayout* lyForm2 = new QFormLayout;
	form2->setLayout(lyForm2);
	lyForm2->addRow(lblFile, editFile);
	

	QVBoxLayout* lyRadioCriteriaBox = new QVBoxLayout;
	this->groupMainBox->setLayout(lyRadioCriteriaBox);
	lyRadioCriteriaBox->addWidget(form2);
	lyRadioCriteriaBox->addWidget(HTML);
	lyRadioCriteriaBox->addWidget(CSV);
	lyRadioCriteriaBox->addWidget(btnExport);
	//lyRadioCriteriaBox->addWidget(con);
/*
	int noLines = 10;
	int noColumns = 4;
	this->tableDiscipline = new QTableWidget{ noLines, noColumns };
	this->listDisciplines = new QListWidget;

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Nume" << "Profesor" << "Tip" << "Numar Ore";
	this->tableDiscipline->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableDiscipline->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);*/
	btnLista = new QPushButton{ "C.R.U.D. GUI" };
	btnDesen = new QPushButton{ "Read Only GUI" };
	QHBoxLayout* obs = new QHBoxLayout;
	QWidget* lyObs = new QWidget;
	lyObs->setLayout(obs);
	obs->addWidget(btnLista);
	obs->addWidget(btnDesen);

	

	lyLeft->addWidget(groupMainBox);
	//lyRight->addWidget(listDisciplines);
	//lyRight->addWidget(tableDiscipline);
	lyLeft->addWidget(lyObs);
	btnClearContract = new QPushButton("Clear");
	lyLeft->addWidget(btnClearContract);

	lyMain->addWidget(left);
	lyMain->addWidget(right);
	
}
void ContractGUI::connectSignalsSlots() {
	QObject::connect(btnAddDiscipline, &QPushButton::clicked, this, [&] {
		try {
			ct.addDisciplineContract(editName->text().toStdString());
			editName->clear();
			//this->reloadSongList(ct.getAllContract());
			//this->reloadSongList2(ct.getAllContract());

		}
		catch (RepoException& er) {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Nu exista materia ceruta!"));
		}
		});
	QObject::connect(btnAddDisciplineRandom, &QPushButton::clicked, this, [&] {
		try {
			unsigned long long nr = stoi(editNrRandom->text().toStdString());
			ct.deleteContract();
			ct.addRandomDisiplinesContract(nr);
			editNrRandom->clear();
			//this->reloadSongList(ct.getAllContract());
			//this->reloadSongList2(ct.getAllContract());
		}
		catch (std::exception) {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Input invalid!"));
		}
		});
	QObject::connect(btnClearContract, &QPushButton::clicked, this, [&] {
		ct.deleteContract();
		//this->reloadSongList(ct.getAllContract());
		//this->reloadSongList2(ct.getAllContract());
		});
	QObject::connect(btnLista, &QPushButton::clicked, this, [&] {
		auto lista = new ContractListGUI{ ct };
		lista->show();
		});
	QObject::connect(btnDesen, &QPushButton::clicked, this, [&] {
		auto lista = new ContractListDrawGUI{ ct };
		lista->show();
		});
	QObject::connect(btnExport, &QPushButton::clicked, this, [&] {
		if (editFile->text().toStdString().size() == 0) {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Input invalid!"));
		}
		else {
			if (this->HTML->isChecked()) {
				ct.exportContractHTML(editFile->text().toStdString());
				QMessageBox::information(this, "Export", QString::fromStdString("Am exportat in fisierul HTML!"));
			}
			else if (this->CSV->isChecked()) {
				ct.exportContractCSV(editFile->text().toStdString());
				QMessageBox::information(this, "Export", QString::fromStdString("Am exportat in fisierul CSV!"));
			}
			else {
				QMessageBox::warning(this, "Warning", QString::fromStdString("Selecteaza tip fisier!"));
			}
		}
		editFile->clear();
		});
}
/*void ContractGUI::reloadSongList(vector<Discipline> disciplines) {
	this->listDisciplines->clear();
	for (auto& dsp : disciplines) {
		string stdsp = dsp.getName() + "," + dsp.getTeacher() + "," + dsp.getType() + "," + std::to_string(dsp.getNumClasses());
		this->listDisciplines->addItem(new QListWidgetItem(QString::fromStdString(stdsp)));

	}
}
void ContractGUI::reloadSongList2(vector<Discipline> disciplones) {
	this->tableDiscipline->clearContents();
	this->tableDiscipline->setRowCount(disciplones.size());

	int lineNumber = 0;
	for (auto& dsp : disciplones) {
		this->tableDiscipline->setItem(lineNumber, 0, new QTableWidgetItem(QString::fromStdString(dsp.getName())));
		this->tableDiscipline->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(dsp.getTeacher())));
		this->tableDiscipline->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(dsp.getType())));
		this->tableDiscipline->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(dsp.getNumClasses())));
		lineNumber++;
	}
}*/