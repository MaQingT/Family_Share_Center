#include <video.h>

bool addVideoRecord(Video video,User user){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",QString::number(user.getFamilyId()));
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("video_record");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    if(db.open()){
        qDebug()<<"add video record function connect";
        QDateTime t;
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`video_record` (`video_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(video.getId())).arg(QString::number(user.getId())).arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
        if(query.exec()){
            qDebug()<<"add record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            return true;
        }
        else{
            qDebug()<<"add record fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"video add record function disconnect";
            return false;
        }
    }
    else{
        qDebug()<<"database connect fail";
        return false;
    }
}

bool addNewVideo(QString videoName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("video");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;

    if(db.open()){
        qDebug()<<"add video record function connect";
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`video` (`video_name`) VALUES ('%2');").arg(familyid).arg(videoName);
        if(query.exec(I)){
            qDebug()<<"add video success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            return true;
        }
        else {
            qDebug()<<"add video fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            return false;
        }
    }else {
        qDebug()<<"database connect fail";
        return false;
    }
}

bool ifNewVideo(QString videoName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("video_record");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;

    if(db.open()){
        qDebug()<<"if video function connect";
        QString S = QString("select * from '%1'.video where user_name = '%2' and artist = '%3'").arg(familyid).arg(videoName);
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            qDebug()<<"already have video";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if video function disconnect";
            return true;
        }
        else {
            qDebug()<<"dont have video";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            qDebug()<<"adding video now";
            if(addNewVideo(videoName,user)) return true;
            else return false;
        }
    }
    else {
        qDebug()<<"if video function fail";
        return false;
    }
}

QList<VideoRecord> syncVideoRecord(User user,int start,int numbers,int Tspecial){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyId);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    QList<VideoRecord> records;
    if(db.open()){
        qDebug()<<"sync video record function connect";
        QString S = QString("SELECT video.video_name,members.user_name,video_record.time FROM `%1`.video,`%1`.video_record,`%1`.members where members.special = '%4' and video_record.video_id = video.video_id and members.user_id = video_record.user_id order by time desc limit %2,%3;")
                .arg(familyId)
                .arg(QString::number(start))
                .arg(QString::number(numbers))
                .arg(QString::number(Tspecial));
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                MusicRecord New(query.value(1).toString(),query.value(0).toString(),query.value(2).toDateTime());
                records<<New;
            }
            qDebug()<<"sync video record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return records;
        }
        else {
            qDebug()<<"sync video record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync video record function disconnect";
            return records;
        }

    }
    else {
        qDebug()<<"connect fail";
        return records;
    }
}
