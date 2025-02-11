#ifndef DRAWOBJ
#define DRAWOBJ

#include <qgraphicsitem.h>
#include <QGraphicsSceneMouseEvent>
#include "drawtool.h"
#include "sizehandle.h"

class GraphicsItem : public QAbstractGraphicsShapeItem
{
public:
    GraphicsItem(QGraphicsItem * parent );
    enum {Type = UserType+1};
    int  type() const { return Type; }
    SizeHandleRect::Direction  hitTest( const QPointF & point ) const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
    virtual QPointF origin () const { return QPointF(0,0); }
    virtual Qt::CursorShape getCursor(SizeHandleRect::Direction dir );
    virtual QRectF  rect() const { return QRectF(0,0,0,0);}
protected:
    virtual void updateGeometry();
    void setState(SelectionHandleState st);
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
    typedef QVector<SizeHandleRect*> Handles;
    Handles m_handles;

};


class GraphicsRectItem : public GraphicsItem
{
public:
    GraphicsRectItem(const QRect & rect ,QGraphicsItem * parent);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
     virtual QRectF  rect() const { return QRectF(-m_width / 2 , -m_height / 2 , m_width,m_height) ;}
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
protected:
    qreal m_width;
    qreal m_height;
};

class GraphicsItemGroup : public GraphicsRectItem
{
public:
    GraphicsItemGroup ( QGraphicsItemGroup * group, QGraphicsItem * parent );
    QRectF boundingRect() const;
    QPainterPath shape() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QGraphicsItemGroup *m_group;
};

class GraphicsEllipseItem : public GraphicsRectItem
{
public:
    GraphicsEllipseItem(const QRect & rect ,QGraphicsItem * parent);
    QPainterPath shape() const;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

class GraphicsLineItem : public GraphicsRectItem
{
public:
    GraphicsLineItem(QGraphicsItem * parent );
    QPainterPath shape() const;
    virtual void resizeTo(SizeHandleRect::Direction dir, const QPointF & point );
protected:

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // DRAWOBJ
