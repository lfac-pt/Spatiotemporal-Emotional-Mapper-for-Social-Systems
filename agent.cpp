#include "agent.h"
#include <QDebug>

Agent::Agent(int n, QPointF coordinates, QString real_name)
{
    this->n=n;
    this->coordinates=coordinates;
    this->real_name=real_name;
}

void Agent::addEmotion(Emotion* e){
    emotion_list.append(e);
}

void Agent::addGoal(QString * g){
    goal_list.append(g);
}

void Agent::addBelief(QString * d){
    belief_list.append(d);
}

Emotion* Agent::getStrongestEmotion(){
    if(emotion_list.size()==0)
        return 0;

    Emotion* max = emotion_list[0];
    foreach(Emotion* e, emotion_list){
        if(e->intensity>max->intensity)
            max = e;
    }
    return max;
}
