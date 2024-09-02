#pragma once

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QApplication>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QTableWidget>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QGridLayout>
#include <QRadioButton>
#include <QListWidget>
#include <qtableview.h>
#include <qlistview.h>
#include <Models.h>
#include "Service.h"
#include "Contract.h"
#include "ui_Lab11_QT.h"
#include "CosGUI.h"

using std::vector;
using std::string;
class ServiceDisciplineGUI : public QWidget {
private:

	Service& srv;
	Contract& ct;

	QTableView* tv = new QTableView;
	QListView* tvl = new QListView;
	MyTableModel* model;
	MyListModel* model2;

	QLabel* lblName = new QLabel{ "Nume Disciplina:" };
	QLabel* lblTeacher = new QLabel{ "Numele Profesorului:" };
	QLabel* lblType = new QLabel{ "Tipul Materiei:" };
	QLabel* lblNumClasses = new QLabel{ "Numarul de Ore:" };
	QLabel* lblNameToDelete = new QLabel{ "Numele materiei" };
	QLabel* lblTypeSort = new QLabel{ "Tipul sortarii" };
	
	QLineEdit* editName;
	QLineEdit* editTeacher;
	QLineEdit* editType;
	QLineEdit* editNumClasses;
	

	QPushButton* btnAddDiscipline;

	QLineEdit* deleteName;
	QPushButton* btnDeleteDiscipline;
	QPushButton* btnFindDiscipline;
	QPushButton* btnUpdateDiscipline;

	QPushButton* btnSortDisciplines;
	QPushButton* btnFilterDisciplines;
	QPushButton* btnFilterDisciplines2;
	QPushButton* btnContract;
	QPushButton* btnUndo;
	QPushButton* btnReport;

	QGroupBox* groupMainBox = new QGroupBox(tr("Sortare"));
	QGroupBox* criteriaBox = new QGroupBox(tr("Criterii de sortare"));
	QGroupBox* typeBox = new QGroupBox(tr("Tipul sortarii"));
	QGroupBox* miscBox = new QGroupBox(tr("Functionalitati"));
	QGroupBox* raportBox = new QGroupBox(tr("Raport"));
	QGroupBox* filterBpx = new QGroupBox(tr("Filtrari"));

	QRadioButton* radioSrtArtistTitlu = new QRadioButton(QString::fromStdString("Nume Materie"));
	QRadioButton* radioSortNumClasses = new QRadioButton(QString::fromStdString("Numar de ore"));
	QRadioButton* radioSrtDurata = new QRadioButton(QString::fromStdString("Profesor+tip"));
	QRadioButton* radioCresc = new QRadioButton(QString::fromStdString("Crescator"));
	QRadioButton* radioDesc= new QRadioButton(QString::fromStdString("Descrescator"));

	QHBoxLayout* lyFilter = new QHBoxLayout;
	QHBoxLayout* lyDelAndFind = new QHBoxLayout;

	QLabel* lblFilterCriteria = new QLabel{ "Campul dupa care filtrez:" };
	QLineEdit* editFilterGen;
	QPushButton* btnFilterType;

	QPushButton* btnReloadData;

	QTableWidget* tableDisciplines;
	QListWidget* listDisciplines;

	void initializeGUIComponents();

	void connectSignalsSlots();
	void reloadSongList(vector<Discipline> disciplines);
	void reloadSongList2(vector<Discipline> disciplines);
public:
	ServiceDisciplineGUI(Service& Srv, Contract& ct) : srv{ Srv }, ct{ ct } {
		initializeGUIComponents();
		model = new MyTableModel{ srv.getAll() };
		model2 = new MyListModel{ srv.getAll() };
		tv->setModel(model);
		tvl->setModel(model2);
		connectSignalsSlots();
		//reloadSongList(srv.getAll());
		//reloadSongList2(srv.getAll());
		
	};
	void guiAddDiscipline();
	void guiDeleteDiscipline();
	void guiUpdateDiscipline();
	void addButtons();
};
