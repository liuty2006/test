#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include "customitemdelegate.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QTableView m_view;
       QStandardItemModel m_model;
       CustomItemDelegate m_delegate;

       void initView();
       void initModel();
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
