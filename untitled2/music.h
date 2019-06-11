#ifndef MUSIC_H
#define MUSIC_H
#include <QString>
#include <QDateTime>
#include <user.h>
#include <QDebug>

class Music{
public:
    music(int musicId,QString musicName,QString artist,QString localAddr){
        this->musicId = musicId;
        this->musicName = musicName;
        this->artist = artist;
        this->localAddr = localAddr;
    }

    int getId(){
        return this->musicId;
    }

    QString getName(){
        return this->musicName;
    }

    QString getArtist(){
        return this->artist;
    }

    QString getLocalAddr(){
        return this->localAddr;
    }

private:
    int musicId;
    QString musicName;
    QString artist;
    QString localAddr;
};

class MusicRecord{
public:
    MusicRecord(QString user_name,QString music_name,QDateTime time){
        this->user_name = user_name;
        this->music_name = music_name;
        this->time = time;
    }

    QString getUserName(){
        return this->user_name;
    }
    QString getMusicName(){
        return this->music_name;
    }
    QDateTime getTime(){
        return this->time;
    }
private:
    QString user_name;
    QString music_name;
    QDateTime time;
};

bool addRecord(Music music,User user);
bool addNewMusic(Music music,User user);
bool ifNewMusic(QString musicName,QString artist,User user);
QList<MusicRecord> syncMusicRecord(User user,int start,int numbers,int Tspecial);

#endif // MUSIC_H
