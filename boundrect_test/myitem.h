#ifndef MYITEM_H
#define MYITEM_H
#include <QGraphicsItem>
class MyItem : public QGraphicsItem
{
public:
    MyItem();
    QRectF boundingRect()const override;
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)override;
private:
   void drawRectPath(QPainter *painter);

protected:
    void keyPressEvent(QKeyEvent *event)override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event)override;
    QPainterPath shape()const override;//重写shape函数
    // test
private:
   //void drawRectPath(QPainter *painter);//绘制矩形不在使用
   void drawtTriangle(QPainter *painter);//添加绘制三角形
};
#endif // MYITEM_H
