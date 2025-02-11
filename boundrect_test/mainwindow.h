#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "drawscene.h"
#include "myview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    //
    DrawScene *m_scene;

    //
    MyView *m_view;

public slots:
    void positionChanged(int x, int y );
};

#endif // MAINWINDOW_H
