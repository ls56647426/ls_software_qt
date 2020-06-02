#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

//界面初始化
void MainWindow::init()
{
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
	//界面样式
	//主窗口
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);
	setAttribute(Qt::WA_TranslucentBackground);                     //隐藏窗口，只显示控件
	setFixedSize(this->size());                                     //禁止拖动窗口大小
	//登录主界面

	//消息提醒对话框
	msgBox.setWindowTitle("帅气的龙少提示您：");
	msgBox.setStandardButtons(QMessageBox::Ok);
	msgBox.setModal(true);
//    msgBox.setParent(this);

	//默认焦点
	ui->userNameLineEdit->setFocus();

	//tab键切换焦点顺序
	//登录界面
	setTabOrder(ui->userNameLineEdit, ui->pwdLineEdit);
	setTabOrder(ui->pwdLineEdit, ui->remeberCheckBox);
	setTabOrder(ui->remeberCheckBox, ui->autoLoginCheckBox);
	setTabOrder(ui->autoLoginCheckBox, ui->loginBtn);
	setTabOrder(ui->loginBtn, ui->toRegisterBtn);
	setTabOrder(ui->toRegisterBtn, ui->toFindBtn);
	setTabOrder(ui->toFindBtn, ui->toAlterBtn);
	setTabOrder(ui->toAlterBtn, ui->closeBtn);
	setTabOrder(ui->closeBtn, ui->miniBtn);
	setTabOrder(ui->miniBtn, ui->userNameLineEdit);
	//注册界面
	setTabOrder(ui->registerUsernamelineEdit, ui->registerPwdlineEdit);
	setTabOrder(ui->registerPwdlineEdit, ui->registerPwd2lineEdit);
	setTabOrder(ui->registerPwd2lineEdit, ui->registerMobileLineEdit);
	setTabOrder(ui->registerMobileLineEdit, ui->registerReturnLoginBtn);
	setTabOrder(ui->registerReturnLoginBtn, ui->registerBtn);
	setTabOrder(ui->registerBtn, ui->registerUsernamelineEdit);
	//修改界面
	setTabOrder(ui->alterUsernamelineEdit, ui->alterOldPwdlineEdit);
	setTabOrder(ui->alterOldPwdlineEdit, ui->alterMobileLineEdit);
	setTabOrder(ui->alterMobileLineEdit, ui->alterNewPwdlineEdit);
	setTabOrder(ui->alterNewPwdlineEdit, ui->alterNewPwd2lineEdit);
	setTabOrder(ui->alterNewPwd2lineEdit, ui->alterReturnLoginBtn);
	setTabOrder(ui->alterReturnLoginBtn, ui->alterBtn);
	setTabOrder(ui->alterBtn, ui->alterUsernamelineEdit);
	//找回界面
	setTabOrder(ui->findUsernameLineEdit, ui->findMobileLineEdit);
	setTabOrder(ui->findMobileLineEdit, ui->findNewPwdLineEdit);
	setTabOrder(ui->findNewPwdLineEdit, ui->findNewPwd2LineEdit);
	setTabOrder(ui->findNewPwd2LineEdit, ui->findReturnLoginBtn);
	setTabOrder(ui->findReturnLoginBtn, ui->findBtn);
	setTabOrder(ui->findBtn, ui->findUsernameLineEdit);

	//lineEdit里的默认回车按钮
	//登录界面
	connect(ui->userNameLineEdit, SIGNAL(returnPressed()), ui->loginBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->pwdLineEdit, SIGNAL(returnPressed()), ui->loginBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	//注册界面
	connect(ui->registerUsernamelineEdit, SIGNAL(returnPressed()), ui->registerBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->registerPwdlineEdit, SIGNAL(returnPressed()), ui->registerBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->registerPwd2lineEdit, SIGNAL(returnPressed()), ui->registerBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->registerMobileLineEdit, SIGNAL(returnPressed()), ui->registerBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	//修改界面
	connect(ui->alterUsernamelineEdit, SIGNAL(returnPressed()), ui->alterBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->alterOldPwdlineEdit, SIGNAL(returnPressed()), ui->alterBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->alterMobileLineEdit, SIGNAL(returnPressed()), ui->alterBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->alterNewPwdlineEdit, SIGNAL(returnPressed()), ui->alterBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->alterNewPwd2lineEdit, SIGNAL(returnPressed()), ui->alterBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	//找回界面
	connect(ui->findUsernameLineEdit, SIGNAL(returnPressed()), ui->findBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->findMobileLineEdit, SIGNAL(returnPressed()), ui->findBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->findNewPwdLineEdit, SIGNAL(returnPressed()), ui->findBtn, SIGNAL(clicked()), Qt::UniqueConnection);
	connect(ui->findNewPwd2LineEdit, SIGNAL(returnPressed()), ui->findBtn, SIGNAL(clicked()), Qt::UniqueConnection);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	bPressFlag = true;
	beginDrag = event->pos();
	QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
	bPressFlag = false;
	QWidget::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
	if(bPressFlag)
	{
		QPoint relaPos(QCursor::pos() - beginDrag);
		move(relaPos);
	}
	QWidget::mouseMoveEvent(event);
}

//登录
void MainWindow::on_loginBtn_clicked()
{
	QString username = ui->userNameLineEdit->text();
	QString password = ui->pwdLineEdit->text();

	QFile file("remPwd.txt");
	QTextStream fileStream(&file);

	//判空
	if(username.isEmpty())
	{
		msgBox.setText("账号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->userNameLineEdit->setFocus();
		return;
	}
	if(password.isEmpty())
	{
		msgBox.setText("密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->pwdLineEdit->setFocus();
		return;
	}

	//根据用户名和密码查询用户
	Specification *spec = new Specification;
	spec->setSqlWhere(spec->And(spec->equal("username", spec->tranString(username)), spec->equal(
									"password", spec->tranString(password))));
	User* user = ud.findOne(spec);

	if(user == nullptr)
	{   //账号或密码错误
		ui->userNameLineEdit->clear();
		ui->pwdLineEdit->clear();
		msgBox.setText("账号或密码错误，请重新输入！");
		msgBox.setIcon(QMessageBox::Icon::Critical);
		msgBox.exec();
		ui->userNameLineEdit->setFocus();
	}
	else
	{   //登录成功
		ui->loginBtn->setText("取消");
		//用户缓存

		//切换到主窗口
		this->hide();
		emit showApplication(user->info["id"].toUInt());
	}
}

//切换到注册界面
void MainWindow::on_toRegisterBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(1);                          //切换到注册页面
	setWindowTitle("注册");
}

//注册界面返回到登录主页面
void MainWindow::on_registerReturnLoginBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
}

//注册
void MainWindow::on_registerBtn_clicked()
{
	QString username = ui->registerUsernamelineEdit->text();
	QString password = ui->registerPwdlineEdit->text();
	QString password2 = ui->registerPwd2lineEdit->text();
	QString mobile = ui->registerMobileLineEdit->text();

	//判空
	if(username.isEmpty())
	{
		msgBox.setText("账号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->registerUsernamelineEdit->setFocus();
		return;
	}
	if(password.isEmpty())
	{
		msgBox.setText("密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->registerPwdlineEdit->setFocus();
		return;
	}
	if(password2.isEmpty())
	{
		msgBox.setText("确认密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->registerPwd2lineEdit->setFocus();
		return;
	}
	if(mobile.isEmpty())
	{
		msgBox.setText("手机号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->registerMobileLineEdit->setFocus();
		return;
	}
	if(password != password2)
	{
		msgBox.setText("确认密码不一致，请重新填写！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->registerPwd2lineEdit->clear();
		ui->registerPwd2lineEdit->setFocus();
		return;
	}

	Specification *spec = new Specification;
	spec->setSqlWhere(spec->equal("username", spec->tranString(username)));

	if(ud.findOne(spec) != nullptr)
	{   //用户名已存在
		ui->registerUsernamelineEdit->clear();
		msgBox.setText("用户名已存在，请重新输入！");
		msgBox.setIcon(QMessageBox::Icon::Critical);
		msgBox.exec();
		ui->registerUsernamelineEdit->setFocus();
		return;
	}

	//注册
	User *user = new User;
	user->setUsername(username);
	user->setPassword(password);
	user->setMobile(mobile);

	ud.save(user);

	msgBox.setText("注册成功！");
	msgBox.setIcon(QMessageBox::Icon::NoIcon);
	msgBox.exec();
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
}

//修改密码界面返回到登录主界面
void MainWindow::on_alterReturnLoginBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
}

//切换到修改密码页面
void MainWindow::on_toAlterBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(2);                          //切换到修改密码页面
	setWindowTitle("修改密码");
}

//修改密码
void MainWindow::on_alterBtn_clicked()
{
	QString username = ui->alterUsernamelineEdit->text();
	QString oldPwd = ui->alterOldPwdlineEdit->text();
	QString mobile = ui->alterMobileLineEdit->text();
	QString newPwd = ui->alterNewPwdlineEdit->text();
	QString newPwd2 = ui->alterNewPwd2lineEdit->text();

	//判空
	if(username.isEmpty())
	{
		msgBox.setText("账号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterUsernamelineEdit->setFocus();
		return;
	}
	if(oldPwd.isEmpty())
	{
		msgBox.setText("新密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterOldPwdlineEdit->setFocus();
		return;
	}
	if(mobile.isEmpty())
	{
		msgBox.setText("手机号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterMobileLineEdit->setFocus();
		return;
	}
	if(newPwd.isEmpty())
	{
		msgBox.setText("新密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterNewPwdlineEdit->setFocus();
		return;
	}
	if(newPwd2.isEmpty())
	{
		msgBox.setText("确认密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterNewPwd2lineEdit->setFocus();
		return;
	}
	if(newPwd != newPwd2)
	{
		msgBox.setText("确认密码不一致，请重新填写！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterNewPwd2lineEdit->clear();
		ui->alterNewPwd2lineEdit->setFocus();
		return;
	}

	//用户确认
	Specification *spec = new Specification;
	QList<QString> list;
	list.append(spec->equal("username", spec->tranString(username)));
	list.append(spec->equal("password", spec->tranString(oldPwd)));
	list.append(spec->equal("mobile", spec->tranString(mobile)));
	spec->setSqlWhere(spec->And(list));

	User *user = nullptr;
	user = ud.findOne(spec);

	if(user == nullptr)
	{   //用户验证失败
		ui->alterUsernamelineEdit->clear();
		ui->alterOldPwdlineEdit->clear();
		msgBox.setText("用户验证失败，请重新输入！");
		msgBox.setIcon(QMessageBox::Icon::Critical);
		msgBox.exec();
		ui->alterUsernamelineEdit->setFocus();
		return;
	}

	//修改
	user->setPassword(newPwd);

	ud.save(user);

	msgBox.setText("修改成功！");
	msgBox.setIcon(QMessageBox::Icon::NoIcon);
	msgBox.exec();
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
}


//切换到找回密码界面
void MainWindow::on_toFindBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(3);                          //切换到修改密码页面
	setWindowTitle("找回密码");
}

//切换到登录页面
void MainWindow::on_findReturnLoginBtn_clicked()
{
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
}

//找回密码
void MainWindow::on_findBtn_clicked()
{
	QString username = ui->findUsernameLineEdit->text();
	QString mobile = ui->findMobileLineEdit->text();
	QString newPwd = ui->findNewPwdLineEdit->text();
	QString newPwd2 = ui->findNewPwd2LineEdit->text();

	//判空
	if(username.isEmpty())
	{
		msgBox.setText("账号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterUsernamelineEdit->setFocus();
		return;
	}
	if(mobile.isEmpty())
	{
		msgBox.setText("手机号为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterMobileLineEdit->setFocus();
		return;
	}
	if(newPwd.isEmpty())
	{
		msgBox.setText("新密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterNewPwdlineEdit->setFocus();
		return;
	}
	if(newPwd2.isEmpty())
	{
		msgBox.setText("确认密码为空，请填写完整！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterNewPwd2lineEdit->setFocus();
		return;
	}
	if(newPwd != newPwd2)
	{
		msgBox.setText("确认密码不一致，请重新填写！");
		msgBox.setIcon(QMessageBox::Icon::Warning);
		msgBox.exec();
		ui->alterNewPwd2lineEdit->clear();
		ui->alterNewPwd2lineEdit->setFocus();
		return;
	}

	//用户确认
	Specification *spec = new Specification;
	spec->setSqlWhere(spec->And(spec->equal("username", spec->tranString(username)),
								spec->equal("mobile", spec->tranString(mobile))));
	User *user = nullptr;
	user = ud.findOne(spec);
	if(user == nullptr)
	{   //用户确认失败
		ui->findUsernameLineEdit->clear();
		ui->findMobileLineEdit->clear();
		msgBox.setText("用户确认失败，请重新输入！");
		msgBox.setIcon(QMessageBox::Icon::Critical);
		msgBox.exec();
		ui->findUsernameLineEdit->setFocus();
	}

	//找回
	user->setPassword(newPwd);

	ud.save(user);

	msgBox.setText("找回成功！");
	msgBox.setIcon(QMessageBox::Icon::NoIcon);
	msgBox.exec();
	ui->stackedWidget->setCurrentIndex(0);                          //切换到登录主页面
	setWindowTitle("登录");
}
