#include "frame.h"

Frame::Frame(qreal t)
{
    this->t=t;
    current_index=0;
}

void Frame::addAgent(Agent * a){
    agent_list.append(a);
}

void Frame::first(){
    current_index=0;
}

bool Frame::next(){
    current_index++;
    return current_index<agent_list.size();
}

Agent* Frame::current(){
    return agent_list[current_index];
}
