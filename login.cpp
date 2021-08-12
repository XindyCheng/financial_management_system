#include "login.h"

Login::Login(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.wrongPassword->hide();
	ui.lineEdit->setEchoMode(QLineEdit::Password);
}
void Login::on_checkBox_clicked()
{
	if (ui.checkBox->isChecked())
	{
		ui.lineEdit->setEchoMode(QLineEdit::Normal);
	}
	else
	{
		ui.lineEdit->setEchoMode(QLineEdit::Password);
	}
}
void Login::on_pushButton_clicked()
{
	QString str;
	str = ui.lineEdit->text();
	//��ȡ����
	QFile file("password.dat");
	file.open(QIODevice::ReadOnly);
	QDataStream in(&file);
	QString password;
	in >> password;	
	file.close();
	//��������Ƿ���ȷ
	if (str == password)
	{
		ui.wrongPassword->hide();
		QMessageBox message(QMessageBox::NoIcon, "Welcome!", "��½�ɹ���");
		message.exec();
		mainwin = new MainWindow;
		mainwin->show();
		this->hide();
	}
	else
	{
		ui.wrongPassword->show();
		QMessageBox::critical(NULL, "Attention", "�������", 
			QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
}
void MainWindow::on_pushButton_back_clicked()
{
	Login* log = new Login;
	log->show();
	this->hide();
}