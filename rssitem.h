#ifndef RSSITEM_H
#define RSSITEM_H

#include <QStandardItem>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QModelIndex>
#include <QListView>
#include <QPainter>
#include <QSize>
#include <QDateTime>
#include "util.h"

class RssItem : public QStandardItem
{
	bool _read, _hidden, _expanded;
	QString _title, _author, _content, _summary, _itemLink, _id;
	QDateTime _date;
public:
	RssItem(const QString &title, const QDateTime &date, const QString &content, const QString &summary, const QString &author, const QString &itemLink, bool read = false, const QString &id = "");
	void setRead(bool value = true);
	void setHidden(bool value);
	void setExpanded(bool value);
	void setText(const QString &title, const QDateTime &date, const QString &content, const QString &summary, const QString &author, const QString itemLink);
	void setText(const QString &junk = "");
	ATTR_READER(const QString&, id)
	ATTR_READER(const QDateTime&, date)
	ATTR_READER(const QString&, title)
	ATTR_READER(const QString&, content)
	ATTR_READER(const QString&, itemLink)
	ATTR_READER(const QString&, summary)
	ATTR_READER(const QString&, author)
	ATTR_READER(bool, read)
	//void paint(QObject* parent, QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const;
	//QSize sizeHint(QObject* parent, const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // RSSITEM_H
