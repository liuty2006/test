#include "mainwindow.h"
#include <QStatusBar>


#include "myitem.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    this->setFixedSize(800,800);
   // statusBar()->showMessage("buf");

    MyItem *item1=new MyItem;
    MyItem *item2=new MyItem;
    item1->setPos(0,0);
    item2->setPos(150,150);

    //
    //DrawScene scene;
    m_scene = new DrawScene;  //定义了一个布局
    m_scene->setBackgroundBrush(Qt::darkGray);

    //
    m_scene->addItem(item1);
    m_scene->addItem(item2);

    //MyView view;
    m_view = new MyView;
    //view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    m_view->setScene(m_scene);
    m_view->resize(800,600);
    //view.show();
    //view.update();

    //
    connect(m_view,SIGNAL(positionChanged(int,int)),this,SLOT(positionChanged(int,int)));

    // scene 位于view的左上角
    m_view->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // 场景出现在view的最上方
    m_view->centerOn(0,0);

    //view的滚动条隐藏
    //m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //
    m_scene->update();
    m_view->update();
    m_view->show();

    //
    m_view->setRenderHint(QPainter::Antialiasing);
    m_view->setCacheMode(QGraphicsView::CacheBackground);
    m_view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
    m_view->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    m_view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);


    //
    //m_view->setTransform(m_view->transform().scale(1,-1));

    //
    m_scene->setSceneRect(0,0,800, 600);
    //m_scene->setSceneRect(-400,-300,800, 600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::positionChanged(int x, int y)
{
   char buf[255];
   sprintf(buf,"%d,%d",x,y);

   //statusBar()->showMessage(buf);

   qDebug() << "helo";
   qDebug() << "%d,%d" << x << "," << y;
}
