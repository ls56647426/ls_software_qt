#include "mainwindow.h"
#include "application.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	Application app;
 //   loginDlg.setWindowFlags(loginDlg.windowFlags() | Qt::WindowStaysOnTopHint);
	w.show();

    //信号与槽之间进行关联
	QObject::connect(&w, SIGNAL(showApplication(quint32)), &app, SLOT(receiveMainWindow(quint32)));

    return a.exec();
}
