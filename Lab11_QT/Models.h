#pragma once
#include "ServiceDisciplineGUI.h"
#include <QAbstractTableModel>
#include "Service.h"
#include <qdebug.h>

class MyTableModel :public QAbstractTableModel {
	 VectorDis disciplines;
public:
	MyTableModel(const VectorDis& disciplines) :disciplines{ disciplines } {
	}
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return disciplines.size();
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {

			Discipline p = disciplines[index.row()];
			if (index.column() == 0) {
				return QString::fromStdString(p.getName());
			}
			else if (index.column() == 1) {
				return QString::fromStdString(p.getTeacher());
			}
			else if (index.column() == 2) {
				return QString::fromStdString(p.getType());
			}
			else if (index.column() == 3) {
				return QString::number(p.getNumClasses());
			}
		}

		return QVariant{};
	}
	QVariant headerData(int section, Qt::Orientation orientation,
		int role) const override{
		if (role == Qt::DisplayRole) {
			if (orientation == Qt::Horizontal) {
				if(section==0)
					return QString("Nume");
				if (section == 1)
					return QString("Profesor");
				if (section == 2)
					return QString("Tip");
				if (section == 3)
					return QString("Numar ore");
			}
			else {
				return QString("%1").arg(section);
			}
		}
		return QVariant{};
	}
	void setDiscipline(const VectorDis& disciplines) {
		emit layoutAboutToBeChanged();
		this->disciplines = disciplines;
		emit layoutChanged();
	}
};

class MyListModel :public QAbstractListModel {
	std::vector<Discipline> disciplines;
public:
	MyListModel(const std::vector<Discipline>& disciplines) :disciplines{ disciplines } {
	}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return disciplines.size();
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::DisplayRole) {
			qDebug() << "get row:" << index.row();
			auto sp = disciplines[index.row()].getName()+","+ disciplines[index.row()].getTeacher()+","+ disciplines[index.row()].getType()+","+ std::to_string(disciplines[index.row()].getNumClasses());
			return QString::fromStdString(sp);
		}
		return QVariant{};
	}
	void setDiscipline(const VectorDis& disciplines) {
		emit layoutAboutToBeChanged();
		this->disciplines = disciplines;
		emit layoutChanged();
	}
};