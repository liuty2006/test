#include "mainwindow.h"
#include "flashitem.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

enum Color {
    color_red,
    color_green
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,800);

    QStringList header ;
    header<<tr("名称")<<tr("数据类型")<<tr("长度")<<tr("连接")<<tr("地址")<<QString("组 ");
    //header<<tr("名称")<<tr("数据类型")<<tr("长度")<<tr("连接")<<tr("组")<<tr("地址");

    // action
    newitemflash = new QAction(tr("newitemflash"),this);
    //newitemflash = new QAction(QString("新建"),this);
    //newitemflash = new QAction("新建",this);
    newtextflash = new QAction(tr("newtextflash"),this);
    QAction *actSave = new QAction(tr("save"),this);
    QAction *actLoad = new QAction(tr("load"),this);

    // menu
    QMenu *mnuSave;
    QMenu *mnuLoad;

    //
    additem = new QMenu(tr("AddItem"),this);
    addtext = new QMenu(tr("AddText"),this);
    mnuSave = new QMenu(tr("Save"),this);
    mnuLoad = new QMenu(tr("Load"),this);

    //
    additem->addAction(newitemflash);
    addtext->addAction(newtextflash);
    mnuSave->addAction(actSave);
    mnuLoad->addAction(actLoad);

    // menu bar
    menuBar()->addMenu(additem);
    menuBar()->addMenu(addtext);
    menuBar()->addMenu(mnuSave);
    menuBar()->addMenu(mnuLoad);

    // scene
    scene=new QGraphicsScene;  //定义了一个布局
    //scene->setSceneRect(-300,-300,300,300);  //定义布局的边界
    scene->setSceneRect(0,0,30,30);  //定义布局的边界
    view=new QGraphicsView;    //定义了一个视图
   // view->setSceneRect(-300,-300,300,300);
    view->setSceneRect(0,0,300,300);

    //
    timer=new QTimer(this); //定义一个定时器

    //
    connect(newitemflash,SIGNAL(triggered()),this,SLOT(additemflash()));
    connect(newtextflash,SIGNAL(triggered()),this,SLOT(addtextflash()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(actLoad,SIGNAL(triggered()),this,SLOT(load()));

    //connect(timer,SIGNAL(timeout()),this,SLOT(addtextflash()));

    //
    view->setScene(scene);
    view->show();

    setCentralWidget(view);

    //
    m_itemNoSign = NULL;
    m_itemSign = NULL;
}

MainWindow::~MainWindow()
{

}

void MainWindow::additemflash()//定时器的开始，用button控制
{
    //m_itemSign
    m_itemSign = new flashitem("Sign");

    //
    m_itemSign->setPos(0,0);

    //
    scene->addItem(m_itemSign);
    //m_itemSign->setPos(-100,-100);

    //
    m_itemSign->setBackColor(0);

    //
    connect(m_itemSign,SIGNAL(mySignal()),this,SLOT(Action()));

/*
    flashitem *item1=new flashitem;
    scene->addItem(item1);
    item1->setPos(-100,-100);

    //
    item1->setBackColor(0);

    //
    connect(item1,SIGNAL(mySignal()),this,SLOT(Action()));
*/
/*    flashitem *item2=new flashitem;
    scene->addItem(item2);
    item2->setPos(100,100);
*/
/*
    flashitem *item1=new flashitem;
    scene->addItem(item1);
    item1->setPos(-100,-100);
*/
}

int g_color = 0;

//
void MainWindow::Property()
{
    if(m_itemNoSign != NULL){
        m_itemNoSign->setBackColor(g_color);
    }
}
/*
 Action{
    action = “OnClick”；item_a = “a”；type = “value”； script = “”；“启动测试”= 1； 	- 直接连接
    action = “OnClick”；item_a = “b”；type = “script”；script = “”；“启动测试”= 0,1；	- VBS动作
}
 */
//
void MainWindow::Action()
{
    //
    if(m_itemNoSign != NULL){
        g_color = 0;
        //m_itemNoSign->setBackColor(0);
    }

    Property();

/*
    QFont font("Times",20);
    QGraphicsTextItem *item = new QGraphicsTextItem("http://blog.csdn.net/zycxnanwang");
    item->setFont(font);
    item->setFlag(QGraphicsItem::ItemIsMovable); //可以移动
    QColor A;
    if(Flash==true)
    A.setBlue(200);
    else A.setGreen(200);
    item->setDefaultTextColor(A);
    scene->addItem(item);
    item->setPos(-470,50);
    Flash=!Flash;
*/
}

//
void MainWindow::loadItems( QXmlStreamReader *xml)
{
    Q_ASSERT(xml->isStartElement() && xml->name() == "canvas");

    //
    flashitem * item = NULL;
    item = new flashitem("test");
    if (item){
        //
        item->loadXml(xml);
    }

/*
    while (xml->readNextStartElement()) {
        AbstractShape * item = NULL;
        if (xml->name() == tr("rect")){
            item = new GraphicsRectItem(QRect(0,0,1,1));
        }else if (xml->name() == tr("roundrect")){
            item = new GraphicsRectItem(QRect(0,0,1,1),true);
        }else if (xml->name() == tr("ellipse"))
            item = new GraphicsEllipseItem(QRect(0,0,1,1));
        else if (xml->name()==tr("polygon"))
            item = new GraphicsPolygonItem();
        else if ( xml->name()==tr("bezier"))
            item = new GraphicsBezier();
        else if ( xml->name() == tr("polyline"))
            item = new GraphicsBezier(false);
        else if ( xml->name() == tr("line"))
            item = new GraphicsLineItem();
        else if ( xml->name() == tr("group"))
            item =qgraphicsitem_cast<AbstractShape*>(loadGroupFromXML(xml));
        else
            xml->skipCurrentElement();

        if (item && item->loadFromXml(xml))
            scene()->addItem(item);
        else if ( item )
            delete item;
    }
*/
}

//
bool MainWindow::load()
{
    QString fileName = "d:\\test.xml";
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
/*
        QMessageBox::warning(this, tr("Qt Drawing"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
*/
        return false;
    }

    //
    QXmlStreamReader xml(&file);
    if (xml.readNextStartElement()) {
        if ( xml.name() == tr("canvas"))
        {
            int width = xml.attributes().value(tr("width")).toInt();
            int height = xml.attributes().value(tr("height")).toInt();
            //scene()->setSceneRect(0,0,width,height);
            //loadCanvas(&xml);
        }
    }

    //Q_ASSERT(xml->isStartElement() && xml->name() == "canvas");
    Q_ASSERT(xml.isStartElement() && xml.name() == "canvas");

    //
    flashitem *item = NULL;

    //
    while (xml.readNextStartElement()) {
        QStringRef str = xml.name();
        if (xml.name() == tr("ellipse")){
            item = new flashitem("ellipse");
            item->loadXml(&xml);
            scene->addItem(item);
        }
    }
/*
    while (xml->readNextStartElement()) {
        AbstractShape * item = NULL;
        if (xml->name() == tr("rect")){
            item = new GraphicsRectItem(QRect(0,0,1,1));
        }else if (xml->name() == tr("roundrect")){
            item = new GraphicsRectItem(QRect(0,0,1,1),true);
        }else if (xml->name() == tr("ellipse"))
            item = new GraphicsEllipseItem(QRect(0,0,1,1));
        else if (xml->name()==tr("polygon"))
            item = new GraphicsPolygonItem();
        else if ( xml->name()==tr("bezier"))
            item = new GraphicsBezier();
        else if ( xml->name() == tr("polyline"))
            item = new GraphicsBezier(false);
        else if ( xml->name() == tr("line"))
            item = new GraphicsLineItem();
        else if ( xml->name() == tr("group"))
            item =qgraphicsitem_cast<AbstractShape*>(loadGroupFromXML(xml));
        else
            xml->skipCurrentElement();

        if (item && item->loadFromXml(xml))
            scene()->addItem(item);
        else if ( item )
            delete item;
    }
*/
    return true;
}

bool MainWindow::save()
{
    //
    QString fileName = "d:\\test.xml";

    //
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
/*
        QMessageBox::warning(this, tr("Qt Drawing"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));*/
        return false;
    }

    //
    QXmlStreamWriter xml(&file);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeDTD("<!DOCTYPE qdraw>");
    xml.writeStartElement("canvas");
    //xml.writeAttribute("width", QString("100"));
    //xml.writeAttribute("height",QString("100"));

    xml.writeAttribute("width", QString("%1").arg(scene->width()));
    xml.writeAttribute("height",QString("%1").arg(scene->height()));

/*
    foreach (QGraphicsItem *item , scene()->items()) {
        AbstractShape * ab = qgraphicsitem_cast<AbstractShape*>(item);
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if ( ab &&!qgraphicsitem_cast<SizeHandleRect*>(ab) && !g ){
            ab->saveToXml(&xml);
        }
    }
*/

    //
    if(m_itemSign != NULL){
        m_itemSign->saveXml(&xml);
        //m_itemSign->saveXml(&xml);
    }

    //
    xml.writeEndElement();
    xml.writeEndDocument();

    return true;
}

void MainWindow::addtextflash()
{
    //m_itemNoSign
    m_itemNoSign = new flashitem("nosign");
    scene->addItem(m_itemNoSign);
    m_itemNoSign->setPos(-100,-100);

    //
    m_itemNoSign->setBackColor(1);

/*
    flashitem *item1=new flashitem;
    scene->addItem(item1);
    item1->setPos(-100,-100);

    //
    item1->setBackColor(1);

    //
    //connect(item1,SIGNAL(mySignal()),this,SLOT(Action()));
*/

/*
    QFont font("Times",20);
    QGraphicsTextItem *item = new QGraphicsTextItem("http://blog.csdn.net/zycxnanwang");
    item->setFont(font);
    item->setFlag(QGraphicsItem::ItemIsMovable); //可以移动
    QColor A;
    if(Flash==true)
    A.setBlue(200);
    else A.setGreen(200);
    item->setDefaultTextColor(A);
    scene->addItem(item);
    item->setPos(-470,50);
    Flash=!Flash;
*/
}

void MainWindow::newtimer() //启动定时器
{

    Flash=true;
    timer->start(100);
}
