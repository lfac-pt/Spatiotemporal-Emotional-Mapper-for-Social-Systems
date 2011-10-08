#include "emmainwindow.h"
#include "ui_emmainwindow.h"

EMMainWindow::EMMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EMMainWindow)
{
    ui->setupUi(this);

    default_input_filename = "emotional_map.xml";
    mustQuit=doneFirstShow=false;

    if(QFile::exists(default_input_filename))
        init(default_input_filename);
}

void EMMainWindow::resizeEvent ( QResizeEvent * event ){
    map_widget->viewSizeChanged();
}

void EMMainWindow::init(QString existing_emotional_map_path){
    XMLHandler* xh = new XMLHandler(existing_emotional_map_path,this);
    MappingDataBuilder * mdb = new MappingDataBuilder();
    xh->read(mdb);
    mapping_raw_data = mdb->getResult();

    if(mdb->error_log.length()>0){
        mustQuit=true;
        error_log=mdb->error_log;
    }


    map_widget = new SpacialAndTemporalMapWidget(mapping_raw_data, QSize(500,281.25));
    ui->mapLayout->addWidget(map_widget);

    connect(map_widget,SIGNAL(adicionalInfoChanged(Agent*)),SLOT(updateAgentAdicionalInfo(Agent*)));
    connect(map_widget,SIGNAL(tick(qreal)),SLOT( mapTicked(qreal)));


    connect(ui->mapSlider,SIGNAL(sliderMoved(int)),SLOT(sliderModed(int)));
    map_widget->connect(ui->stopButton,SIGNAL(clicked()),SLOT(stop()));
    map_widget->connect(ui->playPauseButton,SIGNAL(clicked()),SLOT(tooglePlay()));
    map_widget->connect(ui->frameRateSpinBox,SIGNAL(valueChanged(int)),SLOT(setFrameRate(int)));
    map_widget->connect(ui->zoomHorizontalSlider,SIGNAL(valueChanged(int)),SLOT(setZoom(int)));

    ui->stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    ui->playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(ui->playPauseButton,SIGNAL(clicked()),SLOT(tooglePlayPauseBtn()));
    connect(ui->stopButton,SIGNAL(clicked()),SLOT(toPlayBtn()));
    btnIsPlay = true;

    ui->mapSlider->setMaximum((int)mapping_raw_data->getLastFrame()->t);

    connect(ui->emotionsPlotPushButton,SIGNAL(clicked()),SLOT(plotEmotions()));
    connect(ui->goalsPlotPushButton,SIGNAL(clicked()),SLOT(plotGoals()));
    connect(ui->beliefsPlotPushButton,SIGNAL(clicked()),SLOT(plotBeliefs()));
    map_widget->connect(ui->exportButton,SIGNAL(clicked()),SLOT(exportToImage()));
    connect(ui->emotionsPlotAllPushButton,SIGNAL(clicked()),SLOT(plotAllEmotions()));
}

void EMMainWindow::plotEmotions(){
    int n = map_widget->getSelectedAgent();
    if(n>=0){
        QString agent_name = mapping_raw_data->current()->agent_list[n]->real_name;

        QPointer<DataPlot> data_plot;
        if(!ui->emotionsPlotCheckBox->isChecked())
            data_plot = new DataPlot("Emotions of the agent '"+agent_name+"'",1,mapping_raw_data->getLastFrame()->t);
        else{
            //Procura o último plot válido
            for(int i=plots_with_progressive_series.size()-1;i>=0;i--){
                if(plots_with_progressive_series[i]){
                    data_plot = plots_with_progressive_series[i];
                    break;
                }
            }

            //Para o caso de não encontrar nenhum plot válido (que não tenha sido fechado)
            if(!data_plot){
                data_plot = new DataPlot("Emotions of the agent '"+agent_name+"'",1,mapping_raw_data->getLastFrame()->t);
                ui->emotionsPlotCheckBox->setChecked(false);
            }
            else
                data_plot->setTitle("Multiple plot");
        }


        QHash<QString, QList<QPointF*>*> dict;

        for(int i=0;i<mapping_raw_data->frame_list.size();i++){
            foreach(Emotion* e,mapping_raw_data->frame_list[i]->agent_list[n]->emotion_list){
                QList<QPointF*>* list;
                if(dict.contains(e->name))
                    list = dict.value(e->name);
                else{
                    list = new QList<QPointF*>;
                    dict.insert(e->name,list);
                }

                list->append(new QPointF(mapping_raw_data->frame_list[i]->t,e->intensity));
            }
        }

        int target_size = 1 + (int)mapping_raw_data->getLastFrame()->t;

        foreach(QString str, dict.keys()){
            data_plot->addPointSeries(normalizePointList(dict.value(str),target_size),str+", n='"+agent_name+"'",map_widget->getColorForEmotion(str),true);
        }


        //Se estivermos a criar uma nova janela
        if(!ui->emotionsPlotCheckBox->isChecked()){
            plots_with_progressive_series.append(data_plot);
            data_plot->show();
        }
        else
            data_plot->ensureYLabels();

        if(mapping_raw_data->current()->t==0.0 && ui->mapSlider->value()==ui->mapSlider->maximum())
            data_plot->showInd((int)mapping_raw_data->getLastFrame()->t);
        else
            data_plot->showInd((int)mapping_raw_data->current()->t);

    }
}

void EMMainWindow::plotGoals(){
    int n = map_widget->getSelectedAgent();
    if(n>=0){
        QString agent_name = mapping_raw_data->current()->agent_list[n]->real_name;

        QPointer<DataPlot> data_plot;

        if(!ui->goalPlotCheckBox->isChecked())
            data_plot = new DataPlot("Goals of the agent '"+agent_name+"'",1,mapping_raw_data->getLastFrame()->t,"");
        else{
            //Procura o último plot válido
            for(int i=plots_with_progressive_series.size()-1;i>=0;i--){
                if(plots_with_progressive_series[i]){
                    data_plot = plots_with_progressive_series[i];
                    break;
                }
            }

            //Para o caso de não encontrar nenhum plot válido (que não tenha sido fechado)
            if(!data_plot){
                data_plot = new DataPlot("Goals of the agent '"+agent_name+"'",1,mapping_raw_data->getLastFrame()->t,"");
                ui->goalPlotCheckBox->setChecked(false);
            }
            else
                data_plot->setTitle("Multiple plot");
        }

        QHash<QString, QList<QPointF*>*> dict;
        QHash<QString, qreal> yy_ind_dict;

        for(int i=0;i<mapping_raw_data->frame_list.size();i++){
            foreach(QString* str,mapping_raw_data->frame_list[i]->agent_list[n]->goal_list){
                //Vai buscar a lista onde se vai inserir o novo valor
                QList<QPointF*>* list;
                if(dict.contains(*str))
                    list = dict.value(*str);
                else{
                    list = new QList<QPointF*>;
                    dict.insert(*str,list);
                }

                //Vai buscar o valor do eixo dos yy que a emoção vai ter
                qreal ycord;
                if(yy_ind_dict.contains(*str))
                    ycord = yy_ind_dict.value(*str);
                else{
                    ycord = data_plot->getUnusedYInd();
                    yy_ind_dict.insert(*str,ycord);
                }

                list->append(new QPointF(mapping_raw_data->frame_list[i]->t,ycord));
            }
        }

        int target_size = 1 + (int)mapping_raw_data->getLastFrame()->t;

        foreach(QString str, dict.keys()){
            data_plot->addLineSeries(normalizePointList(dict.value(str),target_size),str+", n='"+agent_name+"'",map_widget->getColorForEmotion(str),true);
        }


        //Se estivermos a criar uma nova janela
        if(!ui->goalPlotCheckBox->isChecked()){
            plots_with_progressive_series.append(data_plot);
            data_plot->show();
        }

        if(mapping_raw_data->current()->t==0.0 && ui->mapSlider->value()==ui->mapSlider->maximum())
            data_plot->showInd((int)mapping_raw_data->getLastFrame()->t);
        else
            data_plot->showInd((int)mapping_raw_data->current()->t);
    }
}

void EMMainWindow::plotBeliefs(){
    int n = map_widget->getSelectedAgent();
    if(n>=0){
        QString agent_name = mapping_raw_data->current()->agent_list[n]->real_name;

        QPointer<DataPlot> data_plot;
        if(!ui->beliefsPlotCheckBox->isChecked())
            data_plot = new DataPlot("Beliefs of the agent '"+agent_name+"'",1,mapping_raw_data->getLastFrame()->t,"");
        else{
            //Procura o último plot válido
            for(int i=plots_with_progressive_series.size()-1;i>=0;i--){
                if(plots_with_progressive_series[i]){
                    data_plot = plots_with_progressive_series[i];
                    break;
                }
            }

            //Para o caso de não encontrar nenhum plot válido (que não tenha sido fechado)
            if(!data_plot){
                data_plot = new DataPlot("Beliefs of the agent '"+agent_name+"'",1,mapping_raw_data->getLastFrame()->t,"");
                ui->beliefsPlotCheckBox->setChecked(false);
            }
            else
                data_plot->setTitle("Multiple plot");
        }

        QHash<QString, QList<QPointF*>*> dict;
        QHash<QString, qreal> yy_ind_dict;

        for(int i=0;i<mapping_raw_data->frame_list.size();i++){
            foreach(QString* str,mapping_raw_data->frame_list[i]->agent_list[n]->belief_list){
                //Vai buscar a lista onde se vai inserir o novo valor
                QList<QPointF*>* list;
                if(dict.contains(*str))
                    list = dict.value(*str);
                else{
                    list = new QList<QPointF*>;
                    dict.insert(*str,list);
                }

                //Vai buscar o valor do eixo dos yy que a emoção vai ter
                qreal ycord;
                if(yy_ind_dict.contains(*str))
                    ycord = yy_ind_dict.value(*str);
                else{
                    ycord = data_plot->getUnusedYInd();
                    yy_ind_dict.insert(*str,ycord);
                }

                list->append(new QPointF(mapping_raw_data->frame_list[i]->t,ycord));
            }
        }


        int target_size = 1 + (int)mapping_raw_data->getLastFrame()->t;

        foreach(QString str, dict.keys()){
            data_plot->addLineSeries(normalizePointList(dict.value(str),target_size),str+", n='"+agent_name+"'",map_widget->getColorForEmotion(str),true);
        }


        //Se estivermos a criar uma nova janela
        if(!ui->beliefsPlotCheckBox->isChecked()){
            plots_with_progressive_series.append(data_plot);
            data_plot->show();
        }

        if(mapping_raw_data->current()->t==0.0 && ui->mapSlider->value()==ui->mapSlider->maximum())
            data_plot->showInd((int)mapping_raw_data->getLastFrame()->t);
        else
            data_plot->showInd((int)mapping_raw_data->current()->t);
    }
}


void EMMainWindow::plotAllEmotions(){
    DataPlot* data_plot = new DataPlot("Average Emotional Intensity",1,mapping_raw_data->getLastFrame()->t);

    QHash<QString, QList<QPointF*>*> dict;

    for(int i=0;i<mapping_raw_data->frame_list.size();i++){

        //Faz o somatório da intensidade de cada emoção para todos os agentes
        QHash<QString, qreal> t_dict;
        QHash<QString, int> n_dict;
        foreach(Agent* ag, mapping_raw_data->frame_list[i]->agent_list){
            foreach(Emotion* e,ag->emotion_list){
                qreal avg_i=0;
                qreal n_i=0;
                if(dict.contains(e->name)){
                    avg_i = t_dict.value(e->name);
                    n_i = n_dict.value(e->name);
                }
                else{
                    t_dict.insert(e->name,0);
                    n_dict.insert(e->name,0);
                }

                t_dict[e->name] = t_dict[e->name]+e->intensity;
                n_dict[e->name] = n_dict[e->name]+1;

            }
        }

        //Insere a média de cada emoção na lista correspondente
        foreach(QString str, t_dict.keys()){
            QList<QPointF*>* list;
            if(dict.contains(str))
                list = dict.value(str);
            else{
                list = new QList<QPointF*>;
                dict.insert(str,list);
            }

            qreal intensity = t_dict[str] / ((qreal)n_dict[str]);

            list->append(new QPointF(mapping_raw_data->frame_list[i]->t,intensity));
        }
    }

    int target_size = 1 + (int)mapping_raw_data->getLastFrame()->t;

    //Insere no gráfico uma série por cada emoção
    foreach(QString str, dict.keys()){
        data_plot->addPointSeries(normalizePointList(dict.value(str),target_size),str,map_widget->getColorForEmotion(str),true);
    }

    plots_with_progressive_series.append(data_plot);
    data_plot->show();

    if(mapping_raw_data->current()->t==0.0 && ui->mapSlider->value()==ui->mapSlider->maximum())
        data_plot->showInd((int)mapping_raw_data->getLastFrame()->t);
    else
        data_plot->showInd((int)mapping_raw_data->current()->t);
}

void EMMainWindow::sliderModed(int p){
    qreal f = ((qreal)p) / ((qreal) (ui->mapSlider->maximum() - ui->mapSlider->minimum()));
    map_widget->seek(f);

    if(!map_widget->isPlaying()){
        ui->currentTimeTextBrowser->setText(QString().number(f*mapping_raw_data->getLastFrame()->t)+" sec");
        ui->currentTimeTextBrowser->setAlignment(Qt::AlignRight);
    }
}

void EMMainWindow::mapTicked(qreal t){
    ui->currentTimeTextBrowser->setText(QString().number(t)+" sec");
    ui->currentTimeTextBrowser->setAlignment(Qt::AlignRight);

    if(!ui->frameRateSpinBox->hasFocus())
        ui->frameRateSpinBox->setValue(map_widget->getFrameRate());
    int slider_new_pos = ((t / mapping_raw_data->getLastFrame()->t) * ((qreal) (ui->mapSlider->maximum() - ui->mapSlider->minimum()))) + ui->mapSlider->minimum();
    ui->mapSlider->setValue(slider_new_pos);

    //Actualiza plots com séries progressivas
    for(int i=0;i<plots_with_progressive_series.size();i++)
        if(plots_with_progressive_series[i])
            plots_with_progressive_series[i]->showInd((int)t);

    //Se for a última frame põe o icone do botão a play
    if(t==mapping_raw_data->getLastFrame()->t){
        ui->playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        btnIsPlay = true;
    }
}

void EMMainWindow::updateAgentAdicionalInfo(Agent* a){
    ui->nAgentLabel->setText(a->real_name);
    ui->coordsTextBrowser->setText(QString().number(a->coordinates.x())+" "+QString().number(a->coordinates.y()));

    ui->goalListWidget->clear();
    foreach(QString* str, a->goal_list)
        ui->goalListWidget->addItem(*(str));

    ui->emotionListWidget->clear();
    foreach(Emotion* e, a->emotion_list)
        ui->emotionListWidget->addItem(e->name+" "+QString().number(e->intensity));

    ui->beliefsListWidget->clear();
    foreach(QString* str, a->belief_list)
        ui->beliefsListWidget->addItem(*(str));
}

EMMainWindow::~EMMainWindow()
{
    delete ui;
}

void EMMainWindow::tooglePlayPauseBtn(){
    if(btnIsPlay){
        ui->playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        btnIsPlay = false;
    }
    else{
        ui->playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        btnIsPlay = true;
    }
}

void EMMainWindow::toPlayBtn(){
    ui->playPauseButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    btnIsPlay = true;
}

void EMMainWindow::showEvent ( QShowEvent * event ) {
    if(!doneFirstShow){
        QFileDialog::Options options;
        QString selectedFilter;

        if(QFile::exists(default_input_filename))
            return;

        QString fileName = "";


        fileName = QFileDialog::getOpenFileName(this, "Open Emotion Map", ".", "XML Files (*.xml);;All Files (*)",
                                        &selectedFilter,
                                        options);

        if(fileName.length()==0){
            mustQuit=true;
            return;
        }

        event->accept();

        init(fileName);

        if(error_log.length()>0)
            QMessageBox::warning(this,"Error found",error_log);

        doneFirstShow=true;
    }
}

void EMMainWindow::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

//The plot class assumes that all the vectors have the size equal to the number of frames
//This function normalizes the size with points with y=0
QList<QPointF*>* EMMainWindow::normalizePointList(QList<QPointF*>* v, int target_size){
    //Esta implementação só funciona se houver uma frame por segundo

    QList<QPointF*>* n_list = new QList<QPointF*>;

    for(int i=0;i<target_size;i++)
        n_list->insert(i,new QPointF(i,0));

    foreach(QPointF* p, *v){
        int ind = (int)p->x();
        if(ind>=n_list->size()){
            qDebug()<<"Out of bounds ind "<<ind<<" size "<<n_list->size()<<" "<<(*v);
            break;
        }
        n_list->at(ind)->setX(p->x());
        n_list->at(ind)->setY(p->y());
    }

    return n_list;
}
