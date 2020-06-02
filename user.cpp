#include "user.h"

User::User()
{
    id = 0;
    info.insert("tablename", "user");
    info.insert("id", id);
	info.insert("username", "'" + username + "'");
	info.insert("password", "'" + password + "'");
	info.insert("mobile", "'" + mobile + "'");
}

int User::getId() const
{
    return id;
}

void User::setId(int value)
{
    info["id"] = id = value;
}

QString User::getUsername() const
{
    return username;
}

void User::setUsername(const QString &value)
{
	username = value;
	info["username"] = "'" + value + "'";
}

QString User::getPassword() const
{
    return password;
}

void User::setPassword(const QString &value)
{
	password = value;
	info["password"] = "'" + value + "'";
}

QString User::getMobile() const
{
    return mobile;
}

void User::setMobile(const QString &value)
{
	mobile = value;
	info["mobile"] = "'" + value + "'";
}

QString User::toString() const
{
    return QString("User:{id = %1, username = %2, password = %3, mobile = %4}").arg(id).arg(username).arg(password).arg(
                mobile);
}
