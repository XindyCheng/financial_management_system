#include "statistic.h"

Statistic::Statistic(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.dateEdit->setDate(QDate::currentDate());
	ui.dateEdit_2->setDate(QDate::currentDate());
}

Statistic::~Statistic()
{
}

void Statistic::on_dateEdit_dateChanged()
{
	currentdate = ui.dateEdit->date();
}

void Statistic::on_dateEdit_2_dateChanged()
{
	currentdate2 = ui.dateEdit_2->date();
}

void Statistic::on_comboBox_currentIdexChanged()
{
	currentType = ui.comboBox->currentIndex();
	switch (currentType)
	{
	case 0: {chartTitle = "����֧��ͳ��ͼ";break;}
	case 1: {chartTitle = "�˻�֧��ͳ��ͼ";break;}
	case 2: {chartTitle = "��������ͳ��ͼ";break;}
	case 3: {chartTitle = "�˻�����ͳ��ͼ";break;}
	case 4: {chartTitle = "��ծ�ֲ�ͳ��ͼ";break;}
	}
}

void Statistic::on_pushButton_generate_clicked()
{
	this->resize(980, 550);
	chart = new QChart;
	series = new QPieSeries();  
	Sta sta(currentdate, currentdate2, currentType);
	sta.staData();
	sta.draw(chart, series);
	//����ͼ�����
	date2 = currentdate2.toString("yyyy-MM-dd");
	date1 = currentdate.toString("yyyy-MM-dd");
	date1.append("~");
	date1.append(date2);
	date1.append(chartTitle);
	chart->addSeries(series);
	chart->setTitle(date1);
	chart->legend()->setAlignment(Qt::AlignRight);
	ui.widget->setChart(chart);
}

void Statistic::on_pushButton_account_clicked()
{
	this->resize(980, 550);
	chart = new QChart;
	series = new QPieSeries();
	//��ȡ�˻���Ϣ
	fstream file;
	file.open("userinfo.dat", ios::in | ios::binary);
	file.seekg(0, ios::beg);
	double weixin, bankcard, yikatong, cash, other;
	file.read((char*)&weixin, sizeof(weixin));
	file.read((char*)&bankcard, sizeof(weixin));
	file.read((char*)&yikatong, sizeof(weixin));
	file.read((char*)&cash, sizeof(weixin));
	file.read((char*)&other, sizeof(weixin));
	file.close();
	double totalValue = weixin + bankcard + yikatong + cash + other;
	//������ͼ
	series->append("΢��", weixin);
	series->append("���п�", bankcard);
	series->append("һ��ͨ", yikatong);
	series->append("�ֽ�", cash);
	series->append("����", other);
	series->setLabelsVisible();
	series->setLabelsPosition(QPieSlice::LabelOutside);
	//����ÿ�ݵ���ɫ���ǩ
	QPieSlice* slice = series->slices().at(0);
	slice->setColor(QColor(175, 215, 237, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%" 
		+ "-"+ QString("%1").arg(slice->value()) );
	slice = series->slices().at(1);
	slice->setColor(QColor(252, 157, 154, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(2);
	slice->setColor(QColor(249, 205, 173, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(3);
	slice->setColor(QColor(200, 200, 169, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(4);
	slice->setColor(QColor(131, 175, 155, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	//����ͼ�����
	chart->addSeries(series);
	chart->setTitle("�˻��ʲ��ֲ�ͼ");
	chart->legend()->setAlignment(Qt::AlignRight);
	ui.widget->setChart(chart);
}


Sta::Sta(QDate qb, QDate qe, int ty)
{
	qbegin = qb;
	qend = qe;
	type = ty;
	for (int i = 0;i < 8;i++)data[i] = 0;
}

Sta::~Sta()
{
	;
}

void Sta::staData()
{
	if (type == 0 || type == 1)filename = "spendingRecord.dat";
	else if (type == 2 || type == 3)filename = "incomeRecord.dat";
	else filename = "borrowingRecord.dat";
	fstream file;
	file.open(filename, ios::out | ios::in | ios::binary);
	file.seekg(0, ios::beg);
	int da, ac, la;
	double mon;
	long si;
	do //���ҷ��������ļ�¼����¼����
	{
		file.read((char*)&si, sizeof(si));
		file.read((char*)&da, sizeof(da));
		file.read((char*)&mon, sizeof(mon));
		file.read((char*)&ac, sizeof(ac));
		file.read((char*)&la, sizeof(la));
		QDate qd = toQdate(da);
		if (ac != 0 && qd >= qbegin && qd <= qend )
		{
			if (type == 0 || type == 2||type==4)
			{
				data[la] += mon;
			}
			if (type == 1 || type == 3)
			{
				data[ac] += mon;
			}
		}
	} while (ac != 0);//�ж��ļ��Ƿ����
	file.close();
}

void Sta::draw(QChart*& chart, QPieSeries*& series)
{
	//�˻�֧�����˻�����ͼ
	if (type == 1 || type == 3)
	{
		double totalValue = data[1] + data[2]
			+ data[3] + data[4]+data[5];
		//������ͼ
		series->append("΢��", data[1]);
		series->append("���п�", data[2]);
		series->append("һ��ͨ", data[3]);
		series->append("�ֽ�", data[4]);
		series->append("����", data[5]);
		series->setLabelsVisible();
		series->setLabelsPosition(QPieSlice::LabelOutside);
		//����ÿ�ݵ���ɫ���ǩ
		QPieSlice* slice = series->slices().at(0);
		slice->setColor(QColor(175, 215, 237, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(1);
		slice->setColor(QColor(252, 157, 154, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(2);
		slice->setColor(QColor(249, 205, 173, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(3);
		slice->setColor(QColor(200, 200, 169, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(4);
		slice->setColor(QColor(131, 175, 155, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
	}
	//����֧��ͼ
	else if (type == 0)
	{
		double totalValue = data[0] + data[1] + data[2]+ data[3] 
			+ data[4] + data[5] + data[6] + data[7];
		//������ͼ
		series->append("��ʳ", data[0]);
		series->append("��ͨ", data[1]);
		series->append("����", data[2]);
		series->append("����", data[3]);
		series->append("����", data[4]);
		series->append("ѧϰ", data[5]);
		series->append("ҽ��", data[6]);
		series->append("����", data[7]);
		series->setLabelsVisible();
		series->setLabelsPosition(QPieSlice::LabelOutside);
		//����ÿ�ݵ���ɫ���ǩ
		QPieSlice* slice = series->slices().at(0);
		slice->setColor(QColor(252, 157, 154, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(1);
		slice->setColor(QColor(175, 215, 237, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(2);
		slice->setColor(QColor(249, 205, 173, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(3);
		slice->setColor(QColor(200, 200, 169, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(4);
		slice->setColor(QColor(131, 175, 155, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(5);
		slice->setColor(QColor(119, 52, 96, 200));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(6);
		slice->setColor(QColor(203, 203, 203, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(7);
		slice->setColor(QColor(250, 227, 113, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
	}
	//��������ͼ
	else if (type == 2)
	{
		double totalValue = data[0] + data[1] + data[2] + data[3]
			+ data[4] + data[5] ;
		//������ͼ
		series->append("�����", data[0]);
		series->append("��ְ", data[1]);
		series->append("��ѧ��", data[2]);
		series->append("��Ϣ", data[3]);
		series->append("����", data[4]);
		series->append("����", data[5]);
		series->setLabelsVisible();
		series->setLabelsPosition(QPieSlice::LabelOutside);
		//����ÿ�ݵ���ɫ���ǩ
		QPieSlice* slice = series->slices().at(0);
		slice->setColor(QColor(175, 215, 237, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(1);
		slice->setColor(QColor(252, 157, 154, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(2);
		slice->setColor(QColor(249, 205, 173, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(3);
		slice->setColor(QColor(200, 200, 169, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(4);
		slice->setColor(QColor(131, 175, 155, 255));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
		slice = series->slices().at(5);
		slice->setColor(QColor(119, 52, 96, 200));
		slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
			+ "-" + QString("%1").arg(slice->value()));
	}
	//��ծ�ֲ�ͼ
	else
	{
	double totalValue = data[0] + data[1] + data[2] + data[3]
		+ data[4] + data[5];
	//������ͼ
	series->append("����", data[0]);
	series->append("����", data[1]);
	series->append("����", data[2]);
	series->append("����", data[3]);
	series->append("��������", data[4]);
	series->append("����", data[5]);
	series->setLabelsVisible();
	series->setLabelsPosition(QPieSlice::LabelOutside);
	//����ÿ�ݵ���ɫ���ǩ
	QPieSlice* slice = series->slices().at(0);
	slice->setColor(QColor(175, 215, 237, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(1);
	slice->setColor(QColor(252, 157, 154, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(2);
	slice->setColor(QColor(249, 205, 173, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(3);
	slice->setColor(QColor(200, 200, 169, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(4);
	slice->setColor(QColor(131, 175, 155, 255));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
	slice = series->slices().at(5);
	slice->setColor(QColor(119, 52, 96, 200));
	slice->setLabel(slice->label() + ":" + QString("%1").arg(slice->value() / totalValue * 100) + "%"
		+ "-" + QString("%1").arg(slice->value()));
    }	
}