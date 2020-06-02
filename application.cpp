#include "application.h"
#include "ui_application.h"

Application::Application(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::Application)
{
	ui->setupUi(this);

	init();
}

Application::~Application()
{
	delete ui;
}

void Application::init()
{
	//应用程序列表加载
	ui->applicationListWidget->setViewMode(QListView::IconMode);
	snakeItem = new QListWidgetItem;
	snakeItem->setText("贪吃蛇");
	ui->applicationListWidget->addItem(snakeItem);

	GAELItem = new QListWidgetItem;
	GAELItem->setText("正邪榜 - 恩怨录");
	ui->applicationListWidget->addItem(GAELItem);

	KIWItem = new QListWidgetItem;
	KIWItem->setText("知识就是财富");
	ui->applicationListWidget->addItem(KIWItem);
}

//接受loginDlg登录信号的槽函数
void Application::receiveMainWindow(quint32 id)
{
	this->uid = id;
	this->show();
}

void Application::on_applicationListWidget_clicked()
{
	if(ui->applicationListWidget->currentItem() == snakeItem)
	{	//贪吃蛇
		QString path("../qt_snake/snake.exe");
		QProcess *process = new QProcess(this);
		process->start(path);
	}
	else if(ui->applicationListWidget->currentItem() == GAELItem)
	{	//正邪榜 - 恩怨录
		QString path("../qt_gael/GAEL.exe");
		QProcess *process = new QProcess(this);
		process->start(path);
	}
	else if(ui->applicationListWidget->currentItem() == KIWItem)
	{	//知识就是财富
		QString path("../qt_kiw/KIW.exe");
		QStringList arguments;
		arguments << QString("%1").arg(uid);
		QProcess *process = new QProcess(this);
		process->start(path, arguments);
	}
}
