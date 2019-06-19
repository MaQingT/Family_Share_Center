#include <messages.h>

bool createMessageRecord(User user,QString content){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","createMessageRecord");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);      //连接数据库名，与设置一致
    db.setUserName("client");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"create message record function connect";
        QDateTime t;
        QString I = QString("INSERT INTO `%1`.`messages` (`user_name`, `content`, `time`) VALUES ('%2', '%3', '%4');").arg(familyId).arg(user.getName()).arg(content).arg(t.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        QSqlQuery query(db);
        if(query.exec(I)){
            qDebug()<<"add message success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add message function disconnect";
            return true;
        }
        else {
            qDebug()<<"add message fail";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add message function disconnect";
            return false;
        }
    }
    else {
        qDebug()<<"connect fail";
        return false;
    }
}

QList<Messages> syncMessageRecords(User user){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyId);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    QList<Messages> records;
    if(db.open()){
        qDebug()<<"sync messages function connect";
        QString S = QString("select * from `%1`.messages;").arg(familyId);
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                Messages New(query.value(1).toString(),query.value(2).toString(),query.value(3).toString());
                records<<New;
            }
            qDebug()<<"sync messages success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync messages function disconnect";
            return records;
        }
        else {
            qDebug()<<"sync messages success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync messages function disconnect";
            return records;
        }

    }
    else {
        qDebug()<<"connect fail";
        return records;
    }
}
