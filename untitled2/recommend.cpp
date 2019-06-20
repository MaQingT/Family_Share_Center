#include <recommend.h>

QList<Music> recommendMusic(User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","recommendMusic");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    QList<Music> recommend;
    if(db.open()){

        qDebug()<<"recommend music function connect";
        QString S = QString("SELECT music.music_id,music.music_name,music.style FROM `%1`.music where music.music_id not in( select music.music_id from `%1`.music,`%1`.collect_music where music.music_name = collect_music.music_name and collect_music.user_name = '%2' ) ORDER BY RAND() LIMIT 5;")
                .arg(familyid)
                .arg(user.getName());
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                Music New(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString());
                recommend<<New;
            }
            QString name;
            qDebug()<<"recommend music record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync music record function disconnect";
            return recommend;
        }
        else {
            QString name;
            qDebug()<<"recommend video record success";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync video record function disconnect";
            return recommend;
        }
    }
    else {
        qDebug()<<"recommend music function connect fail";
        return recommend;
    }
}
