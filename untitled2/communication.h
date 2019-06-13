#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <user.h>

class Communication{
public:

    Communication(QString sender_name,QString recieve_name,QString content,QString time){
        this->sender_name = sender_name;
        this->recieve_name = recieve_name;
        this->content = content;
        this->time = time;
    }

    QString getSName(){
        return this->sender_name;
    }

    QString getRName(){
        return this->recieve_name;
    }

    QString getContent(){
        return this->content;
    }
    QString getTime(){
        return this->time;
    }

private:
    QString sender_name;
    QString recieve_name;
    QString content;
    QString time;
};

#endif // COMMUNICATION_H
