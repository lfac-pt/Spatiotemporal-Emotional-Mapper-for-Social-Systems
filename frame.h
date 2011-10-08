#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QtCore>
#include "agent.h"

class Frame : public QObject
{
public:
    Frame(qreal t);
    void addAgent(Agent * a);
    qreal t;
    QList<Agent*> agent_list;

    //Itertor para agentes
    void first();
    bool next();
    Agent* current();
    int current_index;
};

#endif // FRAME_H
