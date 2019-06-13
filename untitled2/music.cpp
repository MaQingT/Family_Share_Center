#include <music.h>

int addNewMusic(QString musicName,QString artist,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewMusic");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"add new music function connect";
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`music` (`music_name`, `artist`) VALUES ('%2', '%3');").arg(familyid).arg(musicName).arg(artist);
        qDebug()<<I;
        if(query.exec(I)){
            QString S=QString("select music_id from `%1`.`music` where music_name = '%2';").arg(familyid).arg(musicName);
            query.exec(S);
            query.next();
            int id = query.value(0).toInt();
            qDebug()<<"add music success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add new music function disconnect";
            return id;
        }
        else {
            qDebug()<<"add music fail";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add new music function disconnect";
            return false;
        }
    }else {
        qDebug()<<"database connect fail";
        return false;
    }
}

bool addMusicRecord(Music music,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addMusicRecord");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    if(db.open()){
        qDebug()<<"add music record function connect";
        QDateTime t;
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`music_record` (`music_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(music.getId())).arg(QString::number(user.getId())).arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
        qDebug()<<I;
        if(query.exec(I)){
            qDebug()<<"add record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add music record function disconnect";
            return true;
        }
        else{
            qDebug()<<"add record fail";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"music add record function disconnect";
            return false;
        }
    }
    else{
        qDebug()<<"database connect fail";
        return false;
    }
}

int ifNewMusic(QString musicName,QString artist,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","ifNewMusic");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"if music function connect";
        QString S = QString("select * from `%1`.music where music_name = '%2' and artist = '%3';").arg(familyid).arg(musicName).arg(artist);
        qDebug()<<S;
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            int id = query.value(0).toInt();
            qDebug()<<"already have music";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if music function disconnect";
            return id;
        }
        else {
            qDebug()<<"dont have music";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if new music function disconnect";
            return false;
        }
    }
    else {
        qDebug()<<"if music function fail";
        return false;
    }
}

QList<MusicRecord> syncMusicRecord(User user,int Tspecial){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","syncMusicRecord");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致
    QString name;
    QList<MusicRecord> records;
    if(db.open()){
        qDebug()<<"sync music record function connect";
        QString S = QString("SELECT music.music_name,members.user_name,music_record.time FROM `%1`.music,`%1`.music_record,`%1`.members where members.special = '%4' and music_record.music_id = music.music_id and members.user_id = music_record.user_id order by time desc;")
                .arg(familyId)
                .arg(QString::number(Tspecial));
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                MusicRecord New(query.value(1).toString(),query.value(0).toString(),query.value(2).toDateTime());
                records<<New;
            }
            qDebug()<<"sync music record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return records;
        }
        else {
            qDebug()<<"sync music record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return records;
        }

    }
    else {
        qDebug()<<"connect fail";
        return records;
    }
}
