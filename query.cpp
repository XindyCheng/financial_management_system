#include "query.h"

Query::Query(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox_income->hide();
	ui.comboBox_lender->hide();
	ui.comboBox_spending->hide();
	ui.label_4->hide();
	ui.dateEdit->setDate(QDate::currentDate());
	ui.dateEdit_2->setDate(QDate::currentDate());
}

Query::~Query() { ; }

void Query::guide_show()
{
	ui.label_guide->setText("˫���ɲ鿴�ü�¼������");
}

void Query::doubleClicked()
{
	int a = ui.tableWidget->currentRow();
	int b = ui.tableWidget->currentColumn();
	int i ;
	resultList* q = list;
	for (i = 0;i < a;i++)
	{
		q = q->next;
	}
	toDetails(q->fileIndex, q->location);
}

void Query::on_pushButton_clicked()
{
	int row = ui.tableWidget->rowCount();
	for (int i = 0;i < row;i++)
	{
		ui.tableWidget->removeRow(0);
	}
	Search search(currentdate, currentdate2, currentAccount, currentClassify,currentLabel);
	ui.label_guide->setText("��ѯ��......");
	search.goSearch(this);
	ui.label_guide->setText("��ѯ��ϣ�");
	list = search.list;
}

void Query::on_comboBox_account_currentIdexChanged()
{
	currentAccount = ui.comboBox_account->currentIndex();
}

void Query::on_comboBox_classify_currentIdexChanged()
{
	currentClassify = ui.comboBox_classify->currentIndex();
	currentLabel = 0;
	switch (ui.comboBox_classify->currentIndex())
	{
	case 0: {ui.label_4->hide();ui.comboBox_income->hide();
		ui.comboBox_lender->hide();
		ui.comboBox_spending->hide();break;}
	case 1: {ui.label_4->show();ui.comboBox_income->show();
		ui.comboBox_lender->hide();ui.comboBox_spending->hide();break;}
	case 2: {ui.label_4->show();ui.comboBox_spending->show();
		ui.comboBox_lender->hide();ui.comboBox_income->hide();break;}
	case 3: {ui.label_4->show();ui.comboBox_lender->show();
		ui.comboBox_income->hide();ui.comboBox_spending->hide();break;}
	case 4: {ui.label_4->hide();ui.comboBox_income->hide();ui.comboBox_lender->hide();
		ui.comboBox_spending->hide();}
	}
}

void Query::on_comboBox_income_currentIdexChanged()
{
	currentLabel = ui.comboBox_income->currentIndex();
}

void Query::on_comboBox_spending_currentIdexChanged()
{
	currentLabel = ui.comboBox_spending->currentIndex();
}

void Query::on_comboBox_lender_currentIdexChanged()
{
	currentLabel = ui.comboBox_lender->currentIndex();
}

void Query::on_dateEdit_dateChanged()
{
	currentdate = ui.dateEdit->date();
}

void Query::on_dateEdit_2_dateChanged()
{
	currentdate2 = ui.dateEdit_2->date();
}

void Query::newRow//��tableWidget���½�һ��
(int index, QDate date, int classify, double money, int account, int label)
{
	ui.tableWidget->insertRow(index);
	QTableWidgetItem* item;
	QString str;
	//����
	str = date.toString("yyyy-MM-dd"); //����ת��Ϊ�ַ���
	item = new  QTableWidgetItem(str, Query::ctdate);
	ui.tableWidget->setItem(index, Query::ctdate, item);
	//����
	switch (classify)
	{
	case 1: {str = "����";break;}
	case 2: {str = "֧��";break;}
	case 3: {str = "���";break;}
	case 4: {str = "����޸�";break;}
	}
	item = new  QTableWidgetItem(str, Query::ctclassify);
	ui.tableWidget->setItem(index, Query::ctclassify, item);
	//���
	str.setNum(money);
	item = new  QTableWidgetItem(str, Query::ctmoney);
	ui.tableWidget->setItem(index, Query::ctmoney, item);
	//�����˻�
	switch (account)
	{
	case 1: {str = "΢��";break;}
	case 2: {str = "���п�";break;}
	case 3: {str = "һ��ͨ";break;}
	case 4: {str = "�ֽ�";break;}
	case 5: {str = "����";break;}
	};
	item = new  QTableWidgetItem(str, Query::ctaccount);
	ui.tableWidget->setItem(index, Query::ctaccount, item);
	//��ǩ
	switch (classify)
	{
	case 1:
	{
		switch (label)
		{
		case 0: {str = "�����";break;}
		case 1: {str = "��ְ";break;}
		case 2: {str = "��ѧ��";break;}
		case 3: {str = "��Ϣ";break;}
		case 4: {str = "����";break;}
		case 5: {str = "����";break;};
		}
		break;
	}
	case 2:
	{
		switch (label)
		{
		case 0: {str = "��ʳ";break;}
		case 1: {str = "��ͨ";break;}
		case 2: {str = "����";break;}
		case 3: {str = "����";break;}
		case 4: {str = "����";break;}
		case 5: {str = "ѧϰ";break;}
		case 6: {str = "ҽ��";break;}
		case 7: {str = "����";break;}
		}
		break;
	}
	case 3:
	{
		switch (label)
		{
		case 0: {str = "����";break;}
		case 1: {str = "����";break;}
		case 2: {str = "���д���";break;}
		case 3: {str = "����";break;}
		case 4: {str = "��������";break;}
		case 5: {str = "����";break;};
		}
		break;
	};
	}
	item = new  QTableWidgetItem(str, Query::ctlabel);
	ui.tableWidget->setItem(index, Query::ctlabel, item);
}

//Search�ࣺ

Search::~Search() { ; }

Search::Search(QDate qb, QDate qe, int ac, int cla,int la)
{
	qbegin = qb;
	qend = qe;
	begin = toInt(qbegin);
	end = toInt(qend);
	account = ac;
	classify = cla;
	label = la;
	switch (cla) {
	case 0:break;
	case 1: {filename = "incomeRecord.dat";break;}
	case 2: {filename = "spendingRecord.dat";break;}
	case 3: {filename = "borrowingRecord.dat";break;}
	case 4: {filename = "modifyRecord.dat";break;}
	}
}

Search::Search(int fileIndex, long location)
{
	switch (fileIndex) {
	case 0:break;
	case 1: {filename = "incomeRecord.dat";break;}
	case 2: {filename = "spendingRecord.dat";break;}
	case 3: {filename = "borrowingRecord.dat";break;}
	case 4: {filename = "modifyRecord.dat";break;}
	}
	site = location;
	money = 0;
	account = 10;
	label = 0;
}

void Search::initial() { ; }

//�޸ļ�¼�ĺ���
void Search::write()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	//��дָ���ڸü�¼��λ��
	file.seekp(site, ios::beg);
	//д���¼�¼
	file.write((char*)&file.tellp(), sizeof(site));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&account, sizeof(account));
	file.write((char*)&label, sizeof(label));
	file.close();
}

//ɾ����¼�ĺ���
void Search::delet()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	//��дָ���ڸü�¼��λ��
	file.seekp(site, ios::beg);
	int emptydate = 10000101;//�ռ�¼�ı�־
	//д��ռ�¼
	file.write((char*)&file.tellp(), sizeof(site));
	file.write((char*)&emptydate, sizeof(emptydate));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&account, sizeof(account));
	file.write((char*)&label, sizeof(label));
	file.close();
}

void Search::resetBanlance()
{
	fstream file;
	file.open("userinfo.dat", ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double a, b;
	//��ָ���ƶ����ļ��д�����˻���Ϣ��λ��
	for (int i = 1;i <= account;i++) {
		file.read((char*)&a, sizeof(a));
	}
	file.seekp(-long(sizeof(a)), ios::cur);
	switch (classify)
	{
	case 1:
	{a -= money;break;}
	case 2:
	{a += money;break;}
	case 3:
	{a -= money;break;}
	}
	file.write((char*)&a, sizeof(a));
	if (classify == 3)
	{
		file.seekp(0, ios::beg);
		for (int i = 1;i <= 6;i++) {
			file.read((char*)&b, sizeof(b));
		}
		file.seekp(-long(sizeof(b)), ios::cur);
		b -= money;
		file.write((char*)&b, sizeof(b));
	}
	file.close();
}

void Search::goSearch(Query* window)
{
	const char* fname[3] =
	{ "incomeRecord.dat","spendingRecord.dat","borrowingRecord.dat" };
	fstream file;
	int j, n;
	int mark = classify;
	if (mark != 0)n = 1;
	else n = 3;
	int i = 0;
	for (j = 0;j < n;j++)
	{
		if (mark == 0)
		{
			classify = j + 1;
			filename = fname[j];
		}
		file.open(filename, ios::out | ios::in | ios::binary);
		file.seekg(0, ios::beg);
		int da, ac, la;
		double mon;
		long si;
		do //���ҷ��������ļ�¼
		{
			file.read((char*)&si, sizeof(site));
			file.read((char*)&da, sizeof(da));
			file.read((char*)&mon, sizeof(mon));
			file.read((char*)&ac, sizeof(ac));
			file.read((char*)&la, sizeof(la));
			QDate qd = toQdate(da);
			if (ac != 0 && qd >= qbegin && qd <= qend &&
				(ac == account || account == 0) && (la == label-1 || label == 0))
			{
				//������������
				insert(list, i, si, qd, classify, mon, ac, la);
				i++;
			}
		} while (ac != 0);//�ж��ļ��Ƿ����
		file.close();
	}
	resultList* p = list;
	for (int j=0;p;j++)
	{
		////�Ѽ�¼չʾ�ڴ�����
		window->newRow(j, p->date, p->fileIndex, p->money, p->account, p->label);
		p = p->next;
	}
}

