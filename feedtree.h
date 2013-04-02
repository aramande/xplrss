#ifndef FEEDTREE_H
#define FEEDTREE_H

#define LINEBUFLEN 1024

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <stack>
#include "branch.h"
#include "feed.h"
#include "xplrss.h"

class XplRSS;
class Feed;

class FeedTree : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit FeedTree(const QString &filename, QObject *parent = 0);
	explicit FeedTree(QObject *parent = 0);
	Qt::DropActions supportedDropActions() const;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	Qt::ItemFlags flags(const QModelIndex &index) const;
	bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole);
	Feed* toFeed(const QString &line);
	Branch* toBranch(const QString &line);
private:
	QString _filename;
	XplRSS *_parent;
	void read();
signals:

public slots:
	void pressed(QModelIndex);
	void update();
};

#endif // FEEDTREE_H
