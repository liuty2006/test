#ifndef MYVIEW_H
#define MYVIEW_H
#include <QGraphicsView>

class MyView : public QGraphicsView
{
    Q_OBJECT
public:
    MyView();

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    //
    void keyPressEvent(QKeyEvent *event) override;

signals:
    void positionChanged(int x , int y );
};
#endif // MYVIEW_H
