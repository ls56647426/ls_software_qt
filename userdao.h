#ifndef USERDAO_H
#define USERDAO_H

#include "mysql.h"
#include "user.h"
#include "specification.h"

class UserDao
{
public:
    UserDao();

    User* findOne(const quint32 *id);
    User* findOne(const Specification *spec);

    void save(const User *user);

    void del(const quint32 *id);

    //    QList<User> findAll();



private:
    MySQL mysql;
};

#endif // USERDAO_H
