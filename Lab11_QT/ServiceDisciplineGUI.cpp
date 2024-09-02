#include "ServiceDisciplineGUI.h"

void ServiceDisciplineGUI::initializeGUIComponents() {

	//impartim fereastra in 2: in stanga, butoane+labels+qlineedits
	//iar in dreapta: tabelul cu melodii

	//"stanga" si "dreapta" pentru ca este QHBoxLayout
	//se adauga componente incepand din stanga, pe orizontala
	//aici: "left" component, then "right" component
	//care la randul lor contin alte componente

	//main layout	
	
	
	QHBoxLayout* lyMain = new QHBoxLayout;
	this->setLayout(lyMain); 
	//left part of the window
	//pentru aceasta parte setam layout vertical
	QWidget* left = new QWidget;
	QVBoxLayout* lyLeft = new QVBoxLayout;
	left->setLayout(lyLeft);

	//componente pentru functionalitatea de adaugare a unei melodii
	//folosim un QFormLayout pentru detaliile de adaugare a unei melodii
	QWidget* form = new QWidget;
	QFormLayout* lyForm = new QFormLayout;
	form->setLayout(lyForm);
	editName = new QLineEdit;
	editTeacher = new QLineEdit;
	editType = new QLineEdit;
	editNumClasses = new QLineEdit;

	lyForm->addRow(lblName, editName);
	lyForm->addRow(lblTeacher, editTeacher);
	lyForm->addRow(lblType, editType);
	lyForm->addRow(lblNumClasses, editNumClasses);
	

	QWidget* form2 = new QWidget;
	QHBoxLayout* layout = new QHBoxLayout;
	form2->setLayout(layout);
	btnAddDiscipline = new QPushButton("Adauga disciplina");
	btnUpdateDiscipline = new QPushButton("Modifica Disciplina");
	layout->addWidget(btnAddDiscipline);
	layout->addWidget(btnUpdateDiscipline);

	btnDeleteDiscipline = new QPushButton("Sterge disciplina");
	btnFindDiscipline = new QPushButton("Cauta disciplina");
	btnUndo = new QPushButton("Undo");

	QWidget* formDelete = new QWidget;
	QFormLayout* lyFormDelete = new QFormLayout;
	formDelete->setLayout(lyFormDelete);
	deleteName = new QLineEdit;
	lyFormDelete->addRow(lblNameToDelete, deleteName);
	
	QWidget* formDelAndFind = new QWidget;
	QHBoxLayout* lyDAF = new QHBoxLayout;
	formDelAndFind->setLayout(lyDAF);
	lyDAF->addWidget(btnDeleteDiscipline);
	lyDAF->addWidget(btnFindDiscipline);




	//adaugam toate componentele legate de adaugare melodie
	//in layout-ul care corespunde partii din stanga a ferestrei
	
	lyLeft->addWidget(form);
	lyLeft->addWidget(form2);
	lyLeft->addWidget(formDelete);
	lyLeft->addWidget(formDelAndFind);


	//Radio Buttons: ne ajuta cand trebuie sa selectam doar o 
	//optiune din mai multe (doar un RadioButton poate fi selectat
	//la un moment dat)


	//vs. CheckBox (see documentation)
	//also see documentation on QGroupBox, QRadioButton pentru detalii

	//cream un GroupBox pentru radiobuttons care corespund 
	//criteriilor de sortare pe care le avem (dupa artist+titlu 
	//si durata) + butonul de sortare
	

	QVBoxLayout* lyRadioCriteriaBox = new QVBoxLayout;
	this->typeBox->setLayout(lyRadioCriteriaBox);
	lyRadioCriteriaBox->addWidget(radioSrtArtistTitlu);
	lyRadioCriteriaBox->addWidget(radioSortNumClasses);
	lyRadioCriteriaBox->addWidget(radioSrtDurata);

	


	QVBoxLayout* lyRadioTypeBox = new QVBoxLayout;
	this->criteriaBox->setLayout(lyRadioTypeBox);
	lyRadioTypeBox->addWidget(radioCresc);
	lyRadioTypeBox->addWidget(radioDesc);

	btnSortDisciplines = new QPushButton("Sorteaza disciplinele");

	
	QVBoxLayout* lySortBox = new QVBoxLayout;
	this->groupMainBox->setLayout(lySortBox);
	lySortBox->addWidget(typeBox);
	lySortBox->addWidget(criteriaBox);
	lySortBox->addWidget(btnSortDisciplines);

	//adaugam acest grup in partea stanga, 
	//dupa componentele pentru adaugare in layout-ul vertical
	lyLeft->addWidget(groupMainBox);

	

	QWidget* formReport = new QWidget;
	this->raportBox->setLayout(lyFilter);
	lyLeft->addWidget(raportBox);
	//cream un form pentru cerintele suplimentare
	btnReport = new QPushButton("Raport");
	lyLeft->addWidget(btnReport);

	btnContract = new QPushButton("Contract");
	btnFilterDisciplines = new QPushButton("Profesor");
	btnFilterDisciplines2 = new QPushButton("Numar Ore");

	QWidget* formFilter = new QWidget;
	QFormLayout* lyFormFilter = new QFormLayout;
	formFilter->setLayout(lyFormFilter);
	editFilterGen = new QLineEdit();
	lyFormFilter->addRow(lblFilterCriteria, editFilterGen);
	
	QWidget* filterButtons = new QWidget;
	QHBoxLayout* lyBut = new QHBoxLayout;
	filterButtons->setLayout(lyBut);
	lyBut->addWidget(btnFilterDisciplines);
	lyBut->addWidget(btnFilterDisciplines2);

	lyLeft->addWidget(formFilter);
	lyLeft->addWidget(filterButtons);
	btnReloadData = new QPushButton("Reload data");
	
	QWidget* formMisc =  new QWidget;
	QHBoxLayout* lyMiscBox = new QHBoxLayout;
	this->miscBox->setLayout(lyMiscBox);
	lyMiscBox->addWidget(btnContract);
	lyMiscBox->addWidget(btnUndo);
	lyMiscBox->addWidget(btnReloadData);
	lyLeft->addWidget(miscBox);
	//cream un form pentru filtrarea dupa gen 

	
	
	//Buton folosit pentru a reincarca datele
	//i.e. afisam toate melodiile in tabel, in ordinea initiala din fisier
	
	
	

	//componenta right - contine doar tabelul cu melodii
	QWidget* right = new QWidget;
	QVBoxLayout* lyRight = new QVBoxLayout;
	right->setLayout(lyRight);

	int noLines = 10;
	int noColumns = 4;
	this->tableDisciplines = new QTableWidget{ noLines, noColumns };
	this->listDisciplines = new QListWidget;

	//setam header-ul tabelului
	QStringList tblHeaderList;
	tblHeaderList << "Nume" << "Profesor" << "Tip" << "Numar Ore";
	this->tableDisciplines->setHorizontalHeaderLabels(tblHeaderList);

	//optiune pentru a se redimensiona celulele din tabel in functie de continut
	this->tableDisciplines->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	//lyRight->addWidget(tableDisciplines);
	lyRight->addWidget(tv);
	lyMain->addWidget(left);
	lyMain->addWidget(right);
	//lyMain->addWidget(listDisciplines);
	lyMain->addWidget(tvl);
	

}
void ServiceDisciplineGUI::reloadSongList(vector<Discipline> disciplines) {
	model->setDiscipline(disciplines);
	//this->tableDisciplines->clearContents();
	//this->tableDisciplines->setRowCount(disciplones.size());
	
	//int lineNumber = 0;
	/*for (auto& dsp : disciplones) {
		QTableWidgetItem* item = new QTableWidgetItem(QString::fromStdString(dsp.getName()));
		QTableWidgetItem* item2 = new QTableWidgetItem(QString::fromStdString(dsp.getTeacher()));
		QTableWidgetItem* item3 = new QTableWidgetItem(QString::fromStdString(dsp.getType()));
		QTableWidgetItem* item4 = new QTableWidgetItem(QString::number(dsp.getNumClasses()));
		item->setData(Qt::UserRole,QString::fromStdString(dsp.getName()));
		item2->setData(Qt::UserRole, QString::fromStdString(dsp.getTeacher()));
		item3->setData(Qt::UserRole, QString::fromStdString(dsp.getType()));
		item4->setData(Qt::UserRole, QString::number(dsp.getNumClasses()));
		this->tableDisciplines->setItem(lineNumber, 0, item);
		this->tableDisciplines->setItem(lineNumber, 1, item2);
		this->tableDisciplines->setItem(lineNumber, 2, item3);
		this->tableDisciplines->setItem(lineNumber, 3, item4);
		lineNumber++;
	}*/
	
}
void ServiceDisciplineGUI::reloadSongList2(vector<Discipline> disciplines) {

	model2->setDiscipline(disciplines);
}
void ServiceDisciplineGUI::connectSignalsSlots() {
	QObject::connect(btnAddDiscipline, &QPushButton::clicked, this, &ServiceDisciplineGUI::guiAddDiscipline);
	QObject::connect(btnDeleteDiscipline, &QPushButton::clicked, this, &ServiceDisciplineGUI::guiDeleteDiscipline);
	QObject::connect(btnUpdateDiscipline, &QPushButton::clicked, this, &ServiceDisciplineGUI::guiUpdateDiscipline);
	QObject::connect(btnReport, &QPushButton::clicked, this, &ServiceDisciplineGUI::addButtons);
	QObject::connect(btnFindDiscipline, &QPushButton::clicked, this, [&] {
		string name = deleteName->text().toStdString();
		Discipline dsp;
		try {
			dsp = srv.findDisciplineService(name);
			string stdsp = "Disciplina: "+dsp.getName() + "," + dsp.getTeacher() + "," + dsp.getType() + "," + std::to_string(dsp.getNumClasses());
			QMessageBox::information(this, "Gasit!", QString::fromStdString(stdsp));
		}
		catch (ServiceException& er) {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Nu exista materia ceruta!"));
		}
		});
	QObject::connect(btnSortDisciplines, &QPushButton::clicked, [&]() {
		if (this->radioCresc->isChecked()) {
			if (this->radioSrtArtistTitlu->isChecked()) {
				reloadSongList(srv.sortByName());
				this->reloadSongList2(srv.sortByName());
			}
			else if (this->radioSrtDurata->isChecked()) {
				this->reloadSongList(srv.sortByTeacherAndType());
				this->reloadSongList2(srv.sortByTeacherAndType());
			}
			else if (this->radioSortNumClasses->isChecked()) {
				this->reloadSongList(srv.sortByNumClasses());
				this->reloadSongList2(srv.sortByNumClasses());
			}
		}
		else if (this->radioDesc->isChecked()) {
			if (this->radioSrtArtistTitlu->isChecked()) {
				vector<Discipline> dsp = srv.sortByName();
				std::reverse(dsp.begin(), dsp.end());
				this->reloadSongList(dsp);
				this->reloadSongList2(dsp);
			}
				
			else if (this->radioSrtDurata->isChecked()) {
				vector<Discipline> dsp = srv.sortByTeacherAndType();
				std::reverse(dsp.begin(), dsp.end());
				this->reloadSongList(dsp);
				this->reloadSongList2(dsp);
			}
			else if (this->radioSortNumClasses->isChecked()) {
				vector<Discipline> dsp = srv.sortByNumClasses();
				std::reverse(dsp.begin(), dsp.end());
				this->reloadSongList(dsp);
				this->reloadSongList2(dsp);
			}
		}
		else {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Nu ai selectat tipul sortarii!"));
		}
		});

	QObject::connect(btnFilterType, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterGen->text().toStdString();
		try {
			this->reloadSongList(srv.filterAfterTeacher(filterC));
			this->reloadSongList2(srv.filterAfterTeacher(filterC));
		}
		catch (ServiceException& er) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
		}
		
		});
	QObject::connect(btnFilterDisciplines, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterGen->text().toStdString();
		try {
			this->reloadSongList(srv.filterAfterTeacher(filterC));
			this->reloadSongList2(srv.filterAfterTeacher(filterC));
			editFilterGen->clear();
		}
		catch (ServiceException& er) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
		}
		//
		});
	QObject::connect(btnFilterDisciplines2, &QPushButton::clicked, [&]() {
		string filterC = this->editFilterGen->text().toStdString();
		int nr = 0;
		try {
			nr = stoi(filterC);
			editFilterGen->clear();
			this->reloadSongList(srv.filterAfterNumClasses(nr));
			this->reloadSongList2(srv.filterAfterNumClasses(nr));
		}
		catch (ServiceException& er) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
		}
		catch (std::exception) {
			QMessageBox::warning(this, "Warning", QString::fromStdString("Invalid inputb"));
		}
		//
		});
	QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
		try {
			srv.undo();
			this->reloadSongList(this->srv.getAll());
			this->reloadSongList2(this->srv.getAll());
		}
		catch (ServiceException& er) {
			QMessageBox::warning(this, "Warning", QString::fromStdString(er.getMsg()));
		}
	});
	QObject::connect(btnReloadData, &QPushButton::clicked, [&]() {
			this->reloadSongList(srv.getAll());
			this->reloadSongList2(srv.getAll());
		});
	QObject::connect(btnContract, &QPushButton::clicked, [&]() {
		auto gui=new ContractGUI{ ct,srv,this };
		gui->show();
		});
	QObject::connect(tableDisciplines, &QTableWidget::itemSelectionChanged,[&]{
		auto sel = tableDisciplines->selectedItems();
		if (sel.isEmpty()) {
			editName->setText("");
			editTeacher->setText("");
			editFilterGen->setText("");
			editType->setText("");
			editNumClasses->setText("");
			deleteName->setText("");
		}
		else
		{
			auto selIt = sel.at(0);
			auto name = selIt->data(Qt::UserRole).toString();
			Discipline dsp = srv.findDisciplineService(name.toStdString());
			editName->setText(QString::fromStdString(dsp.getName()));
			editType->setText(QString::fromStdString(dsp.getType()));
			editTeacher->setText(QString::fromStdString(dsp.getTeacher()));
			editNumClasses->setText(QString::number(dsp.getNumClasses()));
			deleteName->setText(QString::fromStdString(dsp.getName()));
		}
		});
	QObject::connect(tv->selectionModel(), &QItemSelectionModel::selectionChanged, [this] {
		if (tv->selectionModel()->selectedIndexes().isEmpty()) {
			editName->setText("");
			editTeacher->setText("");
			editFilterGen->setText("");
			editType->setText("");
			editNumClasses->setText("");
			deleteName->setText("");
			return;
		}
		int selRow = tv->selectionModel()->selectedIndexes().at(0).row();
		auto cel0Index = tv->model()->index(selRow, 0);
		auto cel1Index = tv->model()->index(selRow, 1);
		auto cel2Index = tv->model()->index(selRow,2);
		auto cel3Index = tv->model()->index(selRow, 3);

		auto cellValue0 = tv->model()->data(cel0Index, Qt::DisplayRole).toString();
		auto cellValue1 = tv->model()->data(cel1Index, Qt::DisplayRole).toString();
		auto cellValue2 = tv->model()->data(cel2Index, Qt::DisplayRole).toString();
		auto cellValue3 = tv->model()->data(cel3Index, Qt::DisplayRole).toString();
		editName->setText(cellValue0);
		editTeacher->setText(cellValue1);
		editType->setText(cellValue2);
		editNumClasses->setText(cellValue3);
		deleteName->setText(cellValue0);
		});
}


void ServiceDisciplineGUI::guiAddDiscipline() {
	try {
		//preluare detalii din QLineEdit-uri
		string name = editName->text().toStdString();
		string teacher = editTeacher->text().toStdString();
		string type = editType->text().toStdString();
		unsigned int  numClasses = editNumClasses->text().toInt();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		editName->clear();
		editTeacher->clear();
		editType->clear();
		editNumClasses->clear();

		this->srv.addDisciplineService(name, teacher, type, numClasses);
		this->reloadSongList2(this->srv.getAll());
		this->reloadSongList(this->srv.getAll());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina adaugata cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMessage()));
	}


}

void ServiceDisciplineGUI::guiDeleteDiscipline() {
	try {
		//preluare detalii din QLineEdit-uri
		string name = deleteName->text().toStdString();

		//optional - golim QLineEdit-urile dupa apasarea butonului
		deleteName->clear();
		editName->clear();
		editTeacher->clear();
		editType->clear();
		editNumClasses->clear();
		this->srv.deleteDisciplineService(name);
		this->reloadSongList2(this->srv.getAll());
		this->reloadSongList(this->srv.getAll());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina stearsa cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMessage()));
	}
	catch (ServiceException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}

}
void ServiceDisciplineGUI::guiUpdateDiscipline() {
	try {
		//preluare detalii din QLineEdit-uri
		string name = editName->text().toStdString();
		string teacher = editTeacher->text().toStdString();
		string type = editType->text().toStdString();
		unsigned int numClasses = editNumClasses->text().toInt();
		//optional - golim QLineEdit-urile dupa apasarea butonului
		editName->clear();
		editTeacher->clear();
		editType->clear();
		editNumClasses->clear();

		this->srv.updateDisciplineService(name, teacher, type, numClasses);
		this->reloadSongList2(this->srv.getAll());
		this->reloadSongList(this->srv.getAll());

		//afisam un mesaj pentru a anunta utilizatorul ca melodia s-a adaugat
		QMessageBox::information(this, "Info", QString::fromStdString("Disciplina adaugata cu succes."));

	}
	catch (RepoException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMessage()));
	}
	catch (ValidationException& ve) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(ve.getMessage()));
	}
	catch (ServiceException& re) {
		QMessageBox::warning(this, "Warning", QString::fromStdString(re.getMsg()));
	}
}

void ServiceDisciplineGUI::addButtons() {
	map<string, VectorDis>result = srv.reportType();
	for (const auto& ch : result) {
		auto btn = new QPushButton{ QString::fromStdString(ch.first) };
		lyFilter->addWidget(btn);
		QObject::connect(btn, &QPushButton::clicked, [this,btn,ch] {
			string msg = "Nr de materii de tip " + ch.first + " este " + std::to_string(ch.second.size());
			QMessageBox::information(nullptr, "Info Raport", QString::fromStdString(msg));
			delete btn;
			});
	}
}