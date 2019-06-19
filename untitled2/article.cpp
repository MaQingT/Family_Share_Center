#include <article.h>

bool addArticleRecord(Article article,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addArticleRecord");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"add article record function connect";
        QDateTime t;
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`article_record` (`article_id`, `user_id`, `time`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(article.getId())).arg(QString::number(user.getId())).arg(t.currentDateTime().toString("yyyyMMddhhmmss"));
        if(query.exec(I)){
            qDebug()<<"add record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add article record function disconnect";
            return true;
        }
        else{
            qDebug()<<"add record fail";
            QString name;
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

int addNewArticle(QString articleName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewArticle");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"add article record function connect";
        QSqlQuery query(db);
        QString I = QString("INSERT INTO `%1`.`article` (`article_name`) VALUES ('%2');").arg(familyid).arg(articleName);
        if(query.exec(I)){
            QString S = QString("select article_id from `%1`.`article` where article_name = '%2';").arg(familyid).arg(articleName);
            query.exec(S);
            query.next();
            int id = query.value(0).toInt();
            qDebug()<<"add article success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"add article record function disconnect";
            return id;
        }
        else {
            qDebug()<<"add article fail";
            QString name;
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

int ifNewArticle(QString articleName,User user){
    QString familyid = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyid);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyid);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致


    if(db.open()){
        qDebug()<<"if new article function connect";
        QString S = QString("select * from '%1'.article where user_name = '%2' and artist = '%3'").arg(familyid).arg(articleName);
        QSqlQuery query(db);
        if(query.exec(S) && query.next()){
            qDebug()<<"already have article";
            int id = query.value(0).toInt();
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if new article function disconnect";
            return id;
        }
        else {
            qDebug()<<"dont have article";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"if new article function disconnect";
            return false;
        }
    }
    else {
        qDebug()<<"if article function fail";
        return false;
    }
}

QList<ArticleRecord> syncArticleRecord(User user, int Tspecial){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL",familyId);
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    QList<ArticleRecord> records;
    if(db.open()){
        qDebug()<<"sync article record function connect";
        QString S = QString("SELECT article.article_name , article.URL , members.user_name , article_record.`time` FROM `1001`.article_record,`1001`.members,`1001`.article where article.article_id = article_record.article_id and  members.user_id = article_record.user_id order by time desc;")
                .arg(familyId)
                .arg(QString::number(Tspecial));
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                ArticleRecord New(query.value(1).toString(),query.value(0).toString(),query.value(2).toDateTime(),query.value(3).toString());
                records<<New;
            }
            qDebug()<<"sync article record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync article record function disconnect";
            return records;
        }
        else {
            qDebug()<<"sync article record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync article record function disconnect";
            return records;
        }

    }
    else {
        qDebug()<<"connect fail";
        return records;
    }
}

QList<Article> syncArticleCollection(User user){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","syncArticleCollection");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    QList<Article> collection;
    if(db.open()){
        qDebug()<<"sync article collection function connect";
        QString S = QString("SELECT article.article_id,article.article_name,article.article_URL FROM `%1`.collect_article,`%1`.article where collect_article.user_name = '%2' and  article.article_name = collect_article.article_name;").arg(familyId).arg(user.getName());
        QSqlQuery query(db);
        if(query.exec(S)){
            while(query.next()){
                Article New(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString());
                collection<<New;
            }
            qDebug()<<"sync article collection success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync article record function disconnect";
            return collection;
        }
        else {
            qDebug()<<"sync article record success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"sync article record function disconnect";
            return collection;
        }

    }
    else {
        qDebug()<<"sync article collection function connect fail";
        return collection;
    }
}

bool addNewArticleCollect(User user,Article article){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewArticleCollect");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");

    if(db.open()){
        qDebug()<<"add new article collection function connect";
        QString S = QString("SELECT * FROM `1001`.collect_article where user_name = '123' and article_name = 'asdfasdf';")
                .arg(familyId)
                .arg(user.getName())
                .arg(article.getName());
        QString I = QString("INSERT INTO `%1`.`collect_article` (`user_name`, `article_name`) VALUES ('%2', '%3');")
                .arg(familyId)
                .arg(user.getName())
                .arg(article.getName());
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
        qDebug()<<"add new article collection function connect fail";
        return false;
    }
}

bool deleteArticleCollect(User user,Article article){
    QString familyId = QString::number(user.getFamilyId());
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","addNewArticleCollect");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName(familyId);            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");

    if(db.open()){
        qDebug()<<"delete article collection function connect";
        QString D = QString("delete from `%1`.collect_article where user_name = '%2' and article_name = '%3';")
                .arg(familyId)
                .arg(user.getName())
                .arg(article.getName());
        QSqlQuery query(db);
        if(query.exec(D)){
            qDebug()<<"delete article collection success";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"delete article collection function disconnect";
            return true;
        }
        else {
            qDebug()<<"delete article collection fail";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"delete article collection function disconnect";
            return false;
        }
    }
    else {
        qDebug()<<"delete article collection function connect fail";
        return false;
    }
}

