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
    User user(2134,"asdfas","fasd",16,0);
    QList<MusicRecord> list = syncMusicRecord(user,0,10,0);
    while(!list.isEmpty()){
        MusicRecord New = list.takeFirst();
        std::cout<<New.getMusicName().toStdString()<<" "<<New.getUserName().toStdString()<<" "<<New.getTime().toString("yyyy-MM-dd hh:mm:ss").toStdString()<<std::endl;
    }
    return a.exec();
}
