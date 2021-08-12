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
	case 0: {chartTitle = "分类支出统计图";break;}
	case 1: {chartTitle = "账户支出统计图";break;}
	case 2: {chartTitle = "分类收入统计图";break;}
	case 3: {chartTitle = "账户收入统计图";break;}
	case 4: {chartTitle = "负债分布统计图";break;}
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
	//设置图表标题
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
	//读取账户信息
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
	//制作饼图
	series->append("微信", weixin);
	series->append("银行卡", bankcard);
	series->append("一卡通", yikatong);
	series->append("现金", cash);
	series->append("其他", other);
	series->setLabelsVisible();
	series->setLabelsPosition(QPieSlice::LabelOutside);
	//设置每份的颜色与标签
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
	//设置图表标题
	chart->addSeries(series);
	chart->setTitle("账户资产分布图");
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
	do //查找符合条件的记录，记录数据
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
	} while (ac != 0);//判断文件是否结束
	file.close();
}

void Sta::draw(QChart*& chart, QPieSeries*& series)
{
	//账户支出和账户收入图
	if (type == 1 || type == 3)
	{
		double totalValue = data[1] + data[2]
			+ data[3] + data[4]+data[5];
		//制作饼图
		series->append("微信", data[1]);
		series->append("银行卡", data[2]);
		series->append("一卡通", data[3]);
		series->append("现金", data[4]);
		series->append("其他", data[5]);
		series->setLabelsVisible();
		series->setLabelsPosition(QPieSlice::LabelOutside);
		//设置每份的颜色与标签
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
	//分类支出图
	else if (type == 0)
	{
		double totalValue = data[0] + data[1] + data[2]+ data[3] 
			+ data[4] + data[5] + data[6] + data[7];
		//制作饼图
		series->append("美食", data[0]);
		series->append("交通", data[1]);
		series->append("购物", data[2]);
		series->append("宿舍", data[3]);
		series->append("娱乐", data[4]);
		series->append("学习", data[5]);
		series->append("医疗", data[6]);
		series->append("其他", data[7]);
		series->setLabelsVisible();
		series->setLabelsPosition(QPieSlice::LabelOutside);
		//设置每份的颜色与标签
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
	//分类收入图
	else if (type == 2)
	{
		double totalValue = data[0] + data[1] + data[2] + data[3]
			+ data[4] + data[5] ;
		//制作饼图
		series->append("生活费", data[0]);
		series->append("兼职", data[1]);
		series->append("奖学金", data[2]);
		series->append("利息", data[3]);
		series->append("贷款", data[4]);
		series->append("其他", data[5]);
		series->setLabelsVisible();
		series->setLabelsPosition(QPieSlice::LabelOutside);
		//设置每份的颜色与标签
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
	//负债分布图
	else
	{
	double totalValue = data[0] + data[1] + data[2] + data[3]
		+ data[4] + data[5];
	//制作饼图
	series->append("朋友", data[0]);
	series->append("家人", data[1]);
	series->append("银行", data[2]);
	series->append("花呗", data[3]);
	series->append("京东白条", data[4]);
	series->append("其他", data[5]);
	series->setLabelsVisible();
	series->setLabelsPosition(QPieSlice::LabelOutside);
	//设置每份的颜色与标签
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