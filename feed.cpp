#include "feed.h"
#include "xplrss.h"
#include <string>

Feed::Feed(const QString& url, const QString& title, const QString& readItems, QWidget *parent) : QStandardItem(){
	_parent = dynamic_cast<XplRSS*>(parent);
	rssData = new RssModel(url, readItems.split(";"), parent);
	feedUtil = NULL;

	setData(QVariant(url), UrlRole);
	setData(QVariant::fromValue(rssData), RssRole);
	if(title == ""){
		feedUtil = new FeedUtil(this);
	}
	else{
		setText(title);
	}
}

Feed::Feed(const Feed &other){
	setData(other.data(UrlRole), UrlRole);
	setData(other.data(RssRole), RssRole);
	_parent = other.parent();
	rssData = other.rssData;
	rssData->addRef();
	setText(rssData->title());
	feedUtil = NULL;

}

Feed::~Feed(){
	rssData->delRef();
	if(!rssData->ref()) delete rssData;

	if(feedUtil) delete feedUtil;
	feedUtil = NULL;
}

void Feed::setText(const QString &text){
	QString str;
	str.append(text);
	str.remove(",");
	qDebug() << str;
	QStandardItem::setText(str);

	str.append(",");
	str.append(data(UrlRole).toString());
	str.append(",");
	// TODO: write read posts ids here
	setData(QVariant(str), SaveRole);
}

void Feed::setData(const QVariant &value, int role){
	if(role<Qt::UserRole) QStandardItem::setData(value, role);

	switch(role){
		case TextRole:
			setText(value.toString());
			break;
		default:
			QStandardItem::setData(value, role);
			break;
	}
}

FeedUtil::FeedUtil(Feed* feed){
	_feed = feed;
	QVariant qv = _feed->data(RssRole);
	if(qv.canConvert<RssModel*>())
		connect(qv.value<RssModel*>(), SIGNAL(parsed(QString)), this, SLOT(setTitle(QString)));
}

void FeedUtil::setTitle(QString title){
	_feed->setText(title);
	dynamic_cast<XplRSS*>(_feed->parent())->saveFeedTree();
}
