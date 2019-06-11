#include <QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <iostream>
#include <QString>
#include <User.h>
#include <connection.h>
#include <QDateTime>
#include <music.h>

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    User user(1035,"test2","test2",28,0);
    int id =  ifNewMusic("wert","fasdf",user);
    qDebug()<<id;
    if(!id){
        id = addNewMusic("wert","fasdf",user);
    }
    Music music(id,"wert","fasdf","asdfas");
    addMusicRecord(music,user);
    return a.exec();
}
