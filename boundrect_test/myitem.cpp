#include "myitem.h"
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

MyItem::MyItem()
{
    // 注释
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsFocusable);
}
QRectF MyItem::boundingRect()const {
    qreal penwidth=1;
    return QRectF(-50-penwidth/2,-50-penwidth/2,100+penwidth,100+penwidth);
}
void MyItem::drawRectPath(QPainter *painter){
    QPainterPath rectPath;
    rectPath.moveTo(-50,-50);
    rectPath.lineTo(50,-50);
    rectPath.lineTo(50,50);
    rectPath.lineTo(-50,50);
    rectPath.closeSubpath();//返回绘图开始点

    painter->setPen(QPen(Qt::red,20,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin));//pen参数别设置错了，要不不好看出来
    painter->drawPath(rectPath);

    //在之前的绘图上我们绘制出QboundingRect的虚线方框
    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawRect(-50,-50,100,100);
}
void MyItem::paint(QPainter *painter
                   ,const QStyleOptionGraphicsItem *,QWidget *){
qDebug() << "****"<< this->pos();
    //
    //drawRectPath(painter);

    //绘制boundingRect的QRect以方便查看
    painter->setPen(QPen(Qt::black,1,Qt::DotLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawRect(-50,-50,100,100);

    if(hasFocus()&&!collidingItems().isEmpty()){  //判断是否有在获得焦点的同时有碰撞
        qDebug() << "================================" << this->pos();
       painter->setBrush(QColor(Qt::black));     //若有碰撞则绘制的图形将以黑色作为画刷填充
    }
    drawtTriangle(painter);//这次是三角形
}


//上下左右移动图形项
void MyItem::keyPressEvent(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left:{
        moveBy(-1,0);
        break;
    }

    case Qt::Key_Up:{
        moveBy(0,-1);
        break;
    }
    case Qt::Key_Right:{
        moveBy(1,0);
        break;
    }
    case Qt::Key_Down:{
        moveBy(0,1);
        break;
    }
    }
}
//鼠标点击获得焦点
void MyItem::mousePressEvent(QGraphicsSceneMouseEvent *){
    setFocus();
}

void MyItem::drawtTriangle(QPainter *painter){
    QPainterPath trianglePath;
    trianglePath.moveTo(0,-50);
    trianglePath.lineTo(50,50);
    trianglePath.lineTo(-50,50);
    trianglePath.closeSubpath();
    painter->setPen(QPen(Qt::red,1,Qt::SolidLine,Qt::SquareCap,Qt::MiterJoin));
    painter->drawPath(trianglePath);
}

QPainterPath MyItem::shape()const{    //shape()函数返回一个一样的三角形路径
    QPainterPath trianglePath;
    trianglePath.moveTo(0,-50);
    trianglePath.lineTo(50,50);
    trianglePath.lineTo(-50,50);
    trianglePath.closeSubpath();
    return trianglePath;
}
