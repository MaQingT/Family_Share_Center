#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>
#include <user.h>
#include <family.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QtDebug>
#include <QtWidgets/QMessageBox>

//函数声明
//注册函数，其中包含两部分，分别为用户注册部分与家庭登录、注册部分
User Registe(QString User_name,QString userpassword,QString Family_name,int special,QString Family_password);

//用户登陆函数
User User_login(QString User_name,QString password);

//用户注册函数，该函数返回当前用户注册后生成的User_id
int User_Registe(QString name,QString password,int Family_id,int special);

//家庭加入函数，该函数对传入的两个参数进行识别
//若该家庭存在，则调用加入家庭函数
//若家庭不存在，则向用户请求是否创建家庭
//若创建家庭则调用创建家庭函数
//若不创建则要求用户重新输入内容
int Family_login(QString name,QString password);

#endif // CONNECTION_H
