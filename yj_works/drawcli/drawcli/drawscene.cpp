#include "drawscene.h"
#include<QGraphicsSceneMouseEvent>
#include<QGraphicsRectItem>
#include <QDebug>
#include "drawobj.h"
#include <QPainter>

DrawScene::DrawScene(QObject *parent)
    :QGraphicsScene(parent)
{
}

void DrawScene::mouseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    switch( mouseEvent->type() ){
    case QEvent::GraphicsSceneMousePress:
        QGraphicsScene::mousePressEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseMove:
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        break;
    case QEvent::GraphicsSceneMouseRelease:
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        break;
    }
}

void DrawScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter,rect);
    painter->fillRect(sceneRect(),Qt::white);
/*
    if( m_grid ){
        m_grid->paintGrid(painter,sceneRect().toRect());
    }
*/
}

void DrawScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    DrawTool * tool = DrawTool::findTool( DrawTool::c_drawShape );
    if ( tool )
        tool->mousePressEvent(mouseEvent,this);
}

void DrawScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    DrawTool * tool = DrawTool::findTool( DrawTool::c_drawShape );
    if ( tool )
        tool->mouseMoveEvent(mouseEvent,this);
}

void DrawScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    DrawTool * tool = DrawTool::findTool( DrawTool::c_drawShape );
    if ( tool )
        tool->mouseReleaseEvent(mouseEvent,this);
}
