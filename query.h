#pragma once

#include <QWidget>
#include "ui_query.h"
#include"header.h"

//查询界面的窗口类
class Query : public QWidget
{
	Q_OBJECT

public:
	Query(QWidget *parent = Q_NULLPTR);
	~Query();
	void newRow
	(int index, QDate date, int classify, double money, int account, int label);
private:
	Ui::Query ui;
	QDate currentdate = QDate::currentDate();
	QDate currentdate2 = QDate::currentDate();
	resultList* list = NULL;
	double currentMoney = 0;
	int currentAccount = 0;
	int currentClassify = 0;
	int currentLabel = 0;
	enum CellType { ctdate,ctclassify,ctmoney,ctaccount,ctlabel };
	void toDetails(int fileIndex, long location);
	
private slots:
	void on_pushButton_back_clicked();
	void guide_show();
	void doubleClicked();
	void on_pushButton_clicked();
	void on_comboBox_account_currentIdexChanged();
	void on_comboBox_classify_currentIdexChanged();
	void on_comboBox_income_currentIdexChanged();
	void on_comboBox_spending_currentIdexChanged();
	void on_comboBox_lender_currentIdexChanged();
	void on_dateEdit_dateChanged();
	void on_dateEdit_2_dateChanged();
};

//用于查询的类
//因为此类中需要用到一个Query类的指针，所以写在Query的文件下
class Search :public Income, public Spending, public Borrowing
{
public:
	QDate qbegin, qend;
	int begin, end, label = 0;
	resultList* list = NULL;//一个用于储存搜索结果的链表头
	const char* filename;
	Search(QDate qb, QDate qe, int ac, int cla,int la);
	Search(int fileIndex, long location);
	~Search();
	void goSearch(Query*);//搜索并在Query窗口上显示记录，同时生成一个resultList链表
	void resetBanlance();//删除记录后要把余额修改回去
	void write();//修改记录
	void initial();
	void delet();//删除记录
};
