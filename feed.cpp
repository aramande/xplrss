#include "feed.h"
#include "xplrss.h"
#include "feedlistitemmodel.h"
#include <string>

Feed::Feed(const QString& url, const QString& title, const QString& readItems, XplRSS *parent) : QStandardItem(){
	_parent = parent;

	setData(QVariant(url), UrlRole);
	//setData(QVariant::fromValue(new FeedListItemModel(new RssModel(url, readItems.split(";").toSet(), parent))), RssRole);
	setData(QVariant::fromValue(new RssModel(url, readItems.split(";").toSet(), parent)), RssRole);
	feedUtil = new FeedUtil(this);

	if(title == ""){
		feedUtil->setText();
	}
	else{
		setText(title);
	}
}

Feed::Feed(const Feed &other){
	setData(other.data(UrlRole), UrlRole);
	//setData(QVariant::fromValue(other.data(RssRole).value<RssModel*>()->link()), RssRole);
	RssModel* model = other.data(RssRole).value<RssModel*>();
	setData(QVariant::fromValue(model), RssRole);
	model->addRef();
	setText(other.data(TextRole).toString());
	feedUtil = new FeedUtil(this);
	_parent = other.parent();
}

Feed::~Feed(){
	RssModel* rssData = data(RssRole).value<RssModel*>();
	rssData->delRef();
	if(rssData->ref() == 0)	delete rssData;

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
	RssModel* rssData = data(RssRole).value<RssModel*>();

	str.append(",");
	str.append(data(UrlRole).toString());
	str.append(",");

	QList<QString> readItems = rssData->readItems();

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

	RssModel* rssData = data(RssRole).value<RssModel*>();
	QList<QString> readItems = rssData->readItems();

	foreach(QString item, readItems){
		str.append(item);
		str.append(";");
	}
	if(readItems.length() > 0) str.truncate(str.length()-1);
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

void Feed::loadUrl(){
	feedUtil->loadUrl();
}



FeedUtil::FeedUtil(Feed* feed){
	setFeed(feed);
}

void FeedUtil::setFeed(Feed* feed){
	_feed = feed;
}

void FeedUtil::loadUrl(){
	_feed->setData(QVariant(QIcon(":32/loading")),Qt::DecorationRole);
	RssModel* model = _feed->data(RssRole).value<RssModel*>();
	connect(model, SIGNAL(loaded(QStandardItemModel*)), this, SLOT(finishedLoading()));
	qDebug() << "LOADING URL";
	model->loadUrl();
}

void FeedUtil::setText(){
	QVariant qv = _feed->data(RssRole);
	if(qv.canConvert<RssModel*>())
		connect(qv.value<RssModel*>(), SIGNAL(parsed(QString)), this, SLOT(setTitle(QString)));
}

void FeedUtil::finishedLoading(){
	qDebug() << "FINISHED LOADING URL";
	_feed->setData(QVariant(),Qt::DecorationRole);
	RssModel* model = _feed->data(RssRole).value<RssModel*>();
	disconnect(model, SIGNAL(loaded(QStandardItemModel*)), this, SLOT(finishedLoading()));
}

void FeedUtil::setTitle(QString title){
	_feed->setText(title);
	dynamic_cast<XplRSS*>(_feed->parent())->saveFeedTree();
	QVariant qv = _feed->data(RssRole);
	disconnect(qv.value<RssModel*>(), SIGNAL(parsed(QString)), this, SLOT(setTitle(QString)));
}
