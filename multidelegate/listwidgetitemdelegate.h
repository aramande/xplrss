#ifndef LISTWIDGETITEMDELEGATE_H
#define LISTWIDGETITEMDELEGATE_H

#include <QItemDelegate>

class ListWidgetItemDelegate : public QItemDelegate
{
	Q_OBJECT

	public:
		ListWidgetItemDelegate(QWidget *parent = 0) : QItemDelegate(parent) {}

		void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

		QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif
