#ifndef CUSTOMITEMDELEGATE_H
#define CUSTOMITEMDELEGATE_H

#include <QObject>
#include <QAbstractItemDelegate>
#include <QStyledItemDelegate>
#include <QItemDelegate>
class CustomItemDelegate : public QItemDelegate
{
    Q_OBJECT
       mutable QModelIndex m_index;
protected slots:
    void onCloseEditor(QWidget* editor);
public:
    explicit CustomItemDelegate(QObject *parent = nullptr);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

signals:

};

#endif // CUSTOMITEMDELEGATE_H
