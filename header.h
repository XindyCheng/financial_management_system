#pragma once
#pragma execution_character_set("utf-8")
#include<QtCharts>
using namespace QtCharts;

#include <QDate>
#include<QFile>
#include<QDataStream>
#include<QTextStream>
#include<iostream>
#include<fstream>
#include "qmessagebox.h"


using namespace std;

QDate toQdate(int);

int toInt(QDate);

//储存每一个搜索结果的位置数据的结构体
struct resultList
{
	int index;//该结果的索引号
	int fileIndex;//记录该结果的文件编号
	long location;//该记录在文件中的位置
	QDate date;
	double money;
	int account, label;
	resultList* next;
};

//资金流，一个虚基类
class CapitalFlow
{
public:
	QDate qdate;
	int date;
	double money;
	int account;
	long site=-1;
	int classify=0;
	CapitalFlow(QDate da, double mon, int ac );
	CapitalFlow();
	~CapitalFlow();
	virtual void write()=0;
	virtual void initial() = 0;
	void changeBalance();
};

//收入类
class Income :virtual public CapitalFlow
{
public:
	int incomeType;
	Income(QDate da, double mon, int ac, int iT);
	Income();
	~Income();
	void write();
	void initial();
};

//支出类
class Spending :virtual public CapitalFlow
{
public:
	int spendingType;
	Spending(QDate da, double mon, int ac, int iT);
	Spending();
	~Spending();
	void write();
	void initial();
};

//借款类
class Borrowing :virtual public CapitalFlow
{
public:
	int lender;
	Borrowing(QDate da, double mon, int ac, int iT);
	Borrowing();
	~Borrowing();
	void write();
	void initial();
};

//在统计模块中用于生成链表
void insert(resultList*& head, int i, long si,
	QDate qd, int cla, double mon, int ac, int la);

