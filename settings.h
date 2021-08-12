#pragma once

#include <QWidget>
#include "ui_settings.h"
#include"header.h"

//设置界面的窗口类
class Settings : public QWidget
{
	Q_OBJECT

public:
	Settings(QWidget *parent = Q_NULLPTR);
	~Settings();

private:
	Ui::Settings ui;
private slots:
	void on_pushButton_back_clicked();
	void on_incomeInitial_cliked();
	void on_spendingInitial_cliked();
	void on_borrowingInitial_cliked();
	void on_userinfoInitial_cliked();
	void on_pushButton_banlance_clicked();
	void on_comboBox_account_currentIdexChanged();
	void on_pushButton_password_clicked();
	void on_checkBox_clicked();
	void on_checkBox_2_clicked();
};
