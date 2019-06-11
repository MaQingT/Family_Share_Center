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
#include <video.h>
#include <article.h>

int main(int argc,char *argv[])
{
    QApplication a(argc,argv);
    User user(1036,"test3","test3",29,0);
    int id =  ifNewArticle("wert",user);
    qDebug()<<id;
    if(!id){
        id = addNewArticle("wert",user);
    }
    Article article(id,"wert","fasdf");
    addArticleRecord(article,user);
    return a.exec();
}
