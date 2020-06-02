#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>

#include <QListWidget>
#include <QListWidgetItem>
#include <QProcess>

namespace Ui {
class Application;
}

class Application : public QWidget
{
	Q_OBJECT

public:
	explicit Application(QWidget *parent = nullptr);
	~Application();

	void init();

private slots:
	void receiveMainWindow(quint32 id);
	void on_applicationListWidget_clicked();

private:
	Ui::Application *ui;

	quint32 uid;

	QListWidgetItem *snakeItem;
	QListWidgetItem *GAELItem;
	QListWidgetItem *KIWItem;
};

#endif // APPLICATION_H
