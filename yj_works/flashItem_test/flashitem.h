#ifndef FLASHITEM_H
#define FLASHITEM_H
#include<QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
 
class flashitem:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    //bool flash; //这个用来标志重画函数
    flashitem(QString strName);
    ~flashitem();
    QRectF boundingRect() const; //这个函数是vitual必须重新实现，否则所定义的类难以实例化

    //
    void setBackColor(int color);

    //
    QString getName();

Q_SIGNALS:
    void mySignal();

private:
     void timerEvent(QTimerEvent *); //重新实现timeEvent这个函数，定时器的作用
 
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
 
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    //
    int m_color;

    //
    QString m_strName;
};
#endif // FLASHITEM_H
