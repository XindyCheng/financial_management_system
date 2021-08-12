#include "details.h"

Details::Details(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	QDoubleValidator* doubleValidator = new QDoubleValidator;
	doubleValidator->setRange(0, 9999999999);
	ui.lineEdit_money->setValidator(doubleValidator);
}

Details::~Details()
{
}

//初始化页面，把该条记录的信息展示在页面上
void Details::display()
{
	QString str0;
	str0.setNum(file);
	str0.setNum(loca);
	long si;
	int da;
	const char* filename;
	IC = file;
	switch (file) {
	case 0:break;
	case 1: {filename = "incomeRecord.dat";break;}
	case 2: {filename = "spendingRecord.dat";break;}
	case 3: {filename = "borrowingRecord.dat";break;}
	case 4: {filename = "modifyRecord.dat";break;}
	}
	fstream fil;
	fil.open(filename, ios::out | ios::in | ios::binary);
	fil.seekg(0, ios::beg);
	//置读指针于该记录的位置
	fil.seekg(loca, ios::beg);
	//读出该记录
	fil.read((char*)&si, sizeof(loca));
	fil.read((char*)&da, sizeof(da));
	fil.read((char*)&IM, sizeof(IM));
	fil.read((char*)&IA, sizeof(IA));
	fil.read((char*)&IL, sizeof(IL));
	fil.close();
	IDa = toQdate(da);
	ui.dateEdit->setDate(IDa);
	ui.comboBox_account->setCurrentIndex(IA);
	ui.comboBox_classify->setCurrentIndex(IC);
	QString str;
	str.setNum(IM);
	ui.lineEdit_money->setText(str);
	switch (file)
	{
	case 0: {ui.label_5->hide();ui.comboBox_income->hide();
		ui.comboBox_lender->hide();
		ui.comboBox_spending->hide();break;}
	case 1: {ui.label_5->show();ui.comboBox_income->show();
		ui.comboBox_income->setCurrentIndex(IL);
		ui.comboBox_lender->hide();ui.comboBox_spending->hide();break;}
	case 2: {ui.label_5->show();ui.comboBox_spending->show();
		ui.comboBox_spending->setCurrentIndex(IL);
		ui.comboBox_lender->hide();ui.comboBox_income->hide();break;}
	case 3: {ui.label_5->show();ui.comboBox_lender->show();
		ui.comboBox_lender->setCurrentIndex(IL);
		ui.comboBox_income->hide();ui.comboBox_spending->hide();break;}
	case 4: {ui.label_5->hide();ui.comboBox_income->hide();ui.comboBox_lender->hide();
		ui.comboBox_spending->hide();}
	}
}

void Details::on_pushButton_back_clicked()
{
	queryWindow = new Query;
	queryWindow->show();
	this->hide();
}

void Details::on_pushButton_delet_clicked()
{
	if (IC == currentClassify && IM == currentMoney && IL == currentLabel
		&& IA == currentAccount && IDa == currentdate)
	{
		Search se(file, loca);
		se.delet();
		se.account = IA;
		se.money = IM;
		se.classify = IC;
		se.resetBanlance();
		QMessageBox message(QMessageBox::NoIcon, "成功!", "删除成功！");
		message.exec();
		queryWindow = new Query;
		queryWindow->show();
		this->hide();
	}
	else
	{
		QMessageBox::critical(NULL, "无法删除", "页面信息已更改，无法删除，请退回上一步再进行操作",
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
}

void Details::on_pushButton_save_clicked()
{
	Search se(file, loca);
	se.delet();
	se.account = IA;
	se.money = IM;
	se.classify = IC;
	se.resetBanlance();
	if (currentAccount == 0)
	{
		QMessageBox::critical(NULL, "信息不完整", "请选择账户",
			QMessageBox::Ok, QMessageBox::Ok);
		return;
	}
	switch (currentClassify)
	{
	case 0:
	{QMessageBox::critical(NULL, "信息不完整", "请选择分类",
		QMessageBox::Ok, QMessageBox::Ok);
	return;
	break;
	}
	case 1:
	{
		Income record(currentdate, currentMoney, currentAccount, currentLabel);
		record.write();
		record.changeBalance();
		break;
	}
	case 2:
	{
		Spending record(currentdate, currentMoney, currentAccount, currentLabel);
		record.write();
		record.changeBalance();
		break;
	}
	case 3:
	{
		Borrowing record(currentdate, currentMoney, currentAccount, currentLabel);
		record.write();
		record.changeBalance();
		break;
	}
	QMessageBox message(QMessageBox::NoIcon, "成功!", "保存成功！");
	message.exec();
	queryWindow = new Query;
	queryWindow->show();
	this->hide();
	}
}

void Details::on_comboBox_account_currentIdexChanged()
{
	currentAccount = ui.comboBox_account->currentIndex();
}

void Details::on_comboBox_classify_currentIdexChanged()
{
	currentClassify = ui.comboBox_classify->currentIndex();
	currentLabel = 0;
	switch (ui.comboBox_classify->currentIndex())
	{
	case 0: {ui.label_5->hide();ui.comboBox_income->hide();
		ui.comboBox_lender->hide();
		ui.comboBox_spending->hide();break;}
	case 1: {ui.label_5->show();ui.comboBox_income->show();
		ui.comboBox_lender->hide();ui.comboBox_spending->hide();break;}
	case 2: {ui.label_5->show();ui.comboBox_spending->show();
		ui.comboBox_lender->hide();ui.comboBox_income->hide();break;}
	case 3: {ui.label_5->show();ui.comboBox_lender->show();
		ui.comboBox_income->hide();ui.comboBox_spending->hide();break;}
	case 4: {ui.label_5->hide();ui.comboBox_income->hide();ui.comboBox_lender->hide();
		ui.comboBox_spending->hide();}
	}
}

void Details::on_comboBox_income_currentIdexChanged()
{
	currentLabel = ui.comboBox_income->currentIndex();
}

void Details::on_comboBox_spending_currentIdexChanged()
{
	currentLabel = ui.comboBox_spending->currentIndex();
}

void Details::on_comboBox_lender_currentIdexChanged()
{
	currentLabel = ui.comboBox_lender->currentIndex();
}

void Details::on_dateEdit_dateChanged()
{
	currentdate = ui.dateEdit->date();
}

void Details::on_lineEdit_money_editingFinished()
{
	currentMoney = ui.lineEdit_money->text().toDouble();
}

void Query::toDetails(int fileIndex, long location)
{
	Details* DeWin = new Details;
	DeWin->file = fileIndex;
	DeWin->loca = location;
	DeWin->show();
	DeWin->display();
	this->hide();
}
