#include "clickableqgraphicsscene.h"
#include <QDebug>

ClickableQGraphicsScene::ClickableQGraphicsScene(QObject * parent) : QGraphicsScene(parent){
    mouseTracking=false;
}

ClickableQGraphicsScene::ClickableQGraphicsScene(const QRectF & sceneRect, QObject * parent) : QGraphicsScene(sceneRect,parent)
{
    mouseTracking=false;
}

void ClickableQGraphicsScene::mouseReleaseEvent ( QGraphicsSceneMouseEvent * mouseEvent ){

    QPointF p = mouseEvent->scenePos();

    QGraphicsItem * item = this->itemAt(p);
    if(item!=0){
        emit objectClicked(item);
    }
}

void ClickableQGraphicsScene::mouseMoveEvent ( QGraphicsSceneMouseEvent * mouseEvent ){
    if(mouseTracking){
        mouseEvent->accept();
        emit mouseMoved(mouseEvent->scenePos());
    }
}

void ClickableQGraphicsScene::setMouseTracking(bool b){
    mouseTracking=b;
}
