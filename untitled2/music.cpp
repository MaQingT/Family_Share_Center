#include <music.h>

int addNewMusic(QString musicName,User user){
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
        QString I = QString("INSERT INTO `%1`.`music` (`music_name`) VALUES ('%2');").arg(familyid).arg(musicName);
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
        QString I = QString("INSERT INTO `%1`.`music_record` (`music_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');")
                .arg(QString::number(user.getFamilyId()))
                .arg(QString::number(music.getId()))
                .arg(QString::number(user.getId()))
                .arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
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

int ifNewMusic(QString musicName, User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","ifNewMusic");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"if music function connect";
        QString S = QString("select * from `%1`.music where music_name = '%2';").arg(familyid).arg(musicName);
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

QList<Music> syncMusicCollection(User user){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","syncMusicCollection");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    QList<Music> collection;
    if(db.open()){
        qDebug()<<"sync music collection function connect";
        QString S = QString("SELECT music.music_id,music.music_name,music.style FROM `%1`.collect_music,`%1`.music where collect_music.user_name = '%2' and  music.music_name = collect_music.music_name;").arg(familyId).arg(user.getName());
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                Music New(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString());
                collection<<New;
            }
            qDebug()<<"sync music collection success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return collection;
        }
        else {
            qDebug()<<"sync music record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return collection;
        }

    }
    else {
        qDebug()<<"sync music collection function connect fail";
        return collection;
    }
}

bool addNewMusicCollect(User user,Music music){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewMusicCollect");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");

    if(db.open()){
        qDebug()<<"add new music collection function connect";
        QString S = QString("SELECT * FROM `1001`.collect_music where user_name = '123' and music_name = 'asdfasdf';")
                .arg(familyId)
                .arg(user.getName())
                .arg(music.getName());
        QString I = QString("INSERT INTO `%1`.`collect_music` (`user_name`, `music_name`) VALUES ('%2', '%3');")
                .arg(familyId)
                .arg(user.getName())
                .arg(music.getName());
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
        qDebug()<<"add new music collection function connect fail";
        return false;
    }
}

bool deleteMusicCollect(User user,Music music){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewMusicCollect");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");

    if(db.open()){
        qDebug()<<"delete music collection function connect";
        QString D = QString("delete from `%1`.collect_music where user_name = '%2' and music_name = '%3';")
                .arg(familyId)
                .arg(user.getName())
                .arg(music.getName());
        QSqlQuery query(db);
        if(query.exec(D)){
            qDebug()<<"delete music collection success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"delete music collection function disconnect";
            return true;
        }
        else {
            qDebug()<<"delete music collection fail";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"delete music collection function disconnect";
            return false;
        }
    }
    else {
        qDebug()<<"delete music collection function connect fail";
        return false;
    }
}
