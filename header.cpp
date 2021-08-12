#include"header.h"

//这两个函数用于日期的转换，因为在储存数据时为了便于管理，日期的储存类型是int
QDate toQdate(int date)
{
	int yy = date / 10000;
	int mm = (date - yy*10000) / 100;
	int dd = date - yy * 10000 - mm * 100;
	QDate qdate(yy, mm, dd);
	return qdate;
}
int toInt(QDate qdate)
{
	int date = qdate.year() * 10000 + qdate.month() * 100 + qdate.day();
	return date;
}

//在query模块中用于按日期建立有序链表
void insert(resultList*& head, int i, long si,
	QDate qd, int cla, double mon, int ac, int la)
{
	resultList* s, * p, * q;
	s = new resultList;
	s->fileIndex = cla;
	s->index = i;s->location = si;s->date = qd;
	s->money = mon;s->label = la;s->account = ac;
	s->next = NULL;
	if (head == NULL)
	{
		head = s;
		return;
	}
	if (head->date > s->date)
	{
		s->next = head;
		head = s;
		return;
	}
	for (q = head, p = head->next;p;q = p, p = p->next)
		if (p->date > s->date)
		{
			s->next = p;
			q->next = s;
			return;
		}
	q->next = s;
	return;
}

CapitalFlow::CapitalFlow(QDate da, double mon, int ac)
{
	qdate = da;
	date = toInt(qdate);
	money = mon;
	account = ac;
}

CapitalFlow::CapitalFlow()
{
	qdate = QDate(2000, 1, 1);
	date = 20000101;
	money = 0;
	account = 0;
}

CapitalFlow::~CapitalFlow() { ; };

//用于修改账户余额的函数
void CapitalFlow::changeBalance()
{
	fstream file;
	file.open("userinfo.dat", ios::out  |ios::in| ios::binary);
	file.seekg(0, ios::beg);
	double a,b;
	//将指针移动到文件中储存该账户信息的位置
	for (int i = 1;i <= account;i++){
		file.read((char*)&a, sizeof(a));
	}
	file.seekp(-long(sizeof(a)), ios::cur);
	switch (classify)
	{
	case 1:
	{a += money;break;}
	case 2:
	{a -= money;break;}
	case 3:
	{a += money;break;}
	case 4:
	{a = money;break;}
	}
	file.write((char*)&a, sizeof(a));
	if (classify == 3)
	{
		file.seekp(0, ios::beg);
		for (int i = 1;i <= 6;i++){
			file.read((char*)&b, sizeof(b));
		}
		file.seekp(-long(sizeof(b)), ios::cur);
		b += money;
		file.write((char*)&b, sizeof(b));
	}
	file.close();
}

Income::~Income() { ; }

Income::Income()
{
	date = 20200101;
	money = 0;
	account = 0;
	incomeType = 0;
	classify = 1;
}

Income::Income(QDate da, double mon, int ac, int iT) :
	CapitalFlow(da, mon, ac), incomeType(iT) {
	classify = 1;
};

//向incomeRecord文件写入记录
void Income::write()
{
	fstream file;
	file.open("incomeRecord.dat", ios::out |ios::in| ios::binary);
	file.seekg(0, ios::beg);
	int datemark=0;
	double mon;
	int ac,it;
	long si;
	do //查找文件尾
	{
		file.read((char*)&si, sizeof(site));
		file.read((char*)&datemark, sizeof(datemark));
		file.read((char*)&mon, sizeof(mon));
		file.read((char*)&ac, sizeof(ac));
		file.read((char*)&it, sizeof(it));
	} while (ac!=0);//判断是否结束标志
	//置写指针位置
	file.seekp(-long(sizeof(it)),ios::cur);
	file.seekp(-long(sizeof(ac)), ios::cur);
	file.seekp(-long(sizeof(mon)), ios::cur);
	file.seekp(-long(sizeof(datemark)), ios::cur);
	file.seekp(-long(sizeof(si)), ios::cur);
	//写入新纪录
	file.write((char*)&file.tellp(), sizeof(si));//把site设为当前地址
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&account, sizeof(account));
	file.write((char*)&incomeType, sizeof(incomeType));
	//写入结束标志
	ac = 0;//结束的标志
	file.write((char*)&si, sizeof(si));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&ac, sizeof(ac));
	file.write((char*)&incomeType, sizeof(incomeType));
	file.close();
}

//incomeRecord文件的初始化
void Income::initial()
{
	fstream file;
	file.open("incomeRecord.dat", ios::out | ios::binary);
	file.seekg(0, ios::beg);
	int datemark=0;
	double mon=0;
	int ac, it=0;
	long si=0;
	//写入结束标志
	ac = 0;
	file.write((char*)&si, sizeof(si));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&ac, sizeof(ac));
	file.write((char*)&incomeType, sizeof(incomeType));
	file.close();
}

Spending::~Spending() { ; };

Spending::Spending()
{
	date = 20200101;
	money = 0;
	account = 0;
	spendingType = 0;
	classify = 2;
}

Spending::Spending(QDate da, double mon, int ac, int iT) :
	CapitalFlow(da, mon, ac), spendingType(iT) {
	classify=2;
};

//向spendingRecord文件写入记录
void Spending::write()
{
	fstream file;
	file.open("spendingRecord.dat", ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	int datemark = 0;
	double mon;
	int ac, it;
	long si;
	do //查找文件尾
	{
		file.read((char*)&si, sizeof(site));
		file.read((char*)&datemark, sizeof(datemark));
		file.read((char*)&mon, sizeof(mon));
		file.read((char*)&ac, sizeof(ac));
		file.read((char*)&it, sizeof(it));
	} while (ac != 0);//判断是否结束标志
	//置写指针位置
	file.seekp(-long(sizeof(it)), ios::cur);
	file.seekp(-long(sizeof(ac)), ios::cur);
	file.seekp(-long(sizeof(mon)), ios::cur);
	file.seekp(-long(sizeof(datemark)), ios::cur);
	file.seekp(-long(sizeof(si)), ios::cur);
	//写入新纪录
	file.write((char*)&file.tellp(), sizeof(si));//把site设为当前地址
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&account, sizeof(account));
	file.write((char*)&spendingType, sizeof(spendingType));
	//写入结束标志
	ac = 0;//结束的标志
	file.write((char*)&si, sizeof(si));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&ac, sizeof(ac));
	file.write((char*)&spendingType, sizeof(spendingType));
	file.close();
}

//spendingRecord文件的初始化
void Spending::initial()
{
	fstream file;
	file.open("spendingRecord.dat", ios::out | ios::binary);
	file.seekg(0, ios::beg);
	int datemark = 0;
	double mon = 0;
	int ac, it = 0;
	long si = 0;
	//写入结束标志
	ac = 0;
	file.write((char*)&si, sizeof(si));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&ac, sizeof(ac));
	file.write((char*)&spendingType, sizeof(spendingType));
	file.close();
}

Borrowing::~Borrowing() { ; };

Borrowing::Borrowing()
{
	date = 20200101;
	money = 0;
	account = 0;
	lender = 0;
	classify = 3;
}

Borrowing::Borrowing(QDate da, double mon, int ac,int iT) :
	CapitalFlow(da, mon, ac), lender(iT) {
	classify=3;
};

//向borrowingRecord文件写入记录
void Borrowing::write()
{
	fstream file;
	file.open("borrowingRecord.dat", ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	int datemark = 0;
	double mon;
	int ac, it;
	long si;
	do //查找文件尾
	{
		file.read((char*)&si, sizeof(site));
		file.read((char*)&datemark, sizeof(datemark));
		file.read((char*)&mon, sizeof(mon));
		file.read((char*)&ac, sizeof(ac));
		file.read((char*)&it, sizeof(it));
	} while (ac != 0);//判断是否结束标志
	//置写指针位置
	file.seekp(-long(sizeof(it)), ios::cur);
	file.seekp(-long(sizeof(ac)), ios::cur);
	file.seekp(-long(sizeof(mon)), ios::cur);
	file.seekp(-long(sizeof(datemark)), ios::cur);
	file.seekp(-long(sizeof(si)), ios::cur);
	//写入新纪录
	file.write((char*)&file.tellp(), sizeof(si));//把site设为当前地址
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&account, sizeof(account));
	file.write((char*)&lender, sizeof(lender));
	//写入结束标志
	ac = 0;//结束的标志
	file.write((char*)&si, sizeof(si));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&ac, sizeof(ac));
	file.write((char*)&lender, sizeof(lender));
	file.close();
}

//borrowingRecord文件的初始化
void Borrowing::initial()
{
	fstream file;
	file.open("borrowingRecord.dat", ios::out | ios::binary);
	file.seekg(0, ios::beg);
	int datemark = 0;
	double mon = 0;
	int ac, it = 0;
	long si = 0;
	//写入结束标志
	ac = 0;
	file.write((char*)&si, sizeof(si));
	file.write((char*)&date, sizeof(date));
	file.write((char*)&money, sizeof(money));
	file.write((char*)&ac, sizeof(ac));
	file.write((char*)&lender, sizeof(lender));
	file.close();
}
