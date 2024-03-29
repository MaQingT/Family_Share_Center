#include <communication.h>

bool sendPrivateMessages(User me,QString he,QString content){
    QString familyId = QString::number(me.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","sendPrivateMessages");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("Communication");      //连接数据库名，与设置一致
    db.setUserName("client");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"send private message function connect";
        QDateTime t;
        QString currentTime = t.currentDateTime().toString("yyyyMMddhhmmss");
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `Communication`.`content` (`sender_name`, `reciever_name`, `conten`, `time`) VALUES ('%1', '%2', '%3', '%4');")
                .arg(me.getName())
                .arg(he)
                .arg(content)
                .arg(currentTime);
        if(query.exec(I)){
            qDebug()<<"message sent";
            QString name;{
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            addrecord(me,he,currentTime);
            return true;
        }
        else {
            qDebug()<<"message not sent";
            QString name;{
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
            return false;
        }
    }
    else {
        qDebug()<<"send private message function connection fail";
        return false;
    }

}

void addrecord(User me,QString he,QString currentTime){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","sendPrivateMessages");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("Login");      //连接数据库名，与设置一致
    db.setUserName("Communication");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致

    if(db.open()){
        QSqlQuery query(db);
        qDebug()<<"add record function connect";
        int number;
        query.exec(QString("select sentNumber from communication_record where senderName = '%1' and recieverName = '%2';").arg(me.getName()).arg(he));
        if(query.next()){
            number = query.value(0).toInt();
            QString U = QString("UPDATE `Communication`.`comunication_record` SET `sentNumber` = '%1', `lastTime` = '%2' WHERE (`senderName` = '%2' and `recieveName` = '%3');")
                    .arg(QString::number(number++))
                    .arg(currentTime)
                    .arg(me.getName())
                    .arg(he);
            query.exec(U);
        }
        else {
            QString I = QString("INSERT INTO `Communication`.`comunication_record` (`senderName`, `recieverName`, `sentNumber`, `lastTime`) VALUES ('%1', '%2', '1', '%3');").arg(me.getName()).arg(he).arg(currentTime);
            query.exec(I);
            QString name;{
                name = QSqlDatabase::database().connectionName();
            }
            QSqlDatabase::removeDatabase(name);
        }

    }
}


