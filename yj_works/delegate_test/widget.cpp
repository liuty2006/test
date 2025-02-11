#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initView();
       initModel();

       m_view.setModel(&m_model);

       for(int i=0; i<m_model.columnCount(); i++)
       {
           m_view.setColumnWidth(i, 125);
       }

}

Widget::~Widget()
{
    delete ui;
}
void Widget::initView(){
    m_view.setParent(this);
       m_view.move(10, 10);
       m_view.resize(500, 200);
       m_view.setItemDelegate(&m_delegate);
}
void Widget::initModel(){
    QStandardItem* root = m_model.invisibleRootItem();
       QStringList hl;
       QStandardItem* itemA1 = new QStandardItem();
       QStandardItem* itemB1 = new QStandardItem();
       QStandardItem* itemC1 = new QStandardItem();
       QStandardItem* itemA2 = new QStandardItem();
       QStandardItem* itemB2 = new QStandardItem();
       QStandardItem* itemC2 = new QStandardItem();

       hl.append("one");
       hl.append("two");
       hl.append("three");

       m_model.setHorizontalHeaderLabels(hl);

       itemA1->setData("First", Qt::DisplayRole);
       itemB1->setData(QChar('A'), Qt::DisplayRole);
       itemC1->setData(10, Qt::DisplayRole);

       itemA2->setData("Second", Qt::DisplayRole);
       itemB2->setData(QChar('B'), Qt::DisplayRole);
       itemC2->setData(20, Qt::DisplayRole);

       root->setChild(0, 0, itemA1);
       root->setChild(0, 1, itemB1);
       root->setChild(0, 2, itemC1);
       root->setChild(1, 0, itemA2);
       root->setChild(1, 1, itemB2);
       root->setChild(1, 2, itemC2);
}
