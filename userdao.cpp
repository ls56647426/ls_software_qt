#include "userdao.h"

UserDao::UserDao()
{

}

//通过id查找一个用户数据
User* UserDao::findOne(const quint32 *id)
{
    //组合sql语句
    QString content = QString("select * from user where id = %1").arg(*id);

    //获得查询结果
    QSqlRecord* rec = mysql.runOne(content);

    //判空
    if(rec == nullptr)
        return nullptr;

    //将查询的结果存入User类的对象中
    User* user = new User();
    user->setId(rec->value("id").toUInt());
    user->setUsername(rec->value("username").toString());
    user->setPassword(rec->value("password").toString());
    user->setMobile(rec->value("mobile").toString());

    return user;
}

User* UserDao::findOne(const Specification *spec)
{
    //构建sql语句
    QString content = QString("select * from user where %1").arg(spec->getSqlWhere());

    //获得查询结果
    QSqlRecord* rec = mysql.runOne(content);

    //判空
    if(rec == nullptr)
        return nullptr;

    //将查询的结果存入User类的对象中
    User* user = new User;
    user->setId(rec->value("id").toUInt());
    user->setUsername(rec->value("username").toString());
    user->setPassword(rec->value("password").toString());
    user->setMobile(rec->value("mobile").toString());

    return user;
}

//保存一个用户数据
void UserDao::save(const User *user)
{
    //先判断该用户数据是否存在，以主键id来判断
	QString content = QString("select * from user where id = %1").arg(user->info["id"].toUInt());
    QSqlRecord* rec = mysql.runOne(content);

    content.clear();
    if(rec == nullptr)
    {   //如果不存在，则insert
		content = QString("insert into user values(null, %1, %2, %3)").arg(user->info["username"].toString()).arg(
					user->info["password"].toString()).arg(user->info["mobile"].toString());
        mysql.runNo(content);
		//同时新建kiw数据
		content = QString("insert into kiw_user values(null, 0, 0, 0, 0, 0)");
		mysql.runNo(content);
    }
    else
    {   //如果存在，则update
        content = QString("update user set username = %1, password = %2, mobile = %3 where id = %4").arg(
					user->info["username"].toString()).arg(user->info["password"].toString()).arg(
					user->info["mobile"].toString()).arg(user->info["id"].toUInt());
        mysql.runNo(content);
    }
}

//通过id删除一个用户数据
void UserDao::del(const quint32 *id)
{
    //先判断该用户数据是否存在，以主键id来判断
    QString content = QString("select * from user where id = %1").arg(*id);
    QSqlRecord* rec = mysql.runOne(content);

    content.clear();
    if(rec == nullptr)
    {   //判空
        qDebug() << "无此用户";
        return;
    }

    content = QString("delete from user where id = %1").arg(*id);
    mysql.runNo(content);
}


