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
#include <QDataStream>
#include "util.h"

//RssModel::RssModel(QObject *parent) : QStandardItemModel(parent){}

RssModel::RssModel(const QString &url, QStringList readItems, QWidget *parent) : QStandardItemModel(){
	QUrl temp(url);
	_parent = dynamic_cast<XplRSS*>(parent);
	_filename = QString("%1/.xplrss/cache/%2%3.xml").arg(QDir::homePath(), temp.host(), temp.path().split(QRegExp("[^a-z0-9]")).join(""));
	_rssLink = url;
	qRegisterMetaTypeStreamOperators<RssModel*>("RssModel*");
	loadFile();
	loadUrl(url);
	_selectedItem = NULL;
}

RssModel::RssModel(QWidget *parent) : QStandardItemModel(parent){

}

RssModel::RssModel(const RssModel& original) : QStandardItemModel(original.parent()){
	_rssLink = original.rssLink();
	_readItems = QLinkedList<QString>(original._readItems);
	QUrl temp(_rssLink);
	_filename = QString("%1/.xplrss/cache/%2%3.xml").arg(QDir::homePath(), temp.host(), temp.path().split(QRegExp("[^a-z0-9]")).join(""));
	loadUrl(_rssLink);
	_selectedItem = NULL;

}

RssModel::~RssModel(){

}

void RssModel::addRef(){
	++_ref;
}

void RssModel::delRef(){
	--_ref;
}

QDataStream &operator<<(QDataStream &out, RssModel * const &rhs) {
	out.writeRawData(reinterpret_cast<const char*>(&rhs), sizeof(rhs));
	return out;
}

QDataStream &operator>>(QDataStream &in, RssModel *&rhs) {
	in.readRawData(reinterpret_cast<char*>(&rhs), sizeof(rhs));
	return in;
}


RssItem* RssModel::get(int id) const{
	return dynamic_cast<RssItem*>(item(id));
}
Iter<RssItem*> RssModel::begin() const{
	return Iter<RssItem*>(this, 0);
}
Iter<RssItem*> RssModel::end() const{
	return Iter<RssItem*>(this, rowCount());
}

QMimeData* RssModel::mimeData(const QList<QStandardItem *> items ) const
{
	Q_UNUSED(items)
	return new QMimeData();
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
		out.setAutoFormatting(true);
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
			if(_guid != "")
				out.writeTextElement("id", _guid); //TODO: not implemented
			else
				out.writeTextElement("id", _link);

			out.writeTextElement("updated", _updated); //TODO: be formatted

			qDebug() << "I have " << rowCount() << " rows.";
			for(int i; i<rowCount(); ++i){
				RssItem *it = static_cast<RssItem*>(item(i));
				out.writeStartElement("entry");

				out.writeTextElement("title", it->title());
				out.writeStartElement("link");
				out.writeAttribute("href", it->itemLink());
				out.writeEndElement();
				out.writeTextElement("id", it->id());
				out.writeTextElement("updated", it->data(DateRole).toDateTime().toString("yyyy-MM-ddThh:mm:ssZ"));
				if(it->summary() != "")
					out.writeTextElement("summary", it->summary());
				if(it->content() != "")
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
	QUrl url;
	if(urlstring == "") url = _rssLink;
	else url = urlstring;
	http.get(QNetworkRequest(url));
}

void RssModel::loadFile(){
	QFile file(_filename);
	if(file.open(QFile::ReadOnly | QFile::Text)){
		xml.addData(file.readAll());
		parseXml();
		file.close();
		xml.clear();
	}
}

void RssModel::markRead(const QModelIndex &index){
	QStandardItemModel* model = dynamic_cast<QStandardItemModel*>(_parent->feedListView()->model());
	RssItem* item = static_cast<RssItem*>(model->takeItem(index.row()));
	item->setRead(true);
}

void RssModel::pressed(const QModelIndex &index){
	if(!index.isValid()) return;
	auto mouse = QApplication::mouseButtons();
	auto model = dynamic_cast<QSortFilterProxyModel*>(_parent->feedListView()->model());
	auto item = static_cast<RssItem*>(dynamic_cast<QStandardItemModel*>(model->sourceModel())->itemFromIndex(model->mapToSource(index)));
	if(item && mouse & Qt::LeftButton){
		if(_selectedItem != NULL){
			_selectedItem->setHidden(true);
			_selectedItem->setExpanded(false);
			_selectedItem->setText();
		}
		item->setRead(true);
		item->setExpanded(true);
		item->setHidden(false);
		item->setText();
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
	emit(loaded());
	saveFile();
	xml.clear();
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
	emit parsed(_title);
}

// Returns 0 if newer or equal copy rssitem is found, row number + 2 if a copy with submitted date being newer was found, and 1 if no previous copy was found.
int RssModel::filter(QString idStr, QDateTime date){
	for(int i=0; i<rowCount(); ++i){
		RssItem *temp = static_cast<RssItem*>(item(i));
		if(temp->id() == idStr){
			if(temp->data(DateRole).toDateTime() < date){
				return temp->row()+2;
			}
			return 0;
		}
	}
	return 1;
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
				QString tz = date.split(' ')[5];
				QString hour;
				hour = QString("%1%2").arg(QString(tz[1]),QString(tz[2]));
				int offset = hour.toInt();
				if(tz[0] == '-') offset *= -1;

				date.chop(date.length()-date.lastIndexOf(' '));
				QDateTime timestamp = QDateTime::fromString(date, "ddd, dd MMM yyyy hh:mm:ss");
				timestamp.setTimeSpec(Qt::UTC);
				timestamp = timestamp.toLocalTime();
				timestamp = timestamp.addSecs(offset * -3600);
				qDebug() << "Date: " << timestamp.toString() << " tz" << offset;
				int res = filter(id, timestamp);
				if(res){
					if(res != 1) removeRow(res-2);
					qDebug() << QString::number(hash(c_str(id)), 16);
					appendRow(new RssItem(title, timestamp, content, "", "", link, false, id));
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
	QString currentTag;
	QString content;
	QString summary;
	QString author;
	QString title;
	QString date;
	QString link;
	QString id;

	while (!xml.atEnd()) {
		xml.readNext();
		if (xml.isStartElement()) {
			if(xml.name() == "entry"){
				if (title!="" && _title == "" && _link == ""){
					_title = title;
					_link = link;
				}
				content.clear();
				summary.clear();
				author.clear();
				title.clear();
				date.clear();
				link.clear();
				id.clear();
			 }
			currentTag = xml.name().toString();
			if (currentTag == "link"){
				if (xml.attributes().hasAttribute("rel") && xml.attributes().value("rel") == "self")
					link += xml.text().toString();
				else if (xml.attributes().hasAttribute("href"))
					link += xml.attributes().value("href");
			 }
		} else if (xml.isEndElement()) {
			if (xml.name() == "entry" && link != "") {
				QDateTime timestamp = QDateTime::fromString(date, "yyyy-MM-ddThh:mm:ssZ");
				if(timestamp.toString() == "") timestamp = QDateTime::fromString(date, "yyyy-MM-ddThh:mm:ss.zzzZ");
				int res = filter(id, timestamp);
				if(res){
					if(res != 1) removeRow(res-2);
					bool read = false;
					if(_readItems.contains(QString::number(hash(c_str(id)), 16)))
						read = true;
					appendRow(new RssItem(title, timestamp, content, summary, author, link, read, id));
				}

				content.clear();
				summary.clear();
				author.clear();
				title.clear();
				date.clear();
				link.clear();
				id.clear();
			}

		} else if (xml.isCharacters() && !xml.isWhitespace()) {
			 if (currentTag == "title")
				  title += xml.text().toString();
			 else if (currentTag == "updated")
				  date += xml.text().toString();
			 else if (currentTag == "id")
				  id += xml.text().toString();
			 else if (currentTag == "content")
				  content += xml.text().toString();
			 else if (currentTag == "summary")
				 summary += xml.text().toString();
			 else if (currentTag == "name")
				 author += xml.text().toString();
		}
	}
	if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
		qWarning() << "XML ERROR:" << xml.lineNumber() << ": " << xml.errorString();
		http.deleteLater();
	}
}
