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

//����ÿһ�����������λ�����ݵĽṹ��
struct resultList
{
	int index;//�ý����������
	int fileIndex;//��¼�ý�����ļ����
	long location;//�ü�¼���ļ��е�λ��
	QDate date;
	double money;
	int account, label;
	resultList* next;
};

//�ʽ�����һ�������
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

//������
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

//֧����
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

//�����
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

//��ͳ��ģ����������������
void insert(resultList*& head, int i, long si,
	QDate qd, int cla, double mon, int ac, int la);

