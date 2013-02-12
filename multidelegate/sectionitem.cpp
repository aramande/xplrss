#include <QtGui>

#include "sectionitem.h"

SectionItem::SectionItem(QString text)
{
	itemText = text;
}

SectionItem::~SectionItem()
{

}

void SectionItem::paint(QObject *parent, QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index) const
{
	QListWidget *p = (QListWidget*)parent;

	painter->save();
	QTextDocument doc;
	doc.setHtml(itemText);
	QAbstractTextDocumentLayout::PaintContext context;
	doc.setPageSize(QSize(option.rect.size().width(), option.rect.size().height() + p->viewport()->size().height()));
	painter->translate(option.rect.x(), option.rect.y());
	doc.documentLayout()->draw(painter, context);
	painter->restore();
}


QSize SectionItem::sizeHint(QObject *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QListWidget *p = (QListWidget*)parent;
	QFontMetrics fm(p->font());

	float rw = float(p->viewport()->size().width());
	float tw = fm.width(itemText);
	float ratio = tw/rw;
	int lines = int(ratio) + 1;
	return QSize(rw,lines*fm.height());
}
