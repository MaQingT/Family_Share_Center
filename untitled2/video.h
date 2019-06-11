#ifndef VIDEO_H
#define VIDEO_H
#include <QString>
#include <QDateTime>
#include <user.h>
#include <QDebug>

class Video{
public:
    Video(int videoId,QString videoName,QString artist,QString localAddr){
        this->videoId = videoId;
        this->videoName = videoName;
        this->artist = artist;
        this->localAddr = localAddr;
    }

    int getId(){
        return this->videoId;
    }

    QString getName(){
        return this->videoName;
    }

    QString getArtist(){
        return this->artist;
    }

    QString getLocalAddr(){
        return this->localAddr;
    }

private:
    int videoId;
    QString videoName;
    QString artist;
    QString localAddr;
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

bool addNewVideo(QString videoName,User user);

bool ifNewVideo(QString videoName,User user);

QList<VideoRecord> syncVideoRecord(User user,int start,int numbers,int Tspecial);

#endif // VIDEO_H
