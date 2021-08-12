#pragma once

#include <QtWidgets/QWidget>
#include "ui_login.h"
#include"mainwindow.h"

class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);

private:
	Ui::LoginClass ui;
	MainWindow* mainwin;
private slots:
	void on_checkBox_clicked();
	void on_pushButton_clicked();
};
