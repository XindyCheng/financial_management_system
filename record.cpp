#include "record.h"

Record::Record(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.comboBox_income->hide();
	ui.comboBox_lender->hide();
	ui.comboBox_spending->hide();
	ui.label_5->hide();
	ui.dateEdit->setDate(QDate::currentDate());
	QDoubleValidator* doubleValidator = new QDoubleValidator;
	doubleValidator->setRange(0, 9999999999);
	ui.lineEdit_money->setValidator(doubleValidator);
}

Record::~Record()
{
}

void Record::on_dateEdit_dateChanged()
{
	currentdate = ui.dateEdit->date();
}

void Record::on_lineEdit_money_editingFinished()
{
	currentMoney = ui.lineEdit_money->text().toDouble();
}

void Record::on_comboBox_account_currentIdexChanged()
{
	currentAccount = ui.comboBox_account->currentIndex();
}

void Record::on_comboBox_classify_currentIdexChanged()
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
	}
}

void Record::on_comboBox_income_currentIdexChanged()
{
	currentLabel = ui.comboBox_income->currentIndex();
}

void Record::on_comboBox_spending_currentIdexChanged()
{
	currentLabel = ui.comboBox_spending->currentIndex();
}

void Record::on_comboBox_lender_currentIdexChanged()
{
	currentLabel = ui.comboBox_lender->currentIndex();
}

void Record::on_pushButton_save_cliked()
{
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
		Income record(currentdate,currentMoney,currentAccount,currentLabel);
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
		Borrowing record(currentdate, currentMoney, currentAccount,currentLabel);
		record.write();
		record.changeBalance();
		break;
	}
	}
	QMessageBox message(QMessageBox::NoIcon, "保存成功", "保存成功！ ");
	message.exec();
	backToMainWindow();
}
