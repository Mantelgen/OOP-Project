#pragma once
#include <QtWidgets/qwidget.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <qmessagebox.h>
#include <qdebug.h>
#include  <QMainWindow>
#include <qpainter.h>
#include "Service.h"
#include "ServiceDisciplineGUI.h"

class ContractGUI: public QMainWindow {

public:
	ContractGUI(Contract& ct, Service& srv, QWidget* parent = nullptr) :ct{ ct }, srv{ srv } {
		initializeGUIComponents();
		connectSignalsSlots();
		//reloadSongList(ct.getAllContract());
	};
	
private:
	Contract& ct;
	Service& srv;

	QLabel* lblName = new QLabel{ "Nume Disciplina:" };
	QLabel* lblNr = new QLabel{ "Numere de discipline:" };
	QLabel* lblFile = new QLabel{ "Numele fisierului" };
	QLineEdit* editName;
	QLineEdit* editFile;

	QLineEdit* editNrRandom;
	QPushButton* btnAddDiscipline;
	QPushButton* btnAddDisciplineRandom;
	QPushButton* btnExport;
	QPushButton* btnClearContract;
	QPushButton* btnLista;
	QPushButton* btnDesen;

	QGroupBox* groupMainBox = new QGroupBox(tr("Tipul exportului"));
	QRadioButton* HTML= new QRadioButton(QString::fromStdString("HTML"));;
	QRadioButton* CSV=new QRadioButton(QString::fromStdString("CSV"));

	QListWidget* listDisciplines;
	QTableWidget* tableDiscipline;
	QPushButton* btnReloadData;
	//ContractListGUI* con = new ContractListGUI{ ct };
	
	void initializeGUIComponents();
	void connectSignalsSlots();
	//void reloadSongList(vector<Discipline> dsp);
	//void reloadSongList2(vector<Discipline> dsp);
};

class ContractListGUI :public QWidget, public Observer {
private:
	Contract& ct;
	QWidget* listWindow = new QWidget;
	QHBoxLayout* box = new QHBoxLayout;
	QTableWidget* table;

	MyTableModel* model1;
	QTableView* tv = new QTableView;
	
	void initComponents() {
		this->setLayout(box);
		/*int noLines = 10;
		int noColumns = 4;
		table = new QTableWidget{ noLines,noColumns };
		QStringList tblHeaderList;
		tblHeaderList << "Nume" << "Profesor" << "Tip" << "Numar Ore";
		table->setHorizontalHeaderLabels(tblHeaderList);
		table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);*/
		model1 = new MyTableModel{ ct.getAllContract() };
		tv->setModel(model1);
		box->addWidget(tv);
	}
	void reloadTable(VectorDis dsp) {
		/*table->clearContents();
		auto& ct2 = ct.getAllContract();
		table->setRowCount(ct2.size());

		int lineNumber2 = 0;
		for (auto& dsp : ct2) {
			table->setItem(lineNumber2, 0, new QTableWidgetItem(QString::fromStdString(dsp.getName())));
			table->setItem(lineNumber2, 1, new QTableWidgetItem(QString::fromStdString(dsp.getTeacher())));
			table->setItem(lineNumber2, 2, new QTableWidgetItem(QString::fromStdString(dsp.getType())));
			table->setItem(lineNumber2, 3, new QTableWidgetItem(QString::number(dsp.getNumClasses())));
			lineNumber2++;
		}*/
		model1->setDiscipline(dsp);
		
	}
public:
	ContractListGUI(Contract& ct) :ct{ ct } {
		initComponents();
		//reloadTable(ct.getAllContract());
		ct.addObserver(this);
		setAttribute(Qt::WA_DeleteOnClose);
		
		update();
	}
	void update() override {
		auto& dsp = ct.getAllContract();
		reloadTable(ct.getAllContract());
	}
	~ContractListGUI() {
		ct.removeObserver(this);
	}
};
class ContractListDrawGUI :public QWidget, public Observer {
private:
	Contract& ct;
public:
	void paintEvent(QPaintEvent*) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		//p.drawImage(x, 0, QImage("pop.jpeg")); 
		//	auto t = QImage("pop.jpeg").width();
		//p.drawImage(t+, 0, QImage("F-16_June_2008.jpg"));
		for (auto dsp : ct.getAllContract()) {
			p.drawRect(x, y, 10, dsp.getNumClasses()*10);
			x += 40;

		}
	}
	ContractListDrawGUI(Contract& ct) :ct{ ct } {
		ct.addObserver(this);
		setAttribute(Qt::WA_DeleteOnClose);
		update();
	};
	void update() override {
		repaint();
	}
	~ContractListDrawGUI() {
		ct.removeObserver(this);
	}
};


