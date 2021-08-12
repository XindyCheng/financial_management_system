#pragma once

#include <QWidget>
#include"header.h"
#include "ui_statistic.h"

//统计界面的窗口类
class Statistic : public QWidget
{
	Q_OBJECT

public:
	Statistic(QWidget *parent = Q_NULLPTR);
	~Statistic();

private:
	Ui::Statistic ui;
	QDate currentdate = QDate::currentDate();
	QDate currentdate2 = QDate::currentDate();
	int currentType = 0;
	QChart* chart ;
	QPieSeries* series ;
	QString chartTitle = "分类支出统计图";
	QString date1 = currentdate.toString("yyyy-MM-dd");
	QString date2 = currentdate2.toString("yyyy-MM-dd");
private slots:
	void on_dateEdit_dateChanged();
	void on_dateEdit_2_dateChanged();
	void on_pushButton_back_clicked();
	void on_pushButton_account_clicked();
	void on_pushButton_generate_clicked();
	void on_comboBox_currentIdexChanged();
};

//一个用来统计数据和绘图的类
class Sta
{
public:
	QDate qbegin, qend;
	int type;
	double data[8];
	const char* filename;
	void staData();
	void draw(QChart*& chart,QPieSeries*& series);
	Sta(QDate qb,QDate qe,int ty);
	~Sta();
};
