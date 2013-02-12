#ifndef RSSMODEL_H
#define RSSMODEL_H

#include <QStandardItemModel>
#include <QHttp>
#include <QtXml>
#include <QtCore>
#include "rssitem.h"

class RssModel : public QStandardItemModel
{
	Q_OBJECT

public:
	//RssModel(QObject* parent = NULL);
	explicit RssModel(const QString &url, QObject* parent = NULL);
	void markRead(const QModelIndex &index);

private:
	int connectionId;
	QHttp http;
	QXmlStreamReader xml;
	QString _filename, _id, _title, _subtitle, _rssLink, _link, _updated;
	RssItem *_selectedItem;

	void saveFile();
	void loadUrl(const QString &urlstring);
	void loadFile();
	int filter(QString id, QString date);
	void parseXml();
	void parseRss2();
	void parseAtom();
signals:
	
public slots:
	void pressed(const QModelIndex &index);
	void responseHeaderReceived(const QHttpResponseHeader &header);
	void requestFinished(int id, bool error);
};

uint hash(const char *str);
const char* c_str(QString str1);

#endif // RSSMODEL_H
