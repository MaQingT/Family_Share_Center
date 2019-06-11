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

bool addArticleRecord(Article article,User user);

bool addNewArticle(QString articleName,User user);

bool ifNewArticle(QString articleName,User user);

#endif // ARTICLE_H
