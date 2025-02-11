#ifndef FLASHITEM_H
#define FLASHITEM_H
#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

//
class Item:public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    //bool flash; //这个用来标志重画函数
    Item(){};
    //~Item();

    virtual bool saveXml(QXmlStreamWriter * xml) = 0;
    virtual bool loadXml(QXmlStreamReader * xml) = 0;
};

//
class ItemRect : public Item
{
    Q_OBJECT
public:
    //bool flash; //这个用来标志重画函数
    ItemRect(QString strName){m_strName = strName;};
    //~ItemRect();
    QRectF boundingRect() const; //这个函数是vitual必须重新实现，否则所定义的类难以实例化

    //
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    //
    bool saveXml(QXmlStreamWriter * xml) override;

    //
    bool loadXml(QXmlStreamReader * xml) override;

     QString m_strName;
};

//
class flashitem : public Item
{
    Q_OBJECT
public:
    //bool flash; //这个用来标志重画函数
    flashitem(){};
    flashitem(QString strName);
    flashitem(Item* item);
    flashitem* clone() const { return new flashitem(*this);}


    ~flashitem();
    QRectF boundingRect() const; //这个函数是vitual必须重新实现，否则所定义的类难以实例化

    //
    void setBackColor(int color);

    //
    QString getName();

    //
    bool saveXml(QXmlStreamWriter * xml) override;

    //
    bool loadXml(QXmlStreamReader * xml) override;

private:
    //
    qreal m_fRatioX;
    qreal m_fRatioY;

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
