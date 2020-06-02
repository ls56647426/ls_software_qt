#ifndef MYSQL_H
#define MYSQL_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QCoreApplication>

#include <QDebug>

class MySQL
{
public:
    MySQL();
    ~MySQL();

    QSqlRecord* runOne(const QString &content);

    void runNo(const QString &content);

private:
    QSqlDatabase db;                        //数据库配置及打开
    bool isSQL;                             //是否输出sql语句
};

#endif // MYSQL_H
