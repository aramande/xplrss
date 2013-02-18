#include "rssitem.h"
#include <cstdio>
#include <QDebug>
RssItem::RssItem(const QString &title, const QString &date, const QString &content, const QString &summary, const QString &author, const QString &itemLink, bool read, const QString &id) : QStandardItem()
{
	_read = read;
	_hidden = read;
	_expanded = false;
	_id = id;
	_date = date;
	this->setBackground(QBrush(QColor(Qt::white)));
	setText(title,date,content,summary,author,itemLink);
}

const QString& RssItem::id(){
	return _id;
}
const QString& RssItem::date(){
	return _date;
}
const QString& RssItem::title(){
	return _title;
}
const QString& RssItem::content(){
	return _content;
}
const QString& RssItem::itemLink(){
	return _itemLink;
}
const QString& RssItem::summary(){
	return _summary;
}
const QString& RssItem::author(){
	return _author;
}
bool RssItem::read(){
	return _read;
}

void RssItem::setRead(bool value){
	_read = value;
	setText();
}

void RssItem::setHidden(bool value){
	_hidden = value;
	setText();
}

void RssItem::setExpanded(bool value){
	_expanded = value;
	setText();
}

void RssItem::setText(const QString &title, const QString &date, const QString &content, const QString &summary, const QString &author, const QString itemLink){
	_title = title;
	_date = date;
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
		if(_read)
			text = QString ("<font size='4'>%1</font> (%2)").arg(_title, _date);
		else
			text = QString ("<font size='4'><strong>%1</strong></font> (%2)").arg(_title, _date);
	}
	else if(!_expanded){
		if(_read)
			text = QString ("<font size='4'>%1</font> (%2)<p>%3 ...</p>").arg(_title, _date, _summary);
		else
			text = QString ("<font size='4'><strong>%1</strong></font> (%2)<p>%3 ...</p>").arg(_title, _date, _summary);
	}
	else{
		if(_read)
			text = QString ("<font size='4'>%1</font> (%2)<p>%3</p>").arg(_title, _date, _content);
		else
			text = QString ("<font size='4'><strong>%1</strong></font> (%2)<p>%3</p>").arg(_title, _date, _content);
	}

	QStandardItem::setText(text);
}

// Updates the text without setting any new values.
// Used for updating the read state
void RssItem::setText(const QString &junk){
	setText(_title, _date, _content, _summary, _author, _itemLink);

	if(junk=="") return; // just to get rid of the annoying warning
}

/*
void RssItem::paint(QObject* parent, QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const
{
	//removing unused parameter warning
	for(;index.isValid();) break;

	//QListView *p = (QListView*)parent;
	QStyleOptionViewItemV4 options = option;

	painter->save();
	QTextDocument doc;
	doc.setHtml(options.text);
	doc.setTextWidth(option.rect.size().width());
	QAbstractTextDocumentLayout::PaintContext context;
	painter->translate(option.rect.x(), option.rect.y());
	doc.documentLayout()->draw(painter, context);
	painter->restore();
}

QSize RssItem::sizeHint(QObject* parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
	//removing unused parameter warning
	for(;index.isValid();) break;

	QListView *p = (QListView*)parent;
	QFontMetrics fm(p->font());
	QStyleOptionViewItemV4 options = option;
	float rw = float(p->viewport()->size().width());
	float tw = fm.width(options.text);
	float ratio = tw/rw;
	int lines = 0;
	if(ratio - int(ratio) < 0.1f)
		 lines = int(ratio);
	else
		 lines = int(ratio) + 1;
	return QSize(rw,lines*fm.height());
}
*/
