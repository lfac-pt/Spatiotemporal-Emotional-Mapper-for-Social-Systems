#ifndef AGENT_H
#define AGENT_H

#include <QObject>
#include <QtCore>
#include "emotion.h"

class Agent : public QObject
{
public:
    Agent(int n, QPointF coordinates, QString real_name);
    void addEmotion(Emotion* e);
    void addGoal(QString *);
    void addBelief(QString *);
    Emotion* getStrongestEmotion();

    int n;
    QPointF coordinates;
    QList<Emotion*> emotion_list;
    QList<QString*> goal_list;
    QList<QString*> belief_list;
    QString real_name;
};

#endif // AGENT_H
