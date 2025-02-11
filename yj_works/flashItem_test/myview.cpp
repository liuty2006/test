#include "myview.h"
#include <QKeyEvent>
#include <QDebug>

MyView::MyView()
{
}
/*
//重写承载View控件类的keyPressEvent实现简单缩放
//A缩小,B放大
   switch (event->key()) {
case Qt::Key_A:
    qDebug() <<"A button";
    //view->scale(0.5,0.5); //缩放view才能看到Item变大缩小， 除非Scene已经缩放到比View小 此时Scene应该是在View中部
    scene->setSceneRect(0,0,scene->width()*0.5, scene->height()*0.5);
    break;
case Qt::Key_B:
    qDebug() <<"B button";
    //view->scale(2,2);
    scene->setSceneRect(0,0,scene->width()*2, scene->height()*2);
    break;
default:
    break;
}
 */

//
void MyView::mousePressEvent(QMouseEvent *event)
{
    QPointF pt = mapToScene(event->pos());
    //m_hruler->updatePosition(event->pos());
    //m_vruler->updatePosition(event->pos());
    emit positionChanged( pt.x() , pt.y() );
    QGraphicsView::mousePressEvent(event);
}

//
void MyView::mouseMoveEvent(QMouseEvent *event)
{
    QPointF pt = mapToScene(event->pos());
    //m_hruler->updatePosition(event->pos());
    //m_vruler->updatePosition(event->pos());
    emit positionChanged( pt.x() , pt.y() );
    QGraphicsView::mouseMoveEvent(event);
}

// setSceneRect -- 改变scene大小，产生的影响
// setSceneRect -- 改变view大小，产生的的影响
void MyView::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_A:
     //qDebug() <<"A button";

     // 改变view
     this->scale(0.5,0.5); //缩放view才能看到Item变大缩小， 除非Scene已经缩放到比View小 此时Scene应该是在View中部
     //this->sceneRect();
     // 改变scene
     //this->scene()->setSceneRect(0,0,this->scene()->width()*0.5, this->scene()->height()*0.5);
     //this->scene()->setSceneRect(-this->scene()->width()*0.5/2,-this->scene()->height()*0.5/2,this->scene()->width()*0.5, this->scene()->height()*0.5);
     qDebug() << "改变view" <<"sceneRect:" << sceneRect() <<"view rect:" << this->rect();
     break;
    case Qt::Key_B:
     //qDebug() <<"B button";

     // 改变view
     this->scale(2,2);

     // 改变scene
     //this->scene()->setSceneRect(0,0,this->scene()->width()*2, this->scene()->height()*2);
     //this->scene()->setSceneRect(-this->scene()->width(),-this->scene()->height(),this->scene()->width()*2, this->scene()->height()*2);
    qDebug() << "改变view" <<"sceneRect:" << sceneRect() <<"view rect:" << this->rect();
     break;

    case Qt::Key_C:
     //qDebug() <<"A button";

     // 改变view
     //this->scale(0.5,0.5); //缩放view才能看到Item变大缩小， 除非Scene已经缩放到比View小 此时Scene应该是在View中部
     //this->sceneRect();
     // 改变scene
     this->scene()->setSceneRect(0,0,this->scene()->width()*0.5, this->scene()->height()*0.5);
     //this->scene()->setSceneRect(-this->scene()->width()*0.5/2,-this->scene()->height()*0.5/2,this->scene()->width()*0.5, this->scene()->height()*0.5);
    qDebug() << "改变scene" <<"sceneRect:" << sceneRect() <<"view rect:" << this->rect();
     break;
    case Qt::Key_D:
     //qDebug() <<"B button";

     // 改变view
     //this->scale(2,2);

     // 改变scene
     this->scene()->setSceneRect(0,0,this->scene()->width()*2, this->scene()->height()*2);
     //this->scene()->setSceneRect(-this->scene()->width(),-this->scene()->height(),this->scene()->width()*2, this->scene()->height()*2);
    qDebug() << "改变scene" <<"sceneRect:" << sceneRect() <<"view rect:" << this->rect();
     break;
    default:
     break;
    }

    //qDebug() << "改变view" <<"sceneRect:" << sceneRect() <<"view rect:" << this->rect();

    QGraphicsView::keyPressEvent(event);
}
