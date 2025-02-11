#include"flashitem.h"
 
void flashitem::timerEvent(QTimerEvent *)
{
    //flash=!flash;
    this->update(); //估计重新执行paint这个函数
}
 
 
 
void flashitem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::blue);

    switch(m_color){
    case 0:      //red
        painter->setBrush(Qt::red);
        break;
    case 1:      //red
        painter->setBrush(Qt::green);
        break;
    }

    //painter->setBrush(Qt::red);
    //painter->setBrush(flash?(Qt::red):(Qt::green));
    painter->drawEllipse(-50,-50,100,100);
 
}
 
flashitem::flashitem(QString strName)
{
    setFlag(ItemIsMovable);  //可以移动

    //
    m_color = 0;

    //
    m_strName = strName;
/*
    flash=true;
    setFlag(ItemIsMovable);  //可以移动
    startTimer(100); 
 */
}
 
QRectF flashitem::boundingRect() const  //静态函数
{
 
    return QRectF(-50,-50,100,100);
}

//
void flashitem::setBackColor(int color)
{
    m_color = color;
    this->update();
}

QString flashitem::getName()
{
    return m_strName;
}
 
flashitem::~flashitem()
{
 
}

void flashitem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //flash = flash==false? true:false;
    //this->update();

    //
    //emit scene->itemAdded( item );
    emit this->mySignal();
}
