#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>

#include <QAction>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QGraphicsEllipseItem>
#include<QMenu>
#include<QMenuBar>
#include<QTime>
#include<QTimer>
#include"flashitem.h"

#include "drawscene.h"
#include "myview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //
    MyView *m_view; //定义一个视图

    //
    DrawScene *m_scene0;  //定义一个场景
    DrawScene *m_scene1;  //定义一个场景

    //
    DrawScene *m_sceneCur;  //定义一个场景

    //
    //QTimer *timer;
    //bool Flash;

public slots:
    void positionChanged(int x, int y );

public slots:
    void additemflash();
    void addtextflash();

    //
    void addScene();

    //
    void newtimer();

    //
    void Action();

    //
    void Property();

    //
    void slide0();

    //
    void slide1();

private:
    //
    flashitem *m_itemSign;

    //
    flashitem *m_itemNoSign;
};

#endif // MAINWINDOW_H
