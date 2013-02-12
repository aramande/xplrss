#include <QtGui>

#include "listwidgetitemdelegate.h"
#include "headeritem.h"
#include "sectionitem.h"

void ListWidgetItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
						 const QModelIndex &index) const
{
	if (qVariantCanConvert<HeaderItem>(index.data()))
	{
		HeaderItem headerItem = qVariantValue<HeaderItem>(index.data());
		headerItem.paint(painter, option, index);
	}
	else if (qVariantCanConvert<SectionItem>(index.data()))
	{
		SectionItem sectionItem = qVariantValue<SectionItem>(index.data());
		sectionItem.paint(parent(), painter, option, index);
	}
	else
	{
		QItemDelegate::paint(painter, option, index);
	}
}


QSize ListWidgetItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
	if (qVariantCanConvert<SectionItem>(index.data())) {
		SectionItem sectionItem = qVariantValue<SectionItem>(index.data());
		return sectionItem.sizeHint(parent(), option, index);
	} else {
		return QItemDelegate::sizeHint(option, index);
	}
}
