#ifndef ARTICLE_H
#define ARTICLE_H

#include <QString>
#include <user.h>
#include <QDateTime>

class Article{
public:
    Article(int articleid,QString articleName,QString URL){
        this->articleid = articleid;
        this->articleName = articleName;
        this->URL = URL;
    }

    int getId(){
        return this->articleid;
    }
    QString getArticleName(){
        return this->articleName;
    }
    QString getURL(){
        return this->URL;
    }
private:
    int articleid;
    QString articleName;
    QString URL;

};

class ArticleRecord{
public:
    ArticleRecord(QString user_name,QString article_mame,QDateTime time){
        this->user_name = user_name;
        this->article_mame = article_mame;
        this->time = time;
    }
    QString getUserName(){
        return this->user_name;
    }
    QString getArticleName(){
        return this->article_mame;
    }
    QDateTime getTime(){
        return this->time;
    }
private:
    QString user_name;
    QString article_mame;
    QDateTime time;
};

bool addArticleRecord(Article article,User user);

int addNewArticle(QString articleName,User user);

int ifNewArticle(QString articleName,User user);

QList<ArticleRecord> syncArticleRecord(User user,int start,int numbers,int Tspecial);

#endif // ARTICLE_H
