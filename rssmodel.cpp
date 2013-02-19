#include "rssmodel.h"
#include "rssitem.h"
#include <QDebug>
#include <QApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QList>
#include <QUrl>
#include <QFile>
#include <time.h>
#include "util.h"

//RssModel::RssModel(QObject *parent) : QStandardItemModel(parent){}

RssModel::RssModel(const QString &url, QObject *parent) : QStandardItemModel(parent){
	QUrl temp(url);
	_filename = QString("%1/.xplrss/cache/%2%3").arg(QDir::homePath(), QString::number(hash(c_str(temp.path()))), temp.host());

	//loadFile();
	loadUrl(url); //will save result to file
	_selectedItem = NULL;
}

void RssModel::saveFile(){
	QFile file(_filename);
	QDir dir;
	if(!dir.exists(QDir::homePath() + "/.xplrss/cache")){
		if(!dir.exists(QDir::homePath() + "/.xplrss")){
			 dir.mkdir(QDir::homePath() + "/.xplrss");
		}
		dir.mkdir(QDir::homePath() + "/.xplrss/cache");
	}
	qDebug() << _filename << _title << _link;
	if(file.open(QFile::WriteOnly | QFile::Text)){
		QXmlStreamWriter out(&file);
		out.writeStartDocument();
		{
			out.writeStartElement("feed");

			out.writeTextElement("title", _title);
			out.writeTextElement("subtitle", _subtitle); //TODO: not implemented

			out.writeStartElement("link");
			out.writeAttribute("rel", "self");
			out.writeCharacters(_rssLink);
			out.writeEndElement();

			out.writeTextElement("link", _link);
			if(_id != "")
				out.writeTextElement("id", _id); //TODO: not implemented
			else
				out.writeTextElement("id", _link);

			out.writeTextElement("updated", _updated); //TODO: be formatted

			for(int i; i<rowCount(); ++i){
				RssItem *it = static_cast<RssItem*>(item(i));
				out.writeStartElement("entry");

				out.writeTextElement("title", it->title());
				out.writeStartElement("link");
				out.writeAttribute("href", it->itemLink());
				out.writeEndElement();
				out.writeTextElement("id", it->id());
				out.writeTextElement("updated", it->date()); //TODO: be formatted
				if(it->summary() != "")
					out.writeTextElement("summary", it->summary());
				if(it->summary() != "")
					out.writeTextElement("content", it->content());

				out.writeStartElement("author");
				out.writeTextElement("name",it->author());
				out.writeEndElement();

				out.writeEndElement();
			}
			out.writeEndElement();
			out.writeEndDocument();
		}
		file.flush();
		file.close();
	}
	else
		qDebug() << file.errorString();
}

void RssModel::loadUrl(const QString &urlstring){
	connect(&http, SIGNAL(finished(QNetworkReply*)),
		this, SLOT(requestFinished(QNetworkReply*)));
	QUrl url(urlstring);
	http.get(QNetworkRequest(url));
}

void RssModel::loadFile(){
	QFile file(_filename);
	if(file.open(QFile::ReadOnly | QFile::Text)){
		xml.addData(file.readAll());
		parseXml();
		//qDebug() << file.readAll();
		file.close();
	}
}

void RssModel::markRead(const QModelIndex &index){
	RssItem* item = static_cast<RssItem*>(this->itemFromIndex(index));
	item->setRead(true);
}

void RssModel::pressed(const QModelIndex &index){
	if(!index.isValid()) return;
	Qt::MouseButtons mouse = QApplication::mouseButtons();
	RssItem* item = static_cast<RssItem*>(itemFromIndex(index));
	if((mouse & Qt::LeftButton) == Qt::LeftButton){
		if(_selectedItem != NULL){
			_selectedItem->setHidden(true);
			_selectedItem->setExpanded(false);
		}
		item->setRead(true);
		item->setExpanded(true);
		item->setHidden(false);
		_selectedItem = item;
	}
	qDebug() << index << mouse;
}

void RssModel::requestFinished(QNetworkReply *reply){
	if(reply->size() == 0 ){
		qDebug() << "Content empty";
		return;
	}
	xml.addData(reply->readAll());
	parseXml();
	saveFile();
	emit(loaded());
}

void RssModel::parseXml(){
	while(!xml.atEnd()) {
		xml.readNext();
		if (xml.isStartElement()) {
			if(xml.name() == "rss" && xml.attributes().value("version") == "2.0"){
				parseRss2();
			}
			else if(xml.name() == "feed"){
				parseAtom();
			}
			else{
				qDebug() << "Couldn't figure out the type of Feed.";
			}
		}
	}
	if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
		qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
		http.deleteLater();
	}
}

// Returns 1 if copy rssitem is found, 2 if a copy with a different date was found, and 0 otherwise.
int RssModel::filter(QString id, QString date){
	for(int i=0; i<rowCount(); ++i){
		RssItem *temp = static_cast<RssItem*>(item(i));
		if(temp->id() == id){
			if(temp->date() != date){
				return 2;
			}
			return 1;
		}
	}
	return 0;
}

void RssModel::parseRss2(){
	QString currentTag;
	QString link;
	QString content;
	QString title;
	QString date;
	QString id;

	while (!xml.atEnd()) {
		xml.readNext();
		if (xml.isStartElement()) {
			if(xml.name() == "item"){
				if (title!="" && _title == "" && _link == ""){
					_title = title;
					_link = link;
				}
				link.clear();
				title.clear();
				date.clear();
				id.clear();
				content.clear();
			 }

			 currentTag = xml.name().toString();
		} else if (xml.isEndElement()) {
			if (xml.name() == "item" && link != "") {
				if(!filter(id, date)){
					//struct tm tm;
					//time_t t;
					//strptime(c_str(date), "%d %b %Y %H:%M:%S", &tm) == NULL
					QString tz = date.split(' ')[5];
					QString hour;
					hour = QString("%1%2").arg(QString(tz[1]),QString(tz[2]));
					int offset = hour.toInt();
					if(tz[0] == '-') offset *= -1;

					date.chop(date.length()-date.lastIndexOf(' '));
					QDateTime timestamp = QDateTime::fromString(date, "ddd, dd MMM yyyy hh:mm:ss");
					timestamp.setTimeSpec(Qt::UTC);
					timestamp = timestamp.toLocalTime();
					timestamp.addSecs(offset * 3600);
					qDebug() << "Date: " << timestamp.toString() << " tz" << offset;
					RssItem *item = new RssItem(title, date, content, "", "author", link, false, id);
					appendRow(item);
				}

				title.clear();
				link.clear();
				date.clear();
				id.clear();
				content.clear();
			}

		} else if (xml.isCharacters() && !xml.isWhitespace()) {
			 if (currentTag == "title")
				  title += xml.text().toString();
			 else if (currentTag == "link")
				  link += xml.text().toString();
			 else if (currentTag == "pubDate")
				  date += xml.text().toString();
			 else if (currentTag == "guid")
				  id += xml.text().toString();
			 else if (currentTag == "description")
				  content += xml.text().toString();
		}
	}
	if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
		qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
		http.deleteLater();
	}
}

void RssModel::parseAtom(){
	throw QString("To be implemented");

	QString currentTag;
	QString linkString;
	QString contentString;
	QString titleString;
	QString dateString;

	while (!xml.atEnd()) {
		xml.readNext();
		if (xml.isStartElement()) {
			if(xml.name() == "item"){
				if (titleString!="" && _title == "" && _link == ""){
					_title = titleString;
					_link = linkString;
				}
				linkString.clear();
				titleString.clear();
				dateString.clear();
			 }

			 currentTag = xml.name().toString();
		} else if (xml.isEndElement()) {
			if (xml.name() == "item" && linkString != "") {
				RssItem *item = new RssItem(titleString, dateString, contentString, "summary", "author", linkString, false, "");
				appendRow(item);

				titleString.clear();
				linkString.clear();
				dateString.clear();
				contentString.clear();
			}

		} else if (xml.isCharacters() && !xml.isWhitespace()) {
			 if (currentTag == "title")
				  titleString += xml.text().toString();
			 else if (currentTag == "link")
				  linkString += xml.text().toString();
			 else if (currentTag == "pubDate")
				  dateString += xml.text().toString();
			 else if (currentTag == "description")
				  contentString += xml.text().toString();
		}
	}
	if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
		qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
		http.deleteLater();
	}
}
