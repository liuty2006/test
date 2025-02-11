#include "mainwindow.h"
#include "flashitem.h"

#include <QDebug>

enum Color {
    color_red,
    color_green
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //this->setFixedSize(800,800);

    //
    QAction *actNewitem;
    QAction *actNewtext;
    QAction *actNewScene;
    QAction *actSlide0;
    QAction *actSlide1;

    // action
    actNewitem = new QAction(tr("newitemflash"),this);
    actNewtext = new QAction(tr("newtextflash"),this);
    actNewScene = new QAction(tr("newScene"),this);
    actSlide0 = new QAction(tr("Slide0"),this);
    actSlide1 = new QAction(tr("Slide1"),this);

    // menu
    QMenu  *menuitemAdd;
    QMenu  *menuitemaddtext;
    QMenu  *menuitemAddScene;
    QMenu  *menuitemSlide0;
    QMenu  *menuitemSlide1;

    //
    menuitemAdd = new QMenu(tr("AddItem"),this);
    menuitemaddtext = new QMenu(tr("AddText"),this);
    menuitemAddScene = new QMenu(tr("AddScene"),this);
    menuitemSlide0 = new QMenu(tr("Slide0"),this);
    menuitemSlide1 = new QMenu(tr("Slide1"),this);

    //
    menuitemAdd->addAction(actNewitem);
    menuitemaddtext->addAction(actNewtext);
    menuitemAddScene->addAction(actNewScene);
    menuitemSlide0->addAction(actSlide0);
    menuitemSlide1->addAction(actSlide1);

    // menu bar
    menuBar()->addMenu(menuitemAdd);
    menuBar()->addMenu(menuitemaddtext);
    menuBar()->addMenu(menuitemAddScene);
    menuBar()->addMenu(menuitemSlide0);
    menuBar()->addMenu(menuitemSlide1);

    //
    m_scene0 = new DrawScene;  //定义了一个布局
    //m_scene0->setSceneRect(-300,-300,300,300);  //定义布局的边界
    m_scene0->setSceneRect(0,0,800, 600);
    m_scene0->setBackgroundBrush(Qt::darkGray);
    //m_scene0->drawBackground();

    //
    m_view=new MyView;    //定义了一个视图
    //m_view->setSceneRect(-300,-300,300,300);

    //
    m_sceneCur = m_scene0;

    connect(m_view,SIGNAL(positionChanged(int,int)),this,SLOT(positionChanged(int,int)));

    //
    //timer=new QTimer(this); //定义一个定时器

    //
    connect(actNewitem,SIGNAL(triggered()),this,SLOT(additemflash()));
    connect(actNewtext,SIGNAL(triggered()),this,SLOT(addtextflash()));
    connect(actNewScene,SIGNAL(triggered()),this,SLOT(addScene()));
    connect(actSlide0,SIGNAL(triggered()),this,SLOT(slide0()));
    connect(actSlide1,SIGNAL(triggered()),this,SLOT(slide1()));

    //
    //connect(timer,SIGNAL(timeout()),this,SLOT(addtextflash()));
    m_view->setScene(m_sceneCur);
    m_view->show();

    setCentralWidget(m_view);

    //
    m_itemNoSign = NULL;
}

MainWindow::~MainWindow()
{

}

void MainWindow::slide1()
{
    m_sceneCur = m_scene1;

    //
    m_view->setScene(m_sceneCur);
    m_view->show();
}


void MainWindow::slide0()
{
    m_sceneCur = m_scene0;

    //
    m_view->setScene(m_sceneCur);
    m_view->show();
}

//
void MainWindow::addScene()
{
    //m_scene->disconnect();

    //
    //m_scene->disconnect();
    //
    //m_scene-

    //
    m_scene1 = new DrawScene;  //定义了一个布局
    m_scene1->setSceneRect(0,0,800, 600);
    m_scene1->setBackgroundBrush(Qt::darkGray);
    //m_scene1->setSceneRect(-300,-300,300,300);  //定义布局的边界

    //
    m_sceneCur = m_scene1;

    //
    m_view->setScene(m_sceneCur);
    m_view->show();
}

void MainWindow::additemflash()//定时器的开始，用button控制
{
    //m_itemSign
    m_itemSign = new flashitem("Sign");
    m_itemSign->setPos(0,0);
    m_sceneCur->addItem(m_itemSign);
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

void MainWindow::addtextflash()
{
    //m_itemNoSign
    m_itemNoSign = new flashitem("nosign");
    m_sceneCur->addItem(m_itemNoSign);
    m_itemNoSign->setPos(0,0);

    //m_scene->connect()
    //m_scene->disconnect();

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
/*
    Flash=true;
    timer->start(100);
*/
}


void MainWindow::positionChanged(int x, int y)
{
   char buf[255];
   sprintf(buf,"%d,%d",x,y);

   //statusBar()->showMessage(buf);

   qDebug() << "helo";
   qDebug() << "%d,%d" << x << "," << y;
}
