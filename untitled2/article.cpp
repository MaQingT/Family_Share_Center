#include <article.h>

bool addArticleRecord(Article article,User user){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",QString::number(user.getFamilyId()));
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("article_record");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    if(db.open()){
        qDebug()<<"add article record function connect";
        QDateTime t;
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`article_record` (`article_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(article.getId())).arg(QString::number(user.getId())).arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
        if(query.exec()){
            qDebug()<<"add record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add article record function disconnect";
            return true;
        }
        else{
            qDebug()<<"add record fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"article add record function disconnect";
            return false;
        }
    }
    else{
        qDebug()<<"database connect fail";
        return false;
    }
}

bool addNewArticle(QString articleName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("article");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;

    if(db.open()){
        qDebug()<<"add article record function connect";
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`article` (`article_name`) VALUES ('%2');").arg(familyid).arg(articleName);
        if(query.exec(I)){
            qDebug()<<"add article success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add article record function disconnect";
            return true;
        }
        else {
            qDebug()<<"add article fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add article record function disconnect";
            return false;
        }
    }else {
        qDebug()<<"database connect fail";
        return false;
    }
}

bool ifNewArticle(QString articleName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("article_record");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;

    if(db.open()){
        qDebug()<<"if article function connect";
        QString S = QString("select * from '%1'.article where user_name = '%2' and artist = '%3'").arg(familyid).arg(articleName);
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            qDebug()<<"already have article";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if article function disconnect";
            return true;
        }
        else {
            qDebug()<<"dont have article";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add article record function disconnect";
            qDebug()<<"adding article now";
            if(addNewArticle(articleName,user)) return true;
            else return false;
        }
    }
    else {
        qDebug()<<"if article function fail";
        return false;
    }
}
