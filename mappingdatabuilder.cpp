#include "mappingdatabuilder.h"

MappingDataBuilder::MappingDataBuilder()
{
    mrd = 0;
    verbose = false;
    dirty_agent = dirty_frame = false;
    time_multipliers_dictionary = new QHash<QString, qreal>;
    time_multipliers_dictionary->insert("seg",1);
    /*time_multipliers_dictionary->insert("min",60);
    time_multipliers_dictionary->insert("hour",3600);
    time_multipliers_dictionary->insert("day",86400);
    time_multipliers_dictionary->insert("year",31536000);
    */error_log = "";
    agent_couter = 0;
}

void MappingDataBuilder::setCoordinates(QString type, QPointF lower_left, QPointF upper_right) {
    if(verbose)qDebug()<<"setCoordinates type:"+type;
    if(type=="2d_carthesian")
        mrd = new MappingRawData(lower_left,upper_right);
    else{
        error_log = error_log + "Error: the coordinates type "+type+" is not supported. Try '2d_carthesian'\n";
        mrd = new MappingRawData(lower_left,upper_right);
    }
}

void MappingDataBuilder::setBackgroundImage(QString path){
    if(path.length()>0 && !QFile::exists(path))
        error_log = error_log + "Error: the background image file "+path+" wasn't found.\n";
    else if(path.endsWith(".jpg") || path.endsWith(".jpeg"))
        error_log = error_log + "Error: the background image format (jpeg) is not supported due to a Qt bug.\n";

    mrd->setbackgroundImagePath(path);
}

void MappingDataBuilder::setAgentEllipseSize(qreal size){
    if(size<=0)
        error_log = error_log +"Error: the agent ellipse size must be bigger than 0";

    mrd->setAgentElipseSize(size);
}

void MappingDataBuilder::setEmotionColor(QString emotion, QColor color){
    mrd->setEmotionColor(emotion, color);
}

void MappingDataBuilder::beginFrameSet(QString time_units) {
    if(verbose)qDebug()<<"beginFrameSet time_units:"+time_units;

    if(time_multipliers_dictionary->contains(time_units))
        time_multiplier= time_multipliers_dictionary->value(time_units);
    else
        error_log = error_log + "Error: the times units "+time_units+" is not supported. Try 'seg'\n";
}

void MappingDataBuilder::beginFrame(qreal t) {
    if(verbose)qDebug()<<"beginFrame beginFrame:"+QString().number(t);

    if(dirty_agent){
        in_constrution_frame->addAgent(in_constrution_agent);
        dirty_agent = false;
    }

    if(dirty_frame)
        mrd->addFrame(in_constrution_frame);

    in_constrution_frame = new Frame(t);
    dirty_frame=true;
}

void MappingDataBuilder::beginAgent(QString n_str, QString coordinates) {
    int n;
    if(agent_dict.contains(n_str))
        n = agent_dict.value(n_str);
    else{
        n = agent_couter++;
        agent_dict.insert(n_str,n);
    }

    if(verbose)qDebug()<<"beginAgent n:"+QString().number(n);

    if(dirty_agent)
        in_constrution_frame->addAgent(in_constrution_agent);

    QStringList qsl = coordinates.split(' ');
    qreal x = qsl.at(0).toDouble();
    qreal y = qsl.at(1).toDouble();

    in_constrution_agent = new Agent(n, QPointF(x,y),n_str);
    dirty_agent=true;
}

void MappingDataBuilder::addEmotion(QString name, qreal intensity) {
    if(verbose)qDebug()<<"addEmotion name:"+name+" intensity:"<<intensity;

    if(intensity>1 || intensity<0)
        error_log=error_log+"Error in frame t="+QString().number(in_constrution_frame->t)+" agent n="+QString().number(in_constrution_agent->n)+": intensity out of bounds. Must be [0,1].\n";

    in_constrution_agent->addEmotion(new Emotion(name, intensity));
}

void MappingDataBuilder::addGoal(QString description) {
    if(verbose)qDebug()<<"addGoal description:"+description;

    in_constrution_agent->addGoal(new QString(description));
}

void MappingDataBuilder::addBelief(QString description){
    if(verbose)qDebug()<<"addBelief description:"+description;

    in_constrution_agent->addBelief(new QString(description));
}

MappingRawData* MappingDataBuilder::getResult(){
    if(dirty_agent){
        in_constrution_frame->addAgent(in_constrution_agent);
        dirty_agent=false;
    }

    if(dirty_frame){
        mrd->addFrame(in_constrution_frame);
        dirty_frame=false;
    }

    if(verbose)qDebug()<<"MappingRawData build finished";
    return mrd;
}
