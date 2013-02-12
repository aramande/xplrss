#include <QtGui>

#include "headeritem.h"

HeaderItem::HeaderItem(QString text)
{
	itemText = text;
}

HeaderItem::~HeaderItem()
{

}

void HeaderItem::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index) const
{
	QRect rect(option.rect.topLeft(), option.rect.bottomRight());

	painter->save();
	painter->setBrush(QColor("#e97726"));
	painter->drawRect(rect);
	painter->restore();
	
	painter->save();
	painter->setPen(QPen(Qt::black, 3));
	painter->drawLine(rect.bottomLeft(), rect.bottomRight());
	painter->restore();

	painter->save();
	painter->setPen(QPen(Qt::black));
	painter->setFont(QFont("Arial", 12));
	painter->drawText(option.rect, Qt::AlignCenter | Qt::TextWordWrap, itemText);
	painter->restore();
}
