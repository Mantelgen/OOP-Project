#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Lab11_QT.h"

class Lab11_QT : public QMainWindow
{
    Q_OBJECT

public:
    Lab11_QT(QWidget *parent = nullptr);
    ~Lab11_QT();

private:
    Ui::Lab11_QTClass ui;
};
