#ifndef RSSMODEL_H
#define RSSMODEL_H

#include <QStandardItemModel>
#include <QNetworkAccessManager>
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
	QNetworkAccessManager http;
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
	void loaded();
public slots:
	void pressed(const QModelIndex &index);
	void requestFinished(QNetworkReply *reply);
};

#endif // RSSMODEL_H
