#include "mappingrawdata.h"

MappingRawData::MappingRawData(QPointF lower_left, QPointF upper_right)
{
    this->lower_left=lower_left;
    this->upper_right=upper_right;
    current_iterator_index = 0;
    agentElipseSize = 10; //Default size

    //Default colors
    emotion_to_color_dictionary.insert("happy",Qt::red);
    emotion_to_color_dictionary.insert("unhappy",Qt::blue);
    emotion_to_color_dictionary.insert("fear",QColor(122,27,224));
    emotion_to_color_dictionary.insert("hope",Qt::green);
    emotion_to_color_dictionary.insert("surprise",Qt::yellow);
    emotion_to_color_dictionary.insert("disappointed",Qt::cyan);
    emotion_to_color_dictionary.insert("relieved",Qt::magenta);
}

void MappingRawData::setAgentElipseSize(qreal size){
    agentElipseSize = size;
}

qreal MappingRawData::getAgentElipseSize(){
    return agentElipseSize;
}

void MappingRawData::setEmotionColor(QString emotion, QColor color){
    if(emotion_to_color_dictionary.contains(emotion))
        emotion_to_color_dictionary.remove(emotion);

    emotion_to_color_dictionary.insert(emotion,color);
}

QHash<QString, QColor> MappingRawData::getEmotionColorDict(){
    return emotion_to_color_dictionary;
}

void MappingRawData::addFrame(Frame* f){
    frame_list.append(f);
}

Frame* MappingRawData::getFrame(qreal t){
    for(int i=0;i<frame_list.size();i++)
        if(frame_list[i] && frame_list[i]->t==t)
            return frame_list[i];
    return 0;
}

Frame* MappingRawData::getLastFrame(){
    return frame_list[frame_list.size()-1];
}

//Iterator for the frames
void MappingRawData::first(){
    current_iterator_index = 0;
}

void MappingRawData::last(){
    current_iterator_index= frame_list.size()-1;
}

bool MappingRawData::next(){
    current_iterator_index++;
    return current_iterator_index<frame_list.size();
}

bool MappingRawData::hasNext(){
    return current_iterator_index<frame_list.size();
}

Frame* MappingRawData::current(){
    return frame_list[current_iterator_index];
}

void MappingRawData::goTo(qreal f){
    current_iterator_index = (frame_list.size()-1)*f;
}



QPointF MappingRawData::getLowerLeft(){
    return lower_left;
}

QPointF MappingRawData::getUpperRight(){
    return upper_right;
}


QString MappingRawData::getBackgroundImagePath(){
    return background_image_path;
}

void MappingRawData::setbackgroundImagePath(QString path){
    background_image_path = path;
}
