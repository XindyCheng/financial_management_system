#pragma once

#include <QWidget>
#include "ui_details.h"
#include"query.h"

//查看记录详情的页面的窗口
class Details : public QWidget
{
	Q_OBJECT

public:
	Details(QWidget *parent = Q_NULLPTR);
	~Details();
	int file=0;
	long loca=0;
	void display();
	QDate currentdate ;
	QDate IDa;
	double currentMoney = 0,IM;
	int currentAccount = 0,IA;
	int currentClassify = 0,IC;
	int currentLabel = 0,IL;
private:
	Ui::Details ui;
	Query* queryWindow;
private slots:
	void on_pushButton_back_clicked();
	void on_pushButton_delet_clicked();
	void on_pushButton_save_clicked();
	void on_dateEdit_dateChanged();
	void on_lineEdit_money_editingFinished();
	void on_comboBox_account_currentIdexChanged();
	void on_comboBox_classify_currentIdexChanged();
	void on_comboBox_income_currentIdexChanged();
	void on_comboBox_spending_currentIdexChanged();
	void on_comboBox_lender_currentIdexChanged();
};
