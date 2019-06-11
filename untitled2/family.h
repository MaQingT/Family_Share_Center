#ifndef FAMILY_H
#define FAMILY_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QString>
#include <user.h>

class family{
public:
    family(int id,QString name,QString password){
        this->id = id;
        this->name = name;
        this->password = password;
    }
    int getId(){
        return this->id;
    }
    QString getName(){
        return this->name;
    }
    QString getPsw(){
        return this->password;
    }
private:
    int id;
    QString name;
    QString password;
};

//添加用户函数，在创建用户后直接向该家庭的members表中写入数据
bool AddMember(User user);

//创建一个家庭数据库，并创建该数据库中的各项数据表
int createFamily(QString name,QString password);

#endif // FAMILY_H
