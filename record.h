#pragma once

#include <QWidget>
#include "ui_record.h"
#include"header.h"

//记录界面的窗口类
class Record : public QWidget
{
	Q_OBJECT

public:
	Record(QWidget *parent = Q_NULLPTR);
	~Record();

private:
	Ui::Record ui;
	QDate currentdate = QDate::currentDate();
	double currentMoney = 0;
	int currentAccount = 0;
	int currentClassify = 0;
	int currentLabel = 0;
private slots:
	void on_pushButton_back_clicked();
	void on_pushButton_save_cliked();
	void backToMainWindow();
	void on_dateEdit_dateChanged();
	void on_lineEdit_money_editingFinished();
	void on_comboBox_account_currentIdexChanged();
	void on_comboBox_classify_currentIdexChanged();
	void on_comboBox_income_currentIdexChanged();
	void on_comboBox_spending_currentIdexChanged();
	void on_comboBox_lender_currentIdexChanged();
};
