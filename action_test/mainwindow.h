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

    //
    QGraphicsScene *m_scene;  //定义一个场景
    QGraphicsView *m_view; //定义一个视图
    QTimer *timer;
    bool Flash;

    //
    void loadItems( QXmlStreamReader *xml);

    //
    void initDataMap();

    //
    void initRule();

    //
    void initPropertyRule();

public slots:
    void additemflash();
    void addtextflash();
    bool save();
    bool load();

    //
    bool copy();

    //
    void newtimer();

    //
    void Action();

    //
    void Property();

    //
    void Check(Item *item);
    void CheckProperty(Item *item);
private:
    //
    flashitem *m_itemSign;

    //
    ItemRect *m_itemNoSign;

    std::vector<Item *> vectItems;
};

#endif // MAINWINDOW_H
