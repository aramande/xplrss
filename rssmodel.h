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

class RssModel : public QStandardItemModel
{
	Q_OBJECT
public:
	//RssModel(QObject* parent = NULL);
		explicit RssModel(const QString &url, QStringList readItems = QStringList(), QWidget* parent = NULL);
	RssModel(const RssModel& original);
	~RssModel();
	void markRead(const QModelIndex &index);
	void operator>>(QDataStream& source);
	QDataStream& operator<<(QDataStream& source);
	QMimeData* mimeData( const QList<QStandardItem *> items ) const;

	void addRef();
	void delRef();

private:
	int connectionId;
	int _ref;
	QNetworkAccessManager http;
	QXmlStreamReader xml;
	RssItem *_selectedItem;
	QString _filename, _guid, _title, _subtitle, _rssLink, _link, _updated;
	QLinkedList<QString> _readItems;
	XplRSS *_parent;

	void saveFile();
	void loadUrl(const QString &urlstring);
	void loadFile();
	int filter(QString idStr, QDateTime date);
	void parseXml();
	void parseRss2();
	void parseAtom();

public:
	ATTR_ACCESSOR(QString, title)
	ATTR_READER(QString, rssLink)
	ATTR_READER(int, ref)
signals:
	void loaded();
	void parsed(QString);
public slots:
	void pressed(const QModelIndex &index);
	void requestFinished(QNetworkReply *reply);
};

#endif // RSSMODEL_H
