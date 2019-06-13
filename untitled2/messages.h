#ifndef MESSAGES_H
#define MESSAGES_H
#include <QString>
#include <QDateTime>
#include <user.h>

class Messages{
public:

    Messages(QString user_name,QString content,QString time){
        this->user_name = user_name;
        this->content = content;
        this->time = time;
    }

    QString getUserName(){
        return this->user_name;
    }

    QString getContent(){
        return this->content;
    }

    QString getTime(){
        return this->time;
    }

private:
    QString user_name;
    QString content;
    QString time;
};

bool createMessageRecord(User user,QString content);

QList<Messages> syncMessageRecords(User user);

#endif // MESSAGES_H
