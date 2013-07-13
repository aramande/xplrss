#ifndef HTMLDELEGATE_H
#define HTMLDELEGATE_H

#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>
#include <QModelIndex>
#include <QPainter>
#include <QSize>

#include "util.h"

class HTMLDelegate : public QStyledItemDelegate
{
	Q_OBJECT
private:
public:
	explicit HTMLDelegate(QObject *parent = 0);
protected:
	 void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
	 QSize sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const;
signals:
	
public slots:
	
};

#endif // HTMLDELEGATE_H
