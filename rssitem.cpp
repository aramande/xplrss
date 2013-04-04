#include "rssitem.h"
#include "util.h"
#include <cstdio>
#include <QDebug>
RssItem::RssItem(const QString &title, const QDateTime &date, const QString &content, const QString &summary, const QString &author, const QString &itemLink, bool read, const QString &id) : QStandardItem()
{
	setData(QVariant(read), ReadRole);
	_hidden = read;
	_expanded = false;
	_id = id;
	setData(QVariant(date), DateRole);
	this->setBackground(QBrush(QColor(Qt::white)));
	setText(title,date,content,summary,author,itemLink);
}

void RssItem::setRead(bool value){
	setData(value, ReadRole);
}
void RssItem::setHidden(bool value){
	_hidden = value;
}
void RssItem::setExpanded(bool value){
	_expanded = value;
}

void RssItem::setText(const QString &title, const QDateTime &date, const QString &content, const QString &summary, const QString &author, const QString itemLink){
	_title = title;
	setData(date, DateRole);
	_content = content;
	_itemLink = itemLink;

	if(summary == ""){
		QStringList temp;
		int i = 0;
		foreach(QString curr, content.split(" ")){
			if(++i == 100) break;
			temp << curr;
		}
		if(i != 100) _expanded = true;
		else _summary = temp.join(" ");
	}
	else _summary = summary;

	_author = author;

	QString text = "No Data";
	if(_hidden){
		if(data(ReadRole).toBool())
			text = QString ("<font size='4'>%1</font> (%2)").arg(_title, data(DateRole).toDateTime().toString());
		else
			text = QString ("<font size='4'><strong>%1</strong></font> (%2)").arg(_title, data(DateRole).toDateTime().toString());
	}
	else if(!_expanded){
		if(data(ReadRole).toBool())
			text = QString ("<font size='4'>%1</font> (%2)<p>%3 ...</p>").arg(_title,data(DateRole).toDateTime().toString(), _summary);
		else
			text = QString ("<font size='4'><strong>%1</strong></font> (%2)<p>%3 ...</p>").arg(_title, data(DateRole).toDateTime().toString(), _summary);
	}
	else{
		if(data(ReadRole).toBool())
			text = QString ("<font size='4'>%1</font> (%2)<p>%3</p>").arg(_title, data(DateRole).toDateTime().toString(), _content);
		else
			text = QString ("<font size='4'><strong>%1</strong></font> (%2)<p>%3</p>").arg(_title, data(DateRole).toDateTime().toString(), _content);
	}

	QStandardItem::setText(text);

}

// Updates the text without setting any new values.
// Used for updating the read state
void RssItem::setText(const QString &junk){
	Q_UNUSED(junk)
	setText(_title, data(DateRole).toDateTime(), _content, _summary, _author, _itemLink);
}

