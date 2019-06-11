#include "connection.h"

//函数实现

//注册函数，其中包含两部分，分别为用户注册部分与家庭登录、注册部分
User Registe(QString User_name,QString userpassword,QString Family_name,int special,QString Family_password){

    //通过Family_login函数获取加入家庭的Family_id
    int Family_id = Family_login(Family_name,Family_password);
    qDebug()<<"The family_id of this user is "<<Family_id;
    if(!Family_id){
        //回传一个无效的User对象，代表注册失败
        return User::getNULL();
    }

    //通过User_registe函数取得创建后的User_id
    int User_id = User_Registe(User_name,userpassword,Family_id,special);
    qDebug()<<"The User_id of this user is "<<User_id;
    if(User_id == false){
        //回传一个无效的User对象，代表注册失败
        return User::getNULL();
    }
    //实例化一个User对象，代表注册成功
    User user(User_id,User_name,userpassword,Family_id,special);

    //向数据库中添加当前User的信息
    if(AddMember(user)) return user;

    return user;
}

//用户登陆函数
User User_login(QString User_name,QString password){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","User_login");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("Login");      //连接数据库名，与设置一致
    db.setUserName("client");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致
    if (db.open())
    {
        qDebug()<<"User_login function connect";
        QSqlQuery query(db);
        if(query.exec(QString("select * from Login.User_info where user_name = '%1' and user_password = '%2';").arg(User_name).arg(password)) && query.next())
        {
            //获取登录信息
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            QString psw = query.value(2).toString();
            int Familyid = query.value(3).toInt();
            int special = query.value(4).toInt();
            if((User_name == name) && (password == psw)){

                //如果登陆成功，则回传一个根据用户信息生成的User对象
                User user(id,name,psw,Familyid,special);
                QString name;
                {
                    name = QSqlDatabase::database().connectionName();
                }//超出作用域，隐含对象QSqlDatabase::database()被删除。
                QSqlDatabase::removeDatabase(name);
                qDebug()<<"User_login function disconnect";
                return user;
            }
        }
        else {
            //如果登陆失败则弹出对话框，提示登陆失败
            QMessageBox::information(NULL,"Error","用户名或密码错误，请重试！！！", QMessageBox::Yes);
        }
        QString name;
        {
            name = QSqlDatabase::database().connectionName();
        }//超出作用域，隐含对象QSqlDatabase::database()被删除。
        QSqlDatabase::removeDatabase(name);
        qDebug()<<"User_login function disconnect";
        //若登录未成功，则回传一个无效的User对象
        return User::getNULL();
    }
    else
    {
        //若未能连接数据库，则弹出对话框提示未能成功登录，并回传一个无效的User对象
        QMessageBox::information(NULL,"Error","登录失败，请重试！！！", QMessageBox::Yes);
        return User::getNULL();
    }
}

//用户注册函数
int User_Registe(QString name,QString password,int Family_id,int special){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","User_Registe");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName("Login");      //连接数据库名，与设置一致
    db.setUserName("client");          //数据库用户名，与设置一致
    db.setPassword("");    //数据库密码，与设置一致

    if (db.open())
    {
        qDebug()<<"User_Registe function connect";
        QSqlQuery query(db);

        //用于向数据表中查询用户名的SQL语句
        QString S =QString("select * from Login.User_info where User_name='%1' ").arg(name);

        //用于向数据库中添加新的用户信息的SQL语句
        QString I=QString("INSERT INTO Login.User_info (`user_name`, `user_password`, `Family_id`, `special`) VALUES ('%1', '%2', '%3', '%4'); ").arg(name).arg(password).arg(Family_id).arg(special);
        query.exec(S);
        if(query.next()){
            QMessageBox::information(NULL,"注册失败","用户名重复",QMessageBox::Yes);
            qDebug()<<"Repeat of user name";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"User_Registe function disconnect";
            return false;
        }
        if(query.exec(I)){
            QMessageBox::information(NULL,"注册成功","注册成功",QMessageBox::Yes);
            qDebug()<<"Registe successfully";
            query.exec(QString("select user_id from Login.User_info where user_name='%1'; ").arg(name));
            query.next();int id =  query.value(0).toInt();
            qDebug()<<"user id is "<<id;
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"User_Registe function disconnect";
            qDebug()<<"";
            return id;
        }

    }
    else
    {
        qDebug()<<"Cannot open database , Unable to establish a database login";
        return false;
    }
    return false;
}

//家庭加入函数，该函数对传入的两个参数进行识别
//若该家庭存在，则调用加入家庭函数
//若家庭不存在，则向用户请求是否创建家庭
//若创建家庭则调用创建家庭函数
//若不创建则要求用户重新输入内容
//回传该用户的家庭id
int Family_login(QString Family_name, QString Family_password){
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","Family_login");
    db.setHostName("114.116.191.248");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                       //连接数据库端口号，与设置一致
    db.setDatabaseName("Login");            //连接数据库名，与设置一致
    db.setUserName("client");               //数据库用户名，与设置一致
    db.setPassword("");                     //数据库密码，与设置一致

    if(db.open()){
        qDebug()<<"Family_login function connect";
        QSqlQuery query(db);

        //用于向数据库查询家庭信息的SQL语句
        QString S =QString("select * from Login.family_info where family_name = '%1' and family_password = '%2'; ").arg(Family_name).arg(Family_password);
        query.exec(S);
        if(query.next()){

            //如果家庭信息正确，则取出Family_id并回传
            int id = query.value(1).toInt();
            QMessageBox::information(NULL, "加入成功", "加入成功！！！", QMessageBox::Yes);
            QString name;
            qDebug()<<"Get family id "<<id;
            qDebug()<<"family information correct";
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"Family_login function disconnect";
            return id;
        }
        else {
            //若信息有误，提示用户是否创建家庭
            qDebug()<<"family info incorrect";
            QString name;
            {
                name = QSqlDatabase::database().connectionName();
            }//超出作用域，隐含对象QSqlDatabase::database()被删除。
            QSqlDatabase::removeDatabase(name);
            qDebug()<<"Family_login function disconnect";
            if(QMessageBox::information(NULL,"加入失败","未找到相关家庭，是否创建新家庭？",QMessageBox::Yes|QMessageBox::No,QMessageBox::No)==QMessageBox::Yes){

                //若用户选择创建则调用家庭创建函数，取得该函数的返回结果，即家庭的创建情况，将该结果会回传
                return createFamily(Family_name,Family_password);;
            }
            else {
                //若选择
                return false;
            }
        }
    }
    return false;
}
