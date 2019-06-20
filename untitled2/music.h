#ifndef MUSIC_H
#define MUSIC_H
#include <QString>
#include <QDateTime>
#include <user.h>
#include <QDebug>
#include <QtWidgets/QMessageBox>

class Music{
public:
    Music(int musicId,QString musicName,QString style){
        this->musicId = musicId;
        this->musicName = musicName;
        this->style = style;
    }

    int getId(){
        return this->musicId;
    }

    QString getName(){
        return this->musicName;
    }

    QString getStyle(){
        return this->style;
    }

private:
    int musicId;
    QString musicName;
    QString style;
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

bool addMusicRecord(Music music,User user);

int addNewMusic(QString musicName,User user);

int ifNewMusic(QString musicName,User user);

QList<MusicRecord> syncMusicRecord(User user,int Tspecial);

QList<Music> syncMusicCollection(User user);

bool addNewMusicCollect(User user,Music music);

#endif // MUSIC_H
