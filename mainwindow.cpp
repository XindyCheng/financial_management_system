#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//从文件中读取账户信息，并显示到窗口上
	fstream file;
	file.open("userinfo.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double weixin, bankcard, yikatong, cash, liability, other;
	file.read((char*)&weixin, sizeof(weixin));
	file.read((char*)&bankcard, sizeof(weixin));
	file.read((char*)&yikatong, sizeof(weixin));
	file.read((char*)&cash, sizeof(weixin));
	file.read((char*)&other, sizeof(weixin));
	file.read((char*)&liability, sizeof(weixin));
	ui.label_bankcard->setText(QString::number(bankcard));
	ui.label_weixin->setText(QString::number(weixin));
	ui.label_other->setText(QString::number(other));
	ui.label_yikatong->setText(QString::number(yikatong));
	ui.label_cash->setText(QString::number(cash));
	ui.label_liability->setText(QString::number(liability));
}

MainWindow::~MainWindow()
{
}

void MainWindow::on_pushButton_record_clicked()
{
	recordWindow = new Record;
	recordWindow->resize(670, 385);
	recordWindow->show();
	this->hide();
}

void MainWindow::on_pushButton_query_clicked()
{
	queryWindow = new Query;
	queryWindow->resize(905,430);
	queryWindow->show();
	this->hide();
}

void MainWindow::on_pushButton_statistic_clicked()
{
	statisticWindow = new Statistic;
	statisticWindow->show();
	this->hide();
}

void MainWindow::on_pushButton_settings_clicked()
{
	settingsWindow = new Settings;
	settingsWindow->resize(620, 570);
	settingsWindow->show();
	this->hide();
}

void Record::on_pushButton_back_clicked()
{
	MainWindow*mainWin = new MainWindow;
	mainWin->show();
	this->hide();
}

void Record::backToMainWindow()
{
	MainWindow* mainWin = new MainWindow;
	mainWin->show();
	this->hide();
}

void Query::on_pushButton_back_clicked()
{
	MainWindow* mainWin = new MainWindow;
	mainWin->show();
	this->hide();
}

void Statistic::on_pushButton_back_clicked()
{
	MainWindow* mainWin = new MainWindow;
	mainWin->show();
	this->hide();
}

void Settings::on_pushButton_back_clicked()
{
	MainWindow* mainWin = new MainWindow;
	mainWin->show();
	this->hide();
}

