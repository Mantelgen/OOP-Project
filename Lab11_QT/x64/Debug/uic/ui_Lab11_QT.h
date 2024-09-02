/********************************************************************************
** Form generated from reading UI file 'Lab11_QT.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LAB11_QT_H
#define UI_LAB11_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Lab11_QTClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Lab11_QTClass)
    {
        if (Lab11_QTClass->objectName().isEmpty())
            Lab11_QTClass->setObjectName("Lab11_QTClass");
        Lab11_QTClass->resize(600, 400);
        menuBar = new QMenuBar(Lab11_QTClass);
        menuBar->setObjectName("menuBar");
        Lab11_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Lab11_QTClass);
        mainToolBar->setObjectName("mainToolBar");
        Lab11_QTClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(Lab11_QTClass);
        centralWidget->setObjectName("centralWidget");
        Lab11_QTClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(Lab11_QTClass);
        statusBar->setObjectName("statusBar");
        Lab11_QTClass->setStatusBar(statusBar);

        retranslateUi(Lab11_QTClass);

        QMetaObject::connectSlotsByName(Lab11_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *Lab11_QTClass)
    {
        Lab11_QTClass->setWindowTitle(QCoreApplication::translate("Lab11_QTClass", "Lab11_QT", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Lab11_QTClass: public Ui_Lab11_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAB11_QT_H
