#include "xmlhandler.h"

XMLHandler::XMLHandler(QString filename, QWidget* parent)
{
    file = new QFile(filename);
    this->parent = parent;
    builder = 0;
}

bool XMLHandler::read(AbstractMappingDataBuilder * builder){
    QString errorStr;
    int errorLine;
    int errorColumn;

    this->builder = builder;

    //Carrega o xml para memória
    if (!domDocument.setContent(file, true, &errorStr, &errorLine,
                             &errorColumn)) {
     QMessageBox::information(parent, tr("Emotional Mapper"),
                              tr("Parse error at line %1, column %2:\n%3")
                              .arg(errorLine)
                              .arg(errorColumn)
                              .arg(errorStr));
     return false;
    }

    //Faz algumas verificações sobre a validade do ficheiro
    QDomElement root = domDocument.documentElement();
    if (root.tagName() != "emotionalagentmapper") {
        QMessageBox::information(parent, tr("Emotional Mapper"),
                                 tr("The file is not a Emotinal Mapper file."));
        return false;
    } else if (root.hasAttribute("version")
               && root.attribute("version") != "1.0") {
        QMessageBox::information(parent, tr("Emotional Mapper"),
                                 tr("The file is not a Emotinal Mapper version 1.0 "
                                    "file."));
        return false;
    }

    QDomElement geographic_bonduaries = root.firstChildElement("geographic_bonduaries");
    if(geographic_bonduaries.isNull()){
        showError("The element geographic_bonduaries does not exist. The parsing of the file will be aborted.");
        return false;
    }
    parseGeographicBonduaries(geographic_bonduaries);

    QDomElement frame_set = root.firstChildElement("frame_set");
    if(frame_set.isNull()){
        showError("The element frame_set does not exist. The parsing of the file will be aborted.");
        return false;
    }
    parseFrameSet(frame_set);
}

void XMLHandler::parseGeographicBonduaries(QDomElement el){
    QDomElement type_el = el.firstChildElement("type");
    QString type_str = type_el.text();

    QDomElement lower_left = el.firstChildElement("lower_left");
    QString x_str = lower_left.firstChildElement("x").text();
    QString y_str = lower_left.firstChildElement("y").text();
    qreal ll_x = x_str.toDouble();
    qreal ll_y = y_str.toDouble();

    QDomElement upper_right = el.firstChildElement("upper_right");
    x_str = upper_right.firstChildElement("x").text();
    y_str = upper_right.firstChildElement("y").text();
    qreal ur_x = x_str.toDouble();
    qreal ur_y = y_str.toDouble();

    builder->setCoordinates(type_str, QPointF(ll_x,ll_y),QPointF(ur_x,ur_y));

    QDomElement background_image_path_el = el.firstChildElement("bg");
    if(!background_image_path_el.isNull())
        builder->setBackgroundImage(background_image_path_el.text());
    else
        builder->setBackgroundImage("");

    QDomElement agent_size_el = el.firstChildElement("agent_ellipse_size");
    if(!agent_size_el.isNull())
        builder->setAgentEllipseSize(agent_size_el.text().toDouble());

    QDomElement agent_colors_el = el.firstChildElement("agent_colors");
    if(!agent_colors_el.isNull()){
        QDomElement agent_emotion_el = agent_colors_el.firstChildElement("e");

        while(!agent_emotion_el.isNull()){
            QString e_name = agent_emotion_el.attribute("name");
            int red = agent_emotion_el.attribute("r").toInt();
            int green = agent_emotion_el.attribute("g").toInt();
            int blue = agent_emotion_el.attribute("b").toInt();

            builder->setEmotionColor(e_name,QColor(red,green,blue));

            agent_emotion_el = agent_emotion_el.nextSiblingElement("e");
        }
    }
}

void XMLHandler::parseFrameSet(QDomElement el){
    QString time_units = el.attribute("time_units");
    int size = el.attribute("size").toInt();

    builder->beginFrameSet(time_units);

    //Parsing das frames dentro do frame_set
    QDomElement f = el.firstChildElement("f");
    while (!f.isNull()) {

        qreal t = f.attribute("t").toDouble();

        builder->beginFrame(t);

        //Parsing dos agentes dentro da frame
        QDomElement a = f.firstChildElement("a");
        while(!a.isNull()){
            QString n = a.attribute("n");
            QString c = a.attribute("c");

            builder->beginAgent(n,c);

            //Faz parsing às emoçoes do agente
            QDomElement elist = a.firstChildElement("el");
            if(!elist.isNull()){
                QDomElement emotion_el = elist.firstChildElement("e");
                while(!emotion_el.isNull()){
                    QString name = emotion_el.attribute("n");
                    qreal intensity = emotion_el.attribute("i").toDouble();
                    builder->addEmotion(name,intensity);

                    emotion_el = emotion_el.nextSiblingElement("e");
                }

            }

            //Faz parsing aos goals do agente
            QDomElement glist = a.firstChildElement("gl");
            if(!glist.isNull()){
                QDomElement goal_el = glist.firstChildElement("g");
                while(!goal_el.isNull()){
                    QString description = goal_el.attribute("d");

                    if(description.length()==0)
                        description = goal_el.firstChildElement("d").text();

                    builder->addGoal(description);

                    goal_el = goal_el.nextSiblingElement("g");
                }

            }

            //Faz parsing aos beliefs do agente
            QDomElement blist = a.firstChildElement("bl");
            if(!blist.isNull()){
                QDomElement belief_el = blist.firstChildElement("b");
                while(!belief_el.isNull()){
                    QString description = belief_el.attribute("d");

                    if(description.length()==0)
                        description = belief_el.firstChildElement("d").text();

                    builder->addBelief(description);

                    belief_el = belief_el.nextSiblingElement("b");
                }

            }

            a = a.nextSiblingElement("a");
        }

        f = f.nextSiblingElement("f");
    }

}

void XMLHandler::showError(QString message){
    QMessageBox::information(parent, tr("Emotional Mapper"), message);
}

























