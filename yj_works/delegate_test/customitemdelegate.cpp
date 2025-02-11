#include "customitemdelegate.h"

#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>
#include <QTextEdit>
CustomItemDelegate::CustomItemDelegate(QObject *parent) : QItemDelegate(parent)
{
    connect(this, SIGNAL(closeEditor(QWidget*)), this, SLOT(onCloseEditor(QWidget*)));
       connect(this, SIGNAL(commitData(QWidget*)), this, SLOT(onCommitData(QWidget*)));

}
QWidget* CustomItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QWidget* ret = NULL;

    m_index = index; // 记录当前被编辑数据项索引

    if( index.data().type() == QVariant::Int )
    {
        qDebug()<<"new QLineEdit";
        // 当前数据项中的数据类型是bool型,创建复选框组件
        QLineEdit* cb = new QLineEdit(parent);

        cb->setText("平方值");

        ret = cb;
    }
    else if( index.data().type() == QVariant::Char )
    {
        // 当前数据项中的数据类型是char型,创建下拉列表框组件
        QComboBox* cb = new QComboBox(parent);

        cb->addItem("A");
        cb->addItem("B");
        cb->addItem("C");
        cb->addItem("D");

        ret = cb;
    }
    else
    {
        // 其它情况，直接使用父类提供的默认创建编辑器组件方式
        ret = QItemDelegate::createEditor(parent, option, index);
    }

    return ret; //返回创建的编辑器组件
}

void CustomItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void CustomItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if( index.data().type() == QVariant::Int)
    {
        QLineEdit* cb = dynamic_cast<QLineEdit*>(editor);
 qDebug()<<"setEditorData";

           // cb->setChecked(index.data().toBool());//设置设置复选框组件被选中
          int a= index.data().toInt();
          int b=a*a;

          cb->setText(QString::number(b));

    }
    else if( index.data().type() == QVariant::Char )
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);

        if( cb != NULL )
        {
            for(int i=0; i<cb->count(); i++)
            {
                if( cb->itemText(i) == index.data().toString() )
                {
                    cb->setCurrentIndex(i);
                    break;
                }
            }
        }
    }
    else
    {
        QItemDelegate::setEditorData(editor, index);
    }
}

void CustomItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if( index.data().type() == QVariant::Int )
    {
        QLineEdit* cb = dynamic_cast<QLineEdit*>(editor);
   qDebug()<<"setModelData";


            // 将复选框值(role data )取出，根据索引设置到模型
            model->setData(index, cb->text().toInt(), Qt::DisplayRole);

    }
    else if( index.data().type() == QVariant::Char )
    {
        QComboBox* cb = dynamic_cast<QComboBox*>(editor);

        if( cb != NULL )
        {
            model->setData(index, cb->currentText().at(0), Qt::DisplayRole);
        }
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}



void CustomItemDelegate::onCloseEditor(QWidget*)
{
    m_index = QModelIndex(); // 关闭编辑框时将当前记录的索引清空
}
