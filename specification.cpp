#include "specification.h"

Specification::Specification()
{

}

QString Specification::isNull(QString key)
{
    return QString("%1 is null").arg(key);
}

QString Specification::isNotNull(QString key)
{
    return QString("%1 is not null").arg(key);
}

QString Specification::equal(QString key, QVariant value)
{
    return QString("%1 = %2").arg(key).arg(value.toString());
}

QString Specification::notEqual(QString key, QVariant value)
{
    return QString("%1 <> %2").arg(key).arg(value.toString());
}

QString Specification::like(QString key, QString value)
{
    return QString("%1 like %2").arg(key).arg(value);
}

QString Specification::Or(QString a, QString b)
{
    return QString("(%1) or (%2)").arg(a).arg(b);
}

QString Specification::Or(QList<QString> list)
{
    QString res;

    for(QList<QString>::iterator it = list.begin(); it != list.end(); it++)
    {
        if(it != list.begin())
            res += " or ";
        res += *it;
    }

    return res;
}

QString Specification::And(QString a, QString b)
{
    return QString("(%1) and (%2)").arg(a).arg(b);
}

QString Specification::And(QList<QString> list)
{
    QString res;

    for(QList<QString>::iterator it = list.begin(); it != list.end(); it++)
    {
        if(it != list.begin())
            res += " and ";
        res += *it;
    }

	return res;
}

QString Specification::tranString(const QString &value)
{
	return "'" + value + "'";
}

QString Specification::getSqlWhere() const
{
    return sqlWhere;
}

void Specification::setSqlWhere(const QString &value)
{
    sqlWhere = value;
}
