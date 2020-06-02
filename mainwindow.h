#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "userdao.h"

#include <QMessageBox>
#include <QFile>
#include <QFileInfo>
#include <QGraphicsDropShadowEffect>
#include <QStyle>
#include <QMouseEvent>
#include <QCache>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

	void init();
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private slots:
	void on_loginBtn_clicked();

	void on_toRegisterBtn_clicked();

	void on_registerReturnLoginBtn_clicked();

	void on_registerBtn_clicked();

	void on_alterReturnLoginBtn_clicked();

	void on_toAlterBtn_clicked();

	void on_alterBtn_clicked();

	void on_toFindBtn_clicked();

	void on_findReturnLoginBtn_clicked();

	void on_findBtn_clicked();

signals:
	void showApplication(quint32 id);

private:
	Ui::MainWindow *ui;

	UserDao ud;
	QMessageBox msgBox;
	bool bPressFlag;
	QPoint beginDrag;
};
#endif // MAINWINDOW_H
