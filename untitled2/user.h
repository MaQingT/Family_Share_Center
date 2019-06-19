#ifndef USER_H
#define USER_H
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>


class User{
public:
    //构造函数
    User(int id,QString name,QString psw,int family_id,int special)
    {
        this->id = id;
        this->psw = psw;
        this->name = name;
        this->special = special;
        this->family_id = family_id;
    }

    //返回一个空的User对象
    static User getNULL(){
        User usernull(0,"","",0,0);
        return usernull;
    }
    //static bool judge(User a,User b);

    //get方法
    int getId(){
        return this->id;
    }
    QString getName(){
        return this->name;
    }
    QString getPsw(){
        return this->psw;
    }
    int getFamilyId(){
        return this->family_id;
    }
    int getSpecial(){
        return this->special;
    }

private:
    int id;
    QString name;
    QString psw;
    int family_id;
    int special;
};


bool judge(User a,User b);
#endif // USER_H
