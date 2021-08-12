#pragma once

#include <QWidget>
#include "ui_query.h"
#include"header.h"

//��ѯ����Ĵ�����
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

//���ڲ�ѯ����
//��Ϊ��������Ҫ�õ�һ��Query���ָ�룬����д��Query���ļ���
class Search :public Income, public Spending, public Borrowing
{
public:
	QDate qbegin, qend;
	int begin, end, label = 0;
	resultList* list = NULL;//һ�����ڴ����������������ͷ
	const char* filename;
	Search(QDate qb, QDate qe, int ac, int cla,int la);
	Search(int fileIndex, long location);
	~Search();
	void goSearch(Query*);//��������Query��������ʾ��¼��ͬʱ����һ��resultList����
	void resetBanlance();//ɾ����¼��Ҫ������޸Ļ�ȥ
	void write();//�޸ļ�¼
	void initial();
	void delet();//ɾ����¼
};
