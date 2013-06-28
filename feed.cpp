#include "feed.h"
#include "xplrss.h"
#include "feedlistitemmodel.h"
#include <string>

Feed::Feed(const QString& url, const QString& title, const QString& readItems, XplRSS *parent) : QStandardItem(){
	_parent = parent;
	feedUtil = NULL;

	setData(QVariant(url), UrlRole);
	setData(QVariant::fromValue(new FeedListItemModel(new RssModel(url, readItems.split(";").toSet(), parent))), RssRole);
	if(title == ""){
		feedUtil = new FeedUtil(this);
	}
	else{
		setText(title);
	}
}

Feed::Feed(const Feed &other){
	setData(other.data(UrlRole), UrlRole);
	setData(QVariant::fromValue(other.data(RssRole).value<FeedListItemModel*>()->link()), RssRole);
	_parent = other.parent();
}

Feed::~Feed(){
	FeedListItemModel* rssData = data(RssRole).value<FeedListItemModel*>();
	delete rssData;

	if(feedUtil) delete feedUtil;
	feedUtil = NULL;
}

void Feed::setText(const QString &text){
	QString str;
	str.append(text);
	str.remove(",");
	qDebug() << str << text;
	QStandardItem::setText(str);
	QStandardItem::setData(str, TextRole);
	FeedListItemModel* rssData = data(RssRole).value<FeedListItemModel*>();

	str.append(",");
	str.append(data(UrlRole).toString());
	str.append(",");

	QList<QString> readItems = rssData->instance()->readItems();

	foreach(QString item, readItems){
		str.append(item);
		str.append(";");
	}
	setData(QVariant(str), SaveRole);
}

void Feed::updateSaveText(){
	QString str;
	str.append(data(TextRole).toString());
	str.append(",");

	str.append(data(UrlRole).toString());
	str.append(",");

	FeedListItemModel* rssData = data(RssRole).value<FeedListItemModel*>();
	QList<QString> readItems = rssData->instance()->readItems();

	foreach(QString item, readItems){
		str.append(item);
		str.append(";");
	}
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

QVariant Feed::data(int role) const{
	QVariant res;
	switch(role){
	default:
		res = QStandardItem::data(role);
		break;
	}
	return res;
}

FeedUtil::FeedUtil(Feed* feed){
	_feed = feed;
	QVariant qv = _feed->data(RssRole);
	if(qv.canConvert<FeedListItemModel*>())
		connect(qv.value<FeedListItemModel*>(), SIGNAL(parsed(QString)), this, SLOT(setTitle(QString)));
}

void FeedUtil::setTitle(QString title){
	_feed->setText(title);
	dynamic_cast<XplRSS*>(_feed->parent())->saveFeedTree();
}
