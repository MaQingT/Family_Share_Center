#include <family.h>

int createFamily(QString name,QString password){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","createFamily");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("Login");      //连接数据库名，与设置一致
    db.setUserName("client");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"create family function connect";
        QSqlQuery query(db);
        //向数据库中添加新家庭的信息
        QString InsertFamilyInfo = QString("INSERT INTO `Login`.`family_info` (`family_name`, `family_password`) VALUES ('%1', '%2');").arg(name).arg(password);
        if(query.exec(InsertFamilyInfo)) qDebug()<<"Insert Family Info";

        //获取该家庭在数库中的id
        QString SearchId = QString("SELECT family_id FROM Login.family_info WHERE family_name = '%1';").arg(name);
        QString family_id;
        if(query.exec(SearchId)){
            query.next();
            family_id = query.value(0).toString();
            qDebug()<<"Get family id "<<family_id;
        }
        //创建以家庭id为名称的数据库
        QString CreateSchema = QString("CREATE SCHEMA `%1` ;").arg(family_id);
        if(query.exec(CreateSchema)) qDebug()<<"Create Schema";

        //创建家庭成员表
        QString CreateMemberTable = QString("CREATE TABLE `%1`.`members` (  `user_id` INT NOT NULL, `user_name` NVARCHAR(45) NOT NULL, `special` INT NOT NULL,PRIMARY KEY (`user_id`));").arg(family_id);
        if(query.exec(CreateMemberTable)) qDebug()<<"Create Member Table";

        //创建音乐表
        QString CreateMusicTable = QString("CREATE TABLE `%1`.`music` (`music_id` INT NOT NULL AUTO_INCREMENT,`music_name` NVARCHAR(45) NOT NULL,`style` NVARCHAR(45) NULL,PRIMARY KEY (`music_id`),UNIQUE INDEX `music_id_UNIQUE` (`music_id` ASC));").arg(family_id);
        if(query.exec(CreateMusicTable)) qDebug()<<"Create Music Table";

        //创建视频表
        QString CreateVideoTable = QString("CREATE TABLE `%1`.`video` (`video_id` INT NOT NULL AUTO_INCREMENT,`video_name` NVARCHAR(45) NOT NULL,`file_Addr` NVARCHAR(100) NULL,PRIMARY KEY (`video_id`),UNIQUE INDEX `video_id_UNIQUE` (`video_id` ASC));").arg(family_id);
        if(query.exec(CreateVideoTable)) qDebug()<<"Create Video Table";

        //创建文章表
        QString CreateArticleTable = QString("CREATE TABLE `%1`.`article` (`article_id` INT NOT NULL AUTO_INCREMENT,`article_name` NVARCHAR(45) NOT NULL,`URL` NVARCHAR(100) NULL,PRIMARY KEY (`article_id`),UNIQUE INDEX `article_id_UNIQUE` (`article_id` ASC));").arg(family_id);
        if(query.exec(CreateArticleTable)) qDebug()<<"Create Article Table";

        //创建音乐记录表
        QString CreateMusicRecordTable = QString("CREATE TABLE `%1`.`music_record` (`record_id` INT NOT NULL AUTO_INCREMENT,`music_id` INT NOT NULL,`user_id` INT NOT NULL,`time` DATETIME(6) NOT NULL,PRIMARY KEY (`record_id`));").arg(family_id);
        if(query.exec(CreateMusicRecordTable)) qDebug()<<"Create Music Record Table";

        //创建视频记录表
        QString CreateVideoRecordTable = QString("CREATE TABLE `%1`.`video_record` (`record_id` INT NOT NULL AUTO_INCREMENT,`video_id` INT NOT NULL,`user_id` INT NOT NULL,`time` DATETIME(6) NOT NULL,PRIMARY KEY (`record_id`));").arg(family_id);
        if(query.exec(CreateVideoRecordTable)) qDebug()<<"Create Video Record Table";

        //创建文章记录表
        QString CreateArticleRecordTable = QString("CREATE TABLE `%1`.`article_record` (`record_id` INT NOT NULL AUTO_INCREMENT,`article_id` INT NOT NULL,`user_id` INT NOT NULL,`time` DATETIME(6) NOT NULL,PRIMARY KEY (`record_id`));").arg(family_id);
        if(query.exec(CreateArticleRecordTable)) qDebug()<<"Create Article Record Table";

        //创建留言表
        QString CreateMessagesTable = QString("CREATE TABLE `%1`.`messages` (`messages_id` INT NOT NULL AUTO_INCREMENT,`user_name` NVARCHAR(45) NOT NULL,`content` NVARCHAR(140) NOT NULL,`time` DATETIME(6) NULL,PRIMARY KEY (`messages_id`));").arg(family_id);
        if(query.exec(CreateMessagesTable)) qDebug()<<"Create Messages Table";

        //创建音乐收藏表
        QString CreateMusicCollectionTable = QString("CREATE TABLE `%1`.`collect_music` (`collect_id` INT NOT NULL AUTO_INCREMENT,`user_name` NVARCHAR(45) NOT NULL,`music_name` NVARCHAR(45) NOT NULL,PRIMARY KEY (`collect_id`));").arg(family_id);
        if(query.exec(CreateMusicCollectionTable)) qDebug()<<"Create Music Collection Table";

        //创建视频收藏表
        QString CreateVideoCollectionTable = QString("CREATE TABLE `%1`.`collect_video` (`collect_id` INT NOT NULL AUTO_INCREMENT,`user_name` NVARCHAR(45) NOT NULL,`video_name` NVARCHAR(45) NOT NULL,PRIMARY KEY (`collect_id`));").arg(family_id);
        if(query.exec(CreateVideoCollectionTable)) qDebug()<<"Create Video Collection Table";

        //创建文章收藏表
        QString CreateArticleCollectionTable = QString("CREATE TABLE `%1`.`collect_article` (`collect_id` INT NOT NULL AUTO_INCREMENT,`user_name` NVARCHAR(45) NOT NULL,`article_name` NVARCHAR(45) NOT NULL,PRIMARY KEY (`collect_id`));").arg(family_id);
        if(query.exec(CreateArticleCollectionTable)) qDebug()<<"Create Article Collection Table";

        QString name;
        {
            name = QSqlDatabase::database().connectionName();
        }//超出作用域，隐含对象QSqlDatabase::database()被删除。
        QSqlDatabase::removeDatabase(name);
        qDebug()<<"create Family function disconnect";
        qDebug()<<"";
        return family_id.toInt();

    }else return false;
}

bool AddMember(User user){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","AddMember");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("Login");      //连接数据库名，与设置一致
    db.setUserName("client");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"AddMember function connect";
        QSqlQuery query(db);
        if(query.exec(QString("INSERT INTO `%1`.members (`user_id`, `user_name`, `special`) VALUES ('%2', '%3', '%4');").arg(QString::number(user.getFamilyId())).arg(QString::number(user.getId())).arg(user.getName()).arg(QString::number(user.getSpecial())))) qDebug()<<"Add member info successfully";
        else qDebug()<<"Add member info failure";
        QString name;
        {
            name = QSqlDatabase::database().connectionName();
        }//超出作用域，隐含对象QSqlDatabase::database()被删除。
        QSqlDatabase::removeDatabase(name);
        qDebug()<<"AddMember function disconnect";
        return true;
    }
    else return false;
}
