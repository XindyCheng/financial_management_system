#include "settings.h"

Settings::Settings(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//从文件中读取账户信息，并显示到窗口上
	fstream file;
	file.open("userinfo.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double a;
	file.read((char*)&a, sizeof(a));
	ui.label_money->setText(QString::number(a));
	file.close();
	ui.lineEdit_old->setEchoMode(QLineEdit::Password);
	ui.lineEdit_new->setEchoMode(QLineEdit::Password);
	QDoubleValidator* doubleValidator = new QDoubleValidator;
	doubleValidator->setRange(0, 9999999999);
	ui.lineEdit_money->setValidator(doubleValidator);
}

Settings::~Settings()
{
}

void Settings::on_incomeInitial_cliked()
{
	Income ic;
	ic.initial();
	QMessageBox message(QMessageBox::NoIcon, "成功", "初始化成功！ ");
	message.exec();
}

void Settings::on_spendingInitial_cliked()
{
	Spending ic;
	ic.initial();
	QMessageBox message(QMessageBox::NoIcon, "成功", "初始化成功！ ");
	message.exec();
}

void Settings::on_borrowingInitial_cliked()
{
	Borrowing ic;
	ic.initial();
	QMessageBox message(QMessageBox::NoIcon, "成功", "初始化成功！ ");
	message.exec();
}

void Settings::on_userinfoInitial_cliked()
{
	fstream file;
	file.open("userinfo.dat", ios::out | ios::binary);
	file.seekg(0, ios::beg);
	double a = 0;
	file.write((char*)&a, sizeof(a));
	file.write((char*)&a, sizeof(a));
	file.write((char*)&a, sizeof(a));
	file.write((char*)&a, sizeof(a));
	file.write((char*)&a, sizeof(a));
	file.write((char*)&a, sizeof(a));
	QMessageBox message(QMessageBox::NoIcon, "成功", "初始化成功！ ");
	message.exec();
}

void Settings::on_comboBox_account_currentIdexChanged()
{
	//从文件中读取账户信息，并显示到窗口上
	fstream file;
	file.open("userinfo.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double a[6];
	file.read((char*)&a[0], sizeof(a[1]));
	file.read((char*)&a[1], sizeof(a[1]));
	file.read((char*)&a[2], sizeof(a[1]));
	file.read((char*)&a[3], sizeof(a[1]));
	file.read((char*)&a[4], sizeof(a[1]));
	file.read((char*)&a[5], sizeof(a[1]));
	ui.label_money->setText(QString::number(a[ui.comboBox_account->currentIndex()]));
	file.close();
}

void Settings::on_pushButton_banlance_clicked()
{
	fstream file;
	file.open("userinfo.dat", ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double a;
	int account = ui.comboBox_account->currentIndex();
	//将指针移动到文件中储存该账户信息的位置并修改余额
	for (int i = 0;i <= account;i++) {
		file.read((char*)&a, sizeof(a));
	}
	file.seekp(-long(sizeof(a)), ios::cur);
	a = ui.lineEdit_money->text().toDouble();
	file.write((char*)&a, sizeof(a));
	file.close();
	QMessageBox message(QMessageBox::NoIcon, "成功", "余额修改成功！ ");
	message.exec();
	//及时显示新的余额
	file.open("userinfo.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double b[6];
	file.read((char*)&b[0], sizeof(b[1]));
	file.read((char*)&b[1], sizeof(b[1]));
	file.read((char*)&b[2], sizeof(b[1]));
	file.read((char*)&b[3], sizeof(b[1]));
	file.read((char*)&b[4], sizeof(b[1]));
	file.read((char*)&b[5], sizeof(b[1]));
	ui.label_money->setText(QString::number(b[ui.comboBox_account->currentIndex()]));
	file.close();
}

void Settings::on_pushButton_password_clicked()
{
	QString str;
	str = ui.lineEdit_old->text();
	//读取密码
	QFile file("password.dat");
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	QString password;
	in >> password;
	file.close();
	//检查密码是否正确
	if (str == password)
	{
		file.open(QIODevice::WriteOnly);
		QDataStream out(&file);
		out << QString(ui.lineEdit_new->text());
		file.close();
		QMessageBox message(QMessageBox::NoIcon, "成功", "密码修改成功！");
		message.exec();
	}
	else
	{
		QMessageBox::critical(NULL, "Attention", "原密码错误",
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}

void Settings::on_checkBox_clicked()
{
	if (ui.checkBox->isChecked())
	{
		ui.lineEdit_old->setEchoMode(QLineEdit::Normal);
	}
	else
	{
		ui.lineEdit_old->setEchoMode(QLineEdit::Password);
	}
}

void Settings::on_checkBox_2_clicked()
{
	if (ui.checkBox_2->isChecked())
	{
		ui.lineEdit_new->setEchoMode(QLineEdit::Normal);
	}
	else
	{
		ui.lineEdit_new->setEchoMode(QLineEdit::Password);
	}
}