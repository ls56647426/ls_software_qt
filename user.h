#ifndef USER_H
#define USER_H

#include <QString>
#include <QVariant>

class User
{
public:
	QMap<QString, QVariant> info;

    User();

    int getId() const;
    void setId(int value);

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

    QString getMobile() const;
    void setMobile(const QString &value);

    QString toString() const;

private:
	quint32 id;
	QString username;
	QString password;
	QString mobile;
};

#endif // USER_H
