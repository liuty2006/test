#include "mainwindow.h"
#include <QApplication>
#include "myitem.h"
#include <QGraphicsScene>
#include "myview.h"
#include "drawscene.h"

/*
 * https://blog.csdn.net/weixin_39583140/article/details/93599949
总共有五种模式，很容易理解：
QGraphicsView::FullViewportUpdate 全视口更新，整体都更新的意思啦
QGraphicsView::MinimalViewportUpdate 最小更新，哪里有变动更新哪里
QGraphicsView::SmartViewportUpdate 智能选择，它要自己选
QGraphicsView::BoundingRectViewportUpdate 来了，来了，它就是我们要注意的。
QGraphicsView::NoViewportUpdate 不更新
其中默认为QGraphicsView::MinimalViewportUpdate，也就是上例中我们没有进行设置的情况。事实上除了设置为FullViewportUpdate 其余四种皆会出现问题，不妨试一试。
我们可以通过在MyView的构造函数中设置为FullViewportUpdate 的全视口更新得到我们想要的结果，但是却是以牺牲性能为代价的。
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
/*
    // test

    MyItem *item1=new MyItem;
    MyItem *item2=new MyItem;
    item1->setPos(0,0);
    item2->setPos(150,150);

    //
    DrawScene scene;
    scene.setBackgroundBrush(Qt::darkGray);

    //
    scene.addItem(item1);
    scene.addItem(item2);

    MyView view;
    //view.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view.setScene(&scene);
    view.resize(600,600);
    view.show();

    //
    view.setRenderHint(QPainter::Antialiasing);
    view.setCacheMode(QGraphicsView::CacheBackground);
    view.setOptimizationFlags(QGraphicsView::DontSavePainterState);
    view.setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    //view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view.setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    view.setTransform(view.transform().scale(1,-1));
*/
    return a.exec();
}
