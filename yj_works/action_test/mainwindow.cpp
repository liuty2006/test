#include "mainwindow.h"
#include "flashitem.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDebug>

enum Color {
    color_red,
    color_green
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setFixedSize(800,800);

    // action
    newitemflash = new QAction(tr("newitemflash"),this);
    newtextflash = new QAction(tr("newtextflash"),this);
    QAction *actSave = new QAction(tr("save"),this);
    QAction *actLoad = new QAction(tr("load"),this);
    QAction *actCopy = new QAction(tr("copy"),this);

    // menu
    QMenu *mnuSave;
    QMenu *mnuLoad;
    QMenu *mnuCopy;

    //
    additem = new QMenu(tr("AddItem"),this);
    addtext = new QMenu(tr("AddText"),this);
    mnuSave = new QMenu(tr("Save"),this);
    mnuLoad = new QMenu(tr("Load"),this);
    mnuCopy = new QMenu(tr("Copy"),this);

    //
    additem->addAction(newitemflash);
    addtext->addAction(newtextflash);
    mnuSave->addAction(actSave);
    mnuLoad->addAction(actLoad);
    mnuCopy->addAction(actCopy);

    // menu bar
    menuBar()->addMenu(additem);
    menuBar()->addMenu(addtext);
    menuBar()->addMenu(mnuSave);
    menuBar()->addMenu(mnuLoad);
    menuBar()->addMenu(mnuCopy);

    // scene
    m_scene=new QGraphicsScene;  //定义了一个布局
    m_scene->setSceneRect(-300,-300,300,300);  //定义布局的边界
    m_view=new QGraphicsView;    //定义了一个视图
    m_view->setSceneRect(-300,-300,300,300);

    //
    timer=new QTimer(this); //定义一个定时器

    //
    connect(newitemflash,SIGNAL(triggered()),this,SLOT(additemflash()));
    connect(newtextflash,SIGNAL(triggered()),this,SLOT(addtextflash()));
    connect(actSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(actLoad,SIGNAL(triggered()),this,SLOT(load()));
    connect(actCopy,SIGNAL(triggered()),this,SLOT(copy()));

    //connect(timer,SIGNAL(timeout()),this,SLOT(addtextflash()));

    //
    m_view->setScene(m_scene);
    m_view->show();

    setCentralWidget(m_view);

    //
    m_itemNoSign = NULL;
    m_itemSign = NULL;

    //
    initDataMap();
    initRule();
    initPropertyRule();
}

MainWindow::~MainWindow()
{

}

void MainWindow::additemflash()//定时器的开始，用button控制
{
    //m_itemSign
    m_itemSign = new flashitem("sign");
    m_scene->addItem(m_itemSign);
    m_itemSign->setPos(-100,-100);

    //
    vectItems.push_back(m_itemSign);

    //
    //m_itemSign->setBackColor(0);

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

//int g_color = 0;

//

/*
 Action{
    action = “OnClick”；item_a = “a”；type = “value”； script = “”；“启动测试”= 1； 	- 直接连接
    action = “OnClick”；item_a = “b”；type = “script”；script = “”；“启动测试”= 0,1；	- VBS动作
}
 */

//
std::map<QString, int> g_mapData;

//
void MainWindow::initDataMap()
{
    //
    g_mapData["zero"] = 0;
    g_mapData["one"] = 1;

    //
    int i = g_mapData["one"];
    int ii = g_mapData["two"];
/*
    g_mapData.insert(std::pair<QString, int>("one", 1));
    g_mapData.insert(std::pair<QString, int>("tow", 2));

    std::map<QString, int>::iterator iter;
    for(iter = g_mapData.begin(); iter != g_mapData.end(); iter++){
        qDebug() << iter->first<<' '<<iter->second;
    }

    //
    int i = g_mapData["one"];
    int ii = g_mapData["two"];
*/
}

//
enum RuleAction{
    Action_OnClick,
    Action_RightClick,
};

//
enum RuleType{
    Type_Const,
    Type_Value,
    Type_Script,
};

//
struct ActionRule{
    RuleAction action;
    QString strItemID;
    RuleType type;
    QString strScript;

    //
    QString strSourceValue;
    QString strDestValue;
};

//
std::vector<ActionRule> g_vecRules;

//
void MainWindow::initRule()
{
    ActionRule rule;
    rule.action = Action_OnClick;
    rule.strItemID = "sign";
    rule.type = Type_Value;
    rule.strScript = "";
    rule.strSourceValue = "s";
    rule.strDestValue = "zero";

    //
    g_vecRules.push_back(rule);
}

//
void MainWindow::Check(Item *item)
{
    //
    //g_vecRules[0].strSourceValue

    //
    QString strID =  g_vecRules[0].strItemID;

    //
    //if(item->getID() == "sign"){
    if(item->getID() == strID){
        //
        QString strDestValue =  g_vecRules[0].strDestValue;
        g_mapData[strDestValue] = 1;

        //
        //g_mapData["zero"] = 1;
        //g_color = 1;
        //m_itemNoSign->setBackColor(0);
        //break;
    }
}

//
void MainWindow::Action()
{
    QList<QGraphicsItem *> items = m_scene->items();

    //
    foreach (QGraphicsItem *qitem, items) {
        //
        Item *item = dynamic_cast<Item*>(qitem);


        //
        Check(item);

/*
        //
        if(item->getID() == "sign"){
            g_mapData["zero"] = 1;
            //g_color = 1;
            //m_itemNoSign->setBackColor(0);
            break;
        }
*/
    }

    Property();
}

/*
 Property{
    “启动测试”= 0；item_a = “a”；type = “value”；property = “Backcolor”；value = “Red”				- 值域
    “启动测试”= 1；item_a = “a”；type = “value”；property = “Backcolor”；value = “Green”			- 值域
    “电机测试”= 0；item_b = “b”；type = “value”；property = “Boardcolor”；value = “Red”			- 值域
    “电机测试”= 1；item_b = “b”；type = “value”；property = “Boardcolor”；value = “Green”		- 值域
}
*/

//
enum PropertyAction{
    PropertyAction_Backcolor,
    PropertyAction_Boardcolor,
};

//
struct PropertyRule{
    QString strItemID;
    QString strSourceValue;
    PropertyAction action;
    QString strValue;
};

std::vector<PropertyRule> g_vecPropertyRule;

//
void MainWindow::initPropertyRule()
{
    PropertyRule rule;
    rule.strItemID = "nosign";
    rule.strSourceValue = "zero";
    rule.action = PropertyAction_Backcolor;
    rule.strValue = "green";

    //
    g_vecPropertyRule.push_back(rule);
}

//
void MainWindow::CheckProperty(Item *item)
{
    QString strID =  g_vecPropertyRule[0].strItemID;

    //
    //if(item->getID() == "nosign"){
    if(item->getID() == strID){
        //
        QString strSourceValue =  g_vecPropertyRule[0].strSourceValue;

        //
        int color = g_mapData[strSourceValue];
        //int color = g_mapData["zero"];

        //
        //m_itemNoSign->setBackColor(color);
        item->setBackColor(color);



        //g_color = 1;
        //m_itemNoSign->setBackColor(0);
        //break;
    }
}

void MainWindow::Property()
{
    QList<QGraphicsItem *> items = m_scene->items();

    //
    foreach (QGraphicsItem *qitem, items) {
        //
        Item *item = dynamic_cast<Item*>(qitem);

        //
        CheckProperty(item);
/*
        //
        if(item->getID() == "nosign"){
            //
            int color = g_mapData["zero"];
            m_itemNoSign->setBackColor(color);
            //g_color = 1;
            //m_itemNoSign->setBackColor(0);
            break;
        }
*/
    }

/*
   if(m_itemNoSign != NULL){
       m_itemNoSign->setBackColor(g_color);
   }
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
bool MainWindow::copy()
{
   //
   flashitem *item = new flashitem(m_itemSign);
   m_scene->addItem(item);
   //item->m_color = 0;

   // Item *m_itemSign;
   // flashitem item = flashitem(m_itemSign);
   //flashitem *item = new flashitem(m_itemSign);
   //scene->addItem(m_itemSign);
   //m_itemSign->setPos(-150,-150);


   return true;
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
     Item *item = NULL;

    //
    while (xml.readNextStartElement()) {
        QStringRef str = xml.name();
        if (xml.name() == tr("ellipse")){
            item = new flashitem("ellipse");
            item->loadXml(&xml);
            m_scene->addItem(item);
        }
        if (xml.name() == tr("rect")){
            item = new ItemRect("rect");
            item->loadXml(&xml);
            m_scene->addItem(item);
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
    xml.writeAttribute("width", QString("100"));
    xml.writeAttribute("height",QString("100"));

    //xml.writeAttribute("width", QString("%1").arg(scene()->width()));
    //xml.writeAttribute("height",QString("%1").arg(scene()->height()));

/*
    foreach (QGraphicsItem *item , scene()->items()) {
        AbstractShape * ab = qgraphicsitem_cast<AbstractShape*>(item);
        QGraphicsItemGroup *g = dynamic_cast<QGraphicsItemGroup*>(item->parentItem());
        if ( ab &&!qgraphicsitem_cast<SizeHandleRect*>(ab) && !g ){
            ab->saveToXml(&xml);
        }
    }
*/
    //vectItems
    std::vector<Item *>::iterator iter = vectItems.begin();
    // vector<int>::const_iterator iter=v.begin();
    for(; iter != vectItems.end(); ++iter)
    {
        Item *i = *iter;
        i->saveXml(&xml);
    }

/*
    //
    if(m_itemSign != NULL){
        m_itemSign->saveXml(&xml);
        //m_itemSign->saveXml(&xml);
    }

    //
    //m_itemNoSign
    if(m_itemNoSign != NULL){
        m_itemNoSign->saveXml(&xml);
        //m_itemSign->saveXml(&xml);
    }
*/
    //
    xml.writeEndElement();
    xml.writeEndDocument();

    return true;
}

void MainWindow::addtextflash()
{
    m_itemNoSign = new ItemRect("nosign");
    m_scene->addItem(m_itemNoSign);
    m_itemNoSign->setPos(-100,-100);

    //
    vectItems.push_back(m_itemNoSign);

/*
    // ItemRect
    m_itemNoSign = new ItemRect("nosign");
    scene->addItem(m_itemNoSign);
    m_itemNoSign->setPos(-100,-100);
*/
/*
    //m_itemNoSign
    m_itemNoSign = new flashitem("nosign");
    scene->addItem(m_itemNoSign);
    m_itemNoSign->setPos(-100,-100);

    //
    m_itemNoSign->setBackColor(1);
*/
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
