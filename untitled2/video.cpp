#include <video.h>

bool addVideoRecord(Video video,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addVideoRecord");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"add video record function connect";
        QDateTime t;
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`video_record` (`video_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(video.getId())).arg(QString::number(user.getId())).arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
        if(query.exec(I)){
            qDebug()<<"add record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            return true;
        }
        else{
            qDebug()<<"add record fail";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"video add record function disconnect";
            return false;
        }
    }
    else{
        qDebug()<<"add video record function connect fail";
        return false;
    }
}

int addNewVideo(QString videoName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewVideo");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致


    if(db.open()){
        qDebug()<<"add video record function connect";
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`video` (`video_name`) VALUES ('%2');").arg(familyid).arg(videoName);
        if(query.exec(I)){
            QString S = QString("select video_id from `%1`.`video` where video_name = '%2';").arg(familyid).arg(videoName);
            query.exec(S);
            query.next();
            int id = query.value(0).toInt();
            qDebug()<<"add video success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            return id;
        }
        else {
            qDebug()<<"add video fail";
            QString name;
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

int ifNewVideo(QString videoName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","ifNewVideo");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"if new video function connect";
        QString S = QString("select * from `%1`.`video` where video_name = '%2';").arg(familyid).arg(videoName);
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            qDebug()<<"already have video";
            int id = query.value(0).toInt();
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if new video function disconnect";
            return id;
        }
        else {
            qDebug()<<"dont have video";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add video record function disconnect";
            qDebug()<<"adding video now";
            return false;
        }
    }
    else {
        qDebug()<<"if new video function fail";
        return false;
    }
}

QList<VideoRecord> syncVideoRecord(User user, int Tspecial){
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
        QString S = QString("SELECT video.video_name,members.user_name,video_record.time FROM `%1`.video,`%1`.video_record,`%1`.members where members.special = '%4' and video_record.video_id = video.video_id and members.user_id = video_record.user_id order by time desc;")
                .arg(familyId)
                .arg(QString::number(Tspecial));
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                VideoRecord New(query.value(1).toString(),query.value(0).toString(),query.value(2).toDateTime());
                records<<New;
            }
            qDebug()<<"sync video record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync video record function disconnect";
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


QList<Video> syncVideoCollection(User user){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","syncVideoCollection");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    QList<Video> collection;
    if(db.open()){
        qDebug()<<"sync video collection function connect";
        QString S = QString("SELECT video.video_id,video.video_name FROM `%1`.collect_video,`%1`.video where collect_video.user_name = '%2' and  video.video_name = collect_video.video_name;").arg(familyId).arg(user.getName());
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                Video New(query.value(0).toInt(),query.value(1).toString());
                collection<<New;
            }
            qDebug()<<"sync video collection success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync video record function disconnect";
            return collection;
        }
        else {
            qDebug()<<"sync video record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync video record function disconnect";
            return collection;
        }

    }
    else {
        qDebug()<<"sync video collection function connect fail";
        return collection;
    }
}

bool addNewVideoCollect(User user,Video video){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewVideoCollect");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");

    if(db.open()){
        qDebug()<<"add new video collection function connect";
        QString S = QString("SELECT * FROM `1001`.collect_video where user_name = '123' and video_name = 'asdfasdf';")
                .arg(familyId)
                .arg(user.getName())
                .arg(video.getName());
        QString I = QString("INSERT INTO `%1`.`collect_video` (`user_name`, `video_name`) VALUES ('%2', '%3');")
                .arg(familyId)
                .arg(user.getName())
                .arg(video.getName());
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            QMessageBox::information(NULL,"添加失败","重复添加",QMessageBox::Yes);
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            return false;
        }
        else if(query.exec(I)){
            QMessageBox::information(NULL,"添加成功","添加成功！！！",QMessageBox::Yes);
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            return true;
        }
        else {
            QMessageBox::information(NULL,"添加失败","添加失败！！！",QMessageBox::Yes);
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            return false;
        }
    }
    else {
        qDebug()<<"add new video collection function connect fail";
        return false;
    }
}

bool deleteVideoCollect(User user,Video video){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewVideoCollect");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");

    if(db.open()){
        qDebug()<<"delete video collection function connect";
        QString D = QString("delete from `%1`.collect_video where user_name = '%2' and video_name = '%3';")
                .arg(familyId)
                .arg(user.getName())
                .arg(video.getName());
        QSqlQuery query(db);
        if(query.exec(D)){
            qDebug()<<"delete video collection success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"delete video collection function disconnect";
            return true;
        }
        else {
            qDebug()<<"delete video collection fail";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"delete video collection function disconnect";
            return false;
        }
    }
    else {
        qDebug()<<"delete video collection function connect fail";
        return false;
    }
}
