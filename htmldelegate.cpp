#include "htmldelegate.h"
#include <QAbstractItemView>
#include <QDebug>
#include <QListView>

HTMLDelegate::HTMLDelegate(QObject *parent) : QStyledItemDelegate(parent){}

void HTMLDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	QStyleOptionViewItemV4 options = option;
	initStyleOption(&options, index);

	QTextDocument doc;
	QAbstractTextDocumentLayout::PaintContext context;
	QRect rect(option.rect.topLeft(), option.rect.bottomRight());

	// Draw background color
	painter->save();
	painter->setBrush(QColor("#F5F5FC"));
	painter->drawRect(rect);
	painter->restore();

	// Write HTML parsed Text
	painter->save();
	doc.setHtml(options.text);
	doc.setPageSize(rect.size());
	painter->translate(rect.x(), rect.y());
	doc.documentLayout()->draw(painter, context);
	painter->restore();

	// Draw divider line
	painter->save();
	painter->setPen(QPen(Qt::darkBlue, 3));
	painter->drawLine(rect.bottomLeft(), rect.bottomRight());
	painter->restore();
}

QSize HTMLDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const
{
	QStyleOptionViewItemV4 options = option;
	initStyleOption(&options, index);
	QTextDocument doc;
	QRect rect(option.rect.topLeft(), option.rect.bottomRight());

	doc.setHtml(options.text);
	doc.setTextWidth(rect.width());
	return QSize(rect.width(), doc.size().height());
}
