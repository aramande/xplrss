#ifndef FEED_H
#define FEED_H

#include <QtCore>
#include <QtGui>
#include <QStandardItem>
#include "rssmodel.h"
#include "util.h"

class Feed;
class RssModel;

class FeedUtil : public QObject
{
	Q_OBJECT
	public:
		explicit FeedUtil(Feed *feed);
	private:
		Feed *_feed;
	public slots:
		void setTitle(QString title);
	signals:

};

class Feed : public QStandardItem
{
	public:
		explicit Feed(const QString &url, const QString &title = "", const QString &readItems = "", QWidget *parent = 0);
		explicit Feed(const Feed& other);
		~Feed();
		void setText(const QString &text);
		void setData(const QVariant &value, int role);
	private:
		QWidget* _parent;
		RssModel* rssData;
		FeedUtil* feedUtil;
	public:
		ATTR_READER(QWidget*, parent)
};

#endif // FEED_H
