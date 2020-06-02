#include "mysql.h"

#include <QCryptographicHash>

//初始化构造函数
MySQL::MySQL()
{
	db = QSqlDatabase::addDatabase("QMYSQL");       //加载MySQL驱动
    db.setHostName("localhost");                    //设置主机地址
    db.setPort(3306);                               //设置端口号
    db.setDatabaseName("qt_software");              //设置数据库名称
    db.setUserName("root");                         //设置访问账户
    db.setPassword("admin");                        //设置访问密码
    if(!db.open()) {
        qDebug() << "open db error:" << db.lastError();
        exit(-1);
    }
    db.close();

    isSQL = true;
}

//析构函数
MySQL::~MySQL()
{
   // delete query;
}

//select语句
QSqlRecord* MySQL::runOne(const QString &content)
{
    //输出sql语句
    if(isSQL)
        qDebug() << "sql:" << content;

    //打开数据库
    if(!db.open()) {
        qDebug() << "open db error:" << db.lastError();
        exit(EOF);
    }

    //执行sql语句
    QSqlQuery query(db);
    query.exec(content);
    if(query.isValid())
    {
        qDebug() << "Invalid record: " << query.lastError();
        db.close();
        exit(EOF);
    }

    //获取查询结果
    QSqlRecord* rec = nullptr;
    if(!query.first())
    {
        qDebug() << "no result!";
        db.close();
        return nullptr;
    }
    else
    {
        rec = new QSqlRecord(query.record());
        db.close();
        return rec;
    }
}

//insert into语句和update语句
void MySQL::runNo(const QString &content)
{
    //输出sql语句
    if(isSQL)
        qDebug() << "sql:" << content;

    //打开数据库
    if(!db.open()) {
        qDebug() << "open db error:" << db.lastError();
        exit(EOF);
    }

    //执行sql语句
    QSqlQuery query(db);
    query.exec(content);
    if(query.isValid())
    {
        qDebug() << "Invalid record: " << query.lastError();
        db.close();
        exit(EOF);
    }
}

