#ifndef MAINWINDOW_H
#define MAINWINDOW_H

//#include <QMainWindow>

#include <QAction>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMenuBar>
#include <QGraphicsEllipseItem>
#include <QMenu>
#include <QMenuBar>
#include <QTime>
#include <QTimer>
#include"flashitem.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QAction *newitemflash;
    QAction *newtextflash;
    QMenu  *additem;
    QMenu  *addtext;
    QGraphicsScene *scene;  //定义一个场景
    QGraphicsView *view; //定义一个视图
    QTimer *timer;
    bool Flash;

    //
    void loadItems( QXmlStreamReader *xml);

public slots:
    void additemflash();
    void addtextflash();
    bool save();
    bool load();

    //
    void newtimer();

    //
    void Action();

    //
    void Property();

private:
    //
    flashitem *m_itemSign;

    //
    flashitem *m_itemNoSign;
};

#endif // MAINWINDOW_H
