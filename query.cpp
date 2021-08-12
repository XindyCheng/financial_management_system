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
	ui.label_guide->setText("双击可查看该记录的详情");
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
	ui.label_guide->setText("查询中......");
	search.goSearch(this);
	ui.label_guide->setText("查询完毕！");
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

void Query::newRow//在tableWidget中新建一行
(int index, QDate date, int classify, double money, int account, int label)
{
	ui.tableWidget->insertRow(index);
	QTableWidgetItem* item;
	QString str;
	//日期
	str = date.toString("yyyy-MM-dd"); //日期转换为字符串
	item = new  QTableWidgetItem(str, Query::ctdate);
	ui.tableWidget->setItem(index, Query::ctdate, item);
	//分类
	switch (classify)
	{
	case 1: {str = "收入";break;}
	case 2: {str = "支出";break;}
	case 3: {str = "借款";break;}
	case 4: {str = "余额修改";break;}
	}
	item = new  QTableWidgetItem(str, Query::ctclassify);
	ui.tableWidget->setItem(index, Query::ctclassify, item);
	//金额
	str.setNum(money);
	item = new  QTableWidgetItem(str, Query::ctmoney);
	ui.tableWidget->setItem(index, Query::ctmoney, item);
	//操作账户
	switch (account)
	{
	case 1: {str = "微信";break;}
	case 2: {str = "银行卡";break;}
	case 3: {str = "一卡通";break;}
	case 4: {str = "现金";break;}
	case 5: {str = "其他";break;}
	};
	item = new  QTableWidgetItem(str, Query::ctaccount);
	ui.tableWidget->setItem(index, Query::ctaccount, item);
	//标签
	switch (classify)
	{
	case 1:
	{
		switch (label)
		{
		case 0: {str = "生活费";break;}
		case 1: {str = "兼职";break;}
		case 2: {str = "奖学金";break;}
		case 3: {str = "利息";break;}
		case 4: {str = "贷款";break;}
		case 5: {str = "其他";break;};
		}
		break;
	}
	case 2:
	{
		switch (label)
		{
		case 0: {str = "美食";break;}
		case 1: {str = "交通";break;}
		case 2: {str = "购物";break;}
		case 3: {str = "宿舍";break;}
		case 4: {str = "娱乐";break;}
		case 5: {str = "学习";break;}
		case 6: {str = "医疗";break;}
		case 7: {str = "其他";break;}
		}
		break;
	}
	case 3:
	{
		switch (label)
		{
		case 0: {str = "朋友";break;}
		case 1: {str = "家人";break;}
		case 2: {str = "银行贷款";break;}
		case 3: {str = "花呗";break;}
		case 4: {str = "京东白条";break;}
		case 5: {str = "其他";break;};
		}
		break;
	};
	}
	item = new  QTableWidgetItem(str, Query::ctlabel);
	ui.tableWidget->setItem(index, Query::ctlabel, item);
}

//Search类：

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

//修改记录的函数
void Search::write()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	//置写指针于该记录的位置
	file.seekp(site, ios::beg);
	//写入新纪录
	file.write((char*)&file.tellp(), sizeof(site));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&account, sizeof(account));
	file.write((char*)&label, sizeof(label));
	file.close();
}

//删除记录的函数
void Search::delet()
{
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	//置写指针于该记录的位置
	file.seekp(site, ios::beg);
	int emptydate = 10000101;//空记录的标志
	//写入空纪录
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
	//将指针移动到文件中储存该账户信息的位置
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
		do //查找符合条件的记录
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
				//建立有序链表
				insert(list, i, si, qd, classify, mon, ac, la);
				i++;
			}
		} while (ac != 0);//判断文件是否结束
		file.close();
	}
	resultList* p = list;
	for (int j=0;p;j++)
	{
		////把记录展示在窗口上
		window->newRow(j, p->date, p->fileIndex, p->money, p->account, p->label);
		p = p->next;
	}
}

