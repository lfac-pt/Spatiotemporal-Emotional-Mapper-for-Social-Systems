#include "dataplot.h"


#include <QDebug>


DataPlot::DataPlot(QString plot_name, qreal max_yy, qreal max_xx, QString yyLabel,  QWidget *parent):
    QWidget(parent)
{

    setMouseTracking(true);

    this->max_xx=max_xx;
    this->max_yy=max_yy;

    QHBoxLayout * layout = new QHBoxLayout();
    this->setLayout(layout);
    scene = new ClickableQGraphicsScene(this);
    scene->setMouseTracking(true);

    connect(scene,SIGNAL(mouseMoved(QPointF)),SLOT(mouseMovedInScene(QPointF)));

    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QVBoxLayout * v_layout = new QVBoxLayout();

    layout->addLayout(v_layout);

    QPushButton* btn = new QPushButton("Export");
    btn->setMaximumSize(55,25);
    v_layout->addWidget(btn,0,Qt::AlignTop);
    connect(btn,SIGNAL(clicked()),SLOT(exportToImage()));

    btn = new QPushButton("Show all");
    btn->setMaximumSize(55,25);
    v_layout->addWidget(btn,0,Qt::AlignTop);
    connect(btn,SIGNAL(clicked()),SLOT(showAllInds()));

    btn = new QPushButton("Zoom in");
    btn->setMaximumSize(55,25);
    v_layout->addWidget(btn,0,Qt::AlignTop);
    connect(btn,SIGNAL(clicked()),SLOT(zoomIn()));

    btn = new QPushButton("Zoom out");
    btn->setMaximumSize(55,25);
    v_layout->addWidget(btn,0,Qt::AlignTop);
    connect(btn,SIGNAL(clicked()),SLOT(zoomOut()));

    currentCoordXLabel = new QLabel("x: 0");
    v_layout->addWidget(currentCoordXLabel,0,Qt::AlignTop);

    currentCoordYLabel = new QLabel("y: 0");
    v_layout->addWidget(currentCoordYLabel,0,Qt::AlignTop);

    v_layout->addSpacing(330);

    view->setRenderHint(QPainter::Antialiasing);
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    view->setCursor(Qt::CrossCursor);

    //Offsets para os labels dos eixos
    x_offset = y_offset = 20;

    //Tamanho real do plot
    plot_height = height()-y_offset;
    plot_width = width()-x_offset;

    //Inicializa a lista de cores disponíveis
    available_class_colors.append(Qt::red);
    available_class_colors.append(Qt::blue);
    available_class_colors.append(Qt::green);
    available_class_colors.append(Qt::yellow);
    available_class_colors.append(Qt::cyan);
    available_class_colors.append(Qt::magenta);
    available_class_colors.append(QColor(122,27,224));
    available_class_colors.append(Qt::lightGray);
    available_class_colors.append(Qt::darkBlue);
    available_class_colors.append(Qt::darkGray);
    available_class_colors.append(Qt::darkRed);
    available_class_colors.append(Qt::darkGreen);
    available_class_colors.append(Qt::darkMagenta);
    available_class_colors.append(Qt::darkCyan);
    available_class_colors.append(Qt::darkYellow);
    available_class_colors_for_line = available_class_colors;

    //Inicializa a lista de indices yy disponíveis para séries sem coordenada do y
    for(qreal i=0.05;i<=1.0;i+=0.05)
        availabel_yy_inds.append(i);

    QGraphicsTextItem * t_item;

    title_text_item = scene->addText(plot_name);
    title_text_item->setPos(width()/2,-10);

    if(yyLabel.length()>0){
        t_item = scene->addText(QString().number(max_yy));
        t_item->setPos(0,y_offset-10);
    }

    t_item = scene->addText(QString().number(max_xx));
    t_item->setPos(width()-x_offset+10,height()-y_offset);

    t_item = scene->addText("Seconds");
    t_item->setPos(width()/2,height()-y_offset);

    t_item = scene->addText(yyLabel);
    t_item->setPos(0,height()/2);
    t_item->setRotation(-90);

    t_item = scene->addText(QString().number(0));
    t_item->setPos(0,height()-y_offset);

    scene->addLine(x_offset,y_offset,x_offset,plot_height,QPen(QBrush(Qt::black),2));
    scene->addLine(x_offset,plot_height,width(),plot_height,QPen(QBrush(Qt::black),2));

    setWindowTitle(plot_name);

    class_labels_offset=0;

    current_progressive_show_ind=-1;

    initial_width = width();
    initial_height = height();

    this->yyLabel=yyLabel;
}

void DataPlot::showAllInds(){
    int biggest=-1;
    for (int i=0;i<incomplete_series.size();i++)
        if(incomplete_series[i]->size()>=biggest)
            biggest = incomplete_series[i]->size();

    showInd(biggest-1);
}

void DataPlot::exportToImage(){
    QPixmap pixmap(view->size());
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);
    view->render(&painter);

    QFileDialog::Options options;
    QString selectedFilter;

    QString fileName = "";


    fileName = QFileDialog::getSaveFileName(this, "Export Plot", ".", "PNG Files (*.png);;All Files (*)",
                                    &selectedFilter,
                                    options);


    if(fileName.length()==0)
        return;

    QImage image = pixmap.toImage();
    image.save(fileName);
}

void DataPlot::addPointSeries(QList<QPointF*>* v,QString series_name, QColor color, bool progressive_show){
    if(!available_class_colors.contains(color)&&available_class_colors.size()>0)
        color = available_class_colors.at(0);

    available_class_colors.removeOne(color);

    if(!progressive_show){
        for(int i=0;i<v->length();i++)
            paintPoint(i,color,v);
    }
    else{
        incomplete_series.append(v);
        incomplete_series_colors.append(color);
        incomplete_series_isPointSeries.append(true);

        if(current_progressive_show_ind>=0)
            for(int i=0;i<=current_progressive_show_ind && i<v->size();i++)
                paintPoint(i,color,v);
    }


    QGraphicsTextItem *t_item = scene->addText(series_name);
    t_item->setPos(initial_width+40,(initial_height/2)-(40-class_labels_offset));
    QGraphicsItem* item = scene->addEllipse(0,0,3,3,QPen(color),QBrush(color));
    item->setPos(initial_width+35,(initial_height/2)-(30-class_labels_offset));

    class_labels_offset+=15;
}

void DataPlot::addLineSeries(QList<QPointF*>* v,QString series_name, QColor color, bool progressive_show){
    if(!available_class_colors_for_line.contains(color)&&available_class_colors_for_line.size()>0)
        color = available_class_colors_for_line.at(0);

    available_class_colors_for_line.removeOne(color);

    if(!progressive_show){
        for(int i=1;i<v->length();i++)
            paintLineSeg(i,color,v);
    }
    else{
        incomplete_series.append(v);
        incomplete_series_colors.append(color);
        incomplete_series_isPointSeries.append(false);

        if(current_progressive_show_ind>=0)
            for(int i=1;i<=current_progressive_show_ind && i<v->size();i++)
                paintLineSeg(i,color,v);
    }


    QGraphicsTextItem *t_item = scene->addText(series_name);
    t_item->setPos(initial_width+40,(initial_height/2)-(40-class_labels_offset));
    scene->addLine(QLineF(QPointF(initial_width+33,(initial_height/2)-(28-class_labels_offset)),QPointF(initial_width+37,(initial_height/2)-(28-class_labels_offset))),QPen(QBrush(color),3.0));

    class_labels_offset+=15;
}

void DataPlot::paintLineSeg(int i, QColor color, QList<QPointF*>*v){
    if(i==0)
        return;

    QPointF original = *v->at(i);

    qreal x = (v->at(v->length()-1)->x())!=0 ? original.x()/(v->at(v->length()-1)->x()) : 0;
    x*=plot_width;
    x+=x_offset;
    qreal y = 1 - original.y();
    y*=(plot_height-y_offset);
    y+=y_offset;
    QPointF ccords(x,y);

    QPointF last = *v->at(i-1);

    if((last.x()+1)==original.x()){
        x = (v->at(v->length()-1)->x())!=0 ? last.x()/(v->at(v->length()-1)->x()) : 0;
        x*=plot_width;
        x+=x_offset;
        y = 1 - last.y();
        y*=(plot_height-y_offset);
        y+=y_offset;
        QPointF last_ccords(x,y);

        QBrush brush(color);
        QPen pen(brush,3.0);
        pen.setCapStyle(Qt::FlatCap);


        scene->addLine(QLineF(last_ccords,ccords),pen);
    }
}

void DataPlot::paintPoint(int i, QColor color, QList<QPointF*>*v){
    QPointF original = *v->at(i);
    qreal size = calcDotSize(v->size());

    QGraphicsItem* item = scene->addEllipse(0,0,size,size,QPen(color),QBrush(color));

    qreal x = (v->at(v->length()-1)->x())!=0 ? original.x()/(v->at(v->length()-1)->x()) : 0;
    x*=plot_width;
    x+=x_offset;
    qreal y = 1 - original.y();
    y*=(plot_height-y_offset);
    y+=y_offset;
    QPointF ccords(x-size/2,y-size/2);

    item->setPos(ccords);
}

//Das séries com a opção de progressive_show mostra o ponto no indice ind, se existir
void DataPlot::showInd(int ind){
    if(ind > current_progressive_show_ind){

        //Este for trata do caso em que se avança mais que um indice de uma vez
        for(int j=current_progressive_show_ind+1;j<=ind;j++){
            //Percorre as séries incompletas
            for (int i=0;i<incomplete_series.size();i++){
                QList<QPointF*>*v = incomplete_series[i];

                if(j < v->size()){
                    //É uma série do tipo pontos
                    if(incomplete_series_isPointSeries[i]){
                        paintPoint(j,incomplete_series_colors[i],v);
                    }
                    else{//É uma série do tipo linha
                        paintLineSeg(j,incomplete_series_colors[i],v);
                    }
                }
            }
        }

        current_progressive_show_ind=ind;
    }
}

DataPlot::~DataPlot(){

}

void DataPlot::zoomIn(){
    view->scale(1.25,1.25);
}

void DataPlot::zoomOut(){
    view->scale(0.8,0.8);
}

void DataPlot::setTitle(QString s){
    scene->removeItem(title_text_item);
    title_text_item = scene->addText(s);
    title_text_item->setPos(initial_width/2,-10);
}

void DataPlot::closeEvent ( QCloseEvent * event ){
    deleteLater();
}

void DataPlot::mouseMovedInScene(QPointF point){
    qreal x = point.x();
    x-=x_offset;
    x/=plot_width;
    x *= max_xx;

    qreal y = point.y();
    y-=y_offset;
    y/=(plot_height-y_offset);
    y = 1 - y;

    if(y>1 || x>max_xx)
        return;

    currentCoordXLabel->setText("x: "+QString().number(x).left(6));
    currentCoordYLabel->setText("y: "+QString().number(y).left(6));
}

qreal DataPlot::getUnusedYInd(){
    if(!availabel_yy_inds.isEmpty()){
        availabel_yy_inds.removeFirst();
        return availabel_yy_inds[0];
    }
    else
        return 1.0;
}

void DataPlot::ensureYLabels(){
    if(yyLabel.length()==0){
        QGraphicsTextItem * t_item = scene->addText("Intensity");
        t_item->setPos(0,initial_height/2);
        t_item->setRotation(-90);

        t_item = scene->addText(QString().number(max_yy));
        t_item->setPos(0,y_offset-10);
    }
}

qreal DataPlot::calcDotSize(int len){
    return len > 400 ? 1 : len > 50 ? (((400.0-len)/400.0) * 5.0) + 1.0 : 8;
}




