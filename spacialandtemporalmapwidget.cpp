#include "spacialandtemporalmapwidget.h"
#include <QDebug>

SpacialAndTemporalMapWidget::SpacialAndTemporalMapWidget(MappingRawData* mrd, QSize size)
{
    mapping_raw_data = mrd;
    setMinimumSize(size);

    scene = new ClickableQGraphicsScene(QRectF(0,0,size.width(),size.height()),this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    view = new QGraphicsView(scene);

    QHBoxLayout * layout = new QHBoxLayout();
    this->setLayout(layout);
    layout->addWidget(view);

    view->setRenderHint(QPainter::Antialiasing);
    background_item = 0;
    if(mrd->getBackgroundImagePath().length()>0){
        QPixmap *background_pixmap = new QPixmap(mrd->getBackgroundImagePath());
        background_item = scene->addPixmap(*background_pixmap);

        qreal sx = scene->width() / (qreal) background_pixmap->width();
        qreal sy = scene->height() / (qreal) background_pixmap->height();

        background_item->scale(sx,sy);
    }
    else
        view->setBackgroundBrush(Qt::white);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    mapping_raw_data->first();

    n_select_agent=-1;

    timer_intreval=500;

    last_zoom_value = 10;

    agent_elipse_size = mrd->getAgentElipseSize();

    at_the_end = false;

    current_agent_selected_circle=0;

    connect(scene,SIGNAL(objectClicked(QGraphicsItem*)),SLOT(objectClickedInScene(QGraphicsItem* )));

    //Inicializa o temporizador
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));

    //Vai buscar o dicionario emoção -> cor
    emotion_to_color_dictionary = mrd->getEmotionColorDict();

    //Inicializa a lista dos objectos que representam os agentes na scene
    Frame* f = mapping_raw_data->current();
    f->first();
    do{
        QGraphicsItem* item = scene->addEllipse(0,0,5,5,QPen(Qt::transparent),QBrush(Qt::transparent));
        item->setPos(f->current()->coordinates);
        agents_circles.insert(f->current()->n,item);
    }while(f->next());
}

void SpacialAndTemporalMapWidget::viewSizeChanged(){
    /*if(background_item){
        int x_diff =  view->rect().width() - view->sceneRect().width();
        int y_diff = view->rect().height() - view->sceneRect().height();

        QPointF point = background_item->pos();
        point.setX( - (x_diff/2));
        point.setY( - (y_diff/2));
        background_item->setPos(point);
    }*/
}

void SpacialAndTemporalMapWidget::update(){
    //Muda o intrevalo do timer se for o caso
    if(timer->interval()!=timer_intreval)
        timer->setInterval(timer_intreval);

    Frame* f = mapping_raw_data->current();

    //Updates the position of the agents circles
    f->first();
    do{
        updateAgent(f->current());
    }while(f->next());

    //Emite um tick, ou seja, o avanço para a próxima frame
    if(timer->isActive())
        emit tick(f->t);

    at_the_end=false;
    //Para o timer quando não há mais frames
    if(!mapping_raw_data->next()){
        timer->stop();
        at_the_end=true;
        mapping_raw_data->first();
    }
}

void SpacialAndTemporalMapWidget::updateAgent(Agent* a){
    Emotion* e = a->getStrongestEmotion();
    QColor c = emotion_to_color_dictionary.value(e->name,Qt::black);

    double alfa = e->intensity*0.7 +0.3;

    QColor c2 = QColor::fromHslF(c.hslHueF(),c.saturationF(),c.lightnessF()+(((1-alfa)/2)));

    QGraphicsItem* item = scene->addEllipse(0,0,agent_elipse_size,agent_elipse_size,QPen(Qt::transparent),c2);
    item->setCursor(Qt::PointingHandCursor);

    qreal x = a->coordinates.x()/(mapping_raw_data->getUpperRight().x()-mapping_raw_data->getLowerLeft().x());
    x*=scene->width();
    qreal y = a->coordinates.y()/(mapping_raw_data->getUpperRight().y()-mapping_raw_data->getLowerLeft().y());
    y = 1 - y;
    y*=scene->height();
    QPointF ccords(x-agent_elipse_size/2,y-agent_elipse_size/2);

    item->setPos(ccords);

    if(n_select_agent==a->n){
        if(current_agent_selected_circle){
            ccords.setX(ccords.x()-2);
            ccords.setY(ccords.y()-2);
            current_agent_selected_circle->setPos(ccords);
        }

        emit adicionalInfoChanged(a);
    }

    scene->removeItem(agents_circles[a->n]);

    agents_circles[a->n] = item;
}

void SpacialAndTemporalMapWidget::objectClickedInScene(QGraphicsItem* item){
    int n = agents_circles.indexOf(item);

    if(n<0)
        return;

    n_select_agent = n;

    if(current_agent_selected_circle)
        scene->removeItem(current_agent_selected_circle);

    current_agent_selected_circle = scene->addEllipse(0,0,agent_elipse_size+4,agent_elipse_size+4,QPen(QBrush(Qt::gray),2.0),QBrush(Qt::transparent));
    QPointF point = agents_circles[n_select_agent]->pos();
    point.setX(point.x()-2);
    point.setY(point.y()-2);
    current_agent_selected_circle->setPos(point);

    if(!at_the_end)
        emit adicionalInfoChanged(mapping_raw_data->current()->agent_list[n]);
    else
        emit adicionalInfoChanged(mapping_raw_data->getLastFrame()->agent_list[n]);
}

void SpacialAndTemporalMapWidget::tooglePlay(){
    if(timer->isActive())
        timer->stop();
    else
        timer->start(timer_intreval);
}

void SpacialAndTemporalMapWidget::stop(){
    timer->stop();
    mapping_raw_data->first();
}

void SpacialAndTemporalMapWidget::seek(qreal f){
    mapping_raw_data->goTo(f);

    if(!timer->isActive()){
        update();
    }
}

qreal SpacialAndTemporalMapWidget::getFrameRate(){
    return 1.0/(timer_intreval/1000.0);
}

void SpacialAndTemporalMapWidget::setFrameRate(int f){
    timer_intreval=(1.0/f)*1000;
}

//O v pode ser no interevalo [0,20] sendo 10 o valor centrar que corresponde ao zoom por defeito
void SpacialAndTemporalMapWidget::setZoom(int v){
    int diff = v - last_zoom_value;

    while(diff>0){
        zoomIn();
        diff--;
    }

    while(diff<0){
        zoomOut();
        diff++;
    }

    last_zoom_value = v;
}

void SpacialAndTemporalMapWidget::zoomIn(){
    view->scale(1.25,1.25);
}

void SpacialAndTemporalMapWidget::zoomOut(){
    view->scale(0.8,0.8);
}

int SpacialAndTemporalMapWidget::getSelectedAgent(){
    return n_select_agent;
}

QColor SpacialAndTemporalMapWidget::getColorForEmotion(QString emotion){
    return emotion_to_color_dictionary.value(emotion,Qt::black);
}

void SpacialAndTemporalMapWidget::exportToImage(){
    QPixmap pixmap(view->size());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    view->render(&painter);

    QFileDialog::Options options;
    QString selectedFilter;

    QString fileName = "";


    fileName = QFileDialog::getSaveFileName(view->nativeParentWidget(), "Export Map", ".", "PNG Files (*.png);;All Files (*)",
                                    &selectedFilter,
                                    options);


    if(fileName.length()==0)
        return;

    QImage image = pixmap.toImage();
    image.save(fileName);
}

bool SpacialAndTemporalMapWidget::isPlaying(){
    return timer->isActive();
}

