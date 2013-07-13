#ifndef RSSMODEL_H
#define RSSMODEL_H

#include <QStandardItemModel>
#include <QNetworkAccessManager>
#include <QtXml>
#include <QtCore>
#include <QLinkedList>
#include "util.h"
#include "rssitem.h"
#include "xplrss.h"

class XplRSS;
class RssItem;

class RssModel : public QStandardItemModel
{
	Q_OBJECT
public:
	//RssModel(QObject* parent = NULL);
	explicit RssModel(const QString &url, QSet<QString> readItems = QSet<QString>(), XplRSS *parent = NULL);
	RssModel(XplRSS *parent = 0);
	RssModel(const RssModel& original);
	virtual ~RssModel();
	void markRead(const QModelIndex &index);
	void markRead(RssItem* item, bool value = true);
	QMimeData* mimeData( const QList<QStandardItem *> items ) const;

	void addRef();
	void delRef();
	RssItem* get(int) const;
	Iter<RssItem*> begin() const;
	Iter<RssItem*> end() const;
	virtual void loadUrl(const QString &urlstring = "");
	void pressed(const QModelIndex &index, Qt::MouseButtons button);
	QList<QString> readItems() const;

private:
	int connectionId;
	int _ref;
	QNetworkAccessManager http;
	QXmlStreamReader xml;
	RssItem *_selectedItem;
	QString _filename, _guid, _title, _subtitle, _rssLink, _link, _updated;
	QSet<QString> _readItems;
	XplRSS *_parent;

	void saveFile();
	void loadFile();
	int filter(QString idStr, QDateTime date);
	void parseXml();
	void parseRss2();
	void parseAtom();
	void markPrevRead();
protected:
public:
	ATTR_ACCESSOR(QString, title)
	ATTR_READER(QString, rssLink)
	ATTR_READER(int, ref)
signals:
	void loaded(QStandardItemModel*);
	void parsed(QString);
public slots:
	void requestFinished(QNetworkReply *reply);
};

#endif // RSSMODEL_H
