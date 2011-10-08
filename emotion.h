#ifndef EMOTION_H
#define EMOTION_H

#include <QObject>

class Emotion : public QObject
{
public:
    Emotion(QString name, qreal intensity);
    QString name;
    qreal intensity;
};

#endif // EMOTION_H
