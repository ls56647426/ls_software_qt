#ifndef SPECIFICATION_H
#define SPECIFICATION_H

#include <QString>
#include <QVariant>

class Specification
{
public:
    Specification();

    QString isNull(QString key);
    QString isNotNull(QString key);

    QString equal(QString key, QVariant value);
    QString notEqual(QString key, QVariant value);
    QString like(QString key, QString value);

    QString Or(QString a, QString b);
    QString Or(QList<QString> list);

    QString And(QString a, QString b);
    QString And(QList<QString> list);

	QString tranString(const QString &value);

    QString getSqlWhere() const;
    void setSqlWhere(const QString &value);

private:
    QString sqlWhere;
};

#endif // SPECIFICATION_H
