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

bool addVideoRecord(Video video,User user);

bool addNewVideo(QString videoName,User user);

bool ifNewVideo(QString videoName,User user);

#endif // VIDEO_H
