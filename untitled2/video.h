#ifndef VIDEO_H
#define VIDEO_H
#include <QString>
#include <QDateTime>
#include <user.h>
#include <QDebug>
#include <QtWidgets/QMessageBox>

class Video{
public:
    Video(int videoId,QString videoName){
        this->videoId = videoId;
        this->videoName = videoName;
    }

    int getId(){
        return this->videoId;
    }

    QString getName(){
        return this->videoName;
    }

private:
    int videoId;
    QString videoName;
};

class VideoRecord{
public:

    VideoRecord(QString user_name,QString video_name,QDateTime time){
        this->user_name = user_name;
        this->video_name = video_name;
        this->time = time;
    }

    QString getUserName(){
        return this->user_name;
    }

    QString getVideoName(){
        return this->video_name;
    }

    QDateTime getTime(){
        return this->time;
    }

private:

    QString user_name;
    QString video_name;
    QDateTime time;

};

bool addVideoRecord(Video video,User user);

int addNewVideo(QString videoName,User user);

int ifNewVideo(QString videoName,User user);

QList<VideoRecord> syncVideoRecord(User user,int Tspecial);

QList<Video> syncVideoCollection(User user);

bool addNewVideoCollect(User user,Video video);

bool deleteVideoCollect(User user,Video video);

#endif // VIDEO_H
