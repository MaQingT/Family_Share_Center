#ifndef RECOMMEND_H
#define RECOMMEND_H

#include <QString>
#include <QDateTime>
#include <user.h>
#include <QDebug>
#include <QtWidgets/QMessageBox>
#include <music.h>
#include <video.h>
#include <article.h>

QList<Music> recommendMusic(User user);

QList<Video> recommendVideo(User user);

#endif // RECOMMEND_H
