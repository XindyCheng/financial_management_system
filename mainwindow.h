#pragma once

#include <QMainWindow>
#include "ui_mainwindow.h"
#include"record.h"
#include"query.h"
#include"settings.h"
#include "statistic.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
	Ui::MainWindow ui;
	Record* recordWindow;
	Query* queryWindow;
	Settings* settingsWindow;
	Statistic* statisticWindow;
private slots:
	void on_pushButton_back_clicked();
	void on_pushButton_record_clicked();
	void on_pushButton_query_clicked();
	void on_pushButton_settings_clicked();
	void on_pushButton_statistic_clicked();
};
