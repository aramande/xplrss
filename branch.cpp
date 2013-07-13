#include "branch.h"
#include "util.h"
#include "feed.h"
//#include "compoundmodel.h"
#include <QDebug>

Branch::Branch(const QString &label) : QStandardItem(label)
{
	setData(QVariant(label),SaveRole);
	//setData(QVariant::fromValue(new FeedListItemModel(this)), RssRole);
}

Branch::Branch(const Branch &other) : QStandardItem(other.data(SaveRole).toString()){
	setData(other.data(SaveRole),TextRole);
	//setData(other.data(RssRole),RssRole);
	//data(RssRole).value<RssModel*>()->addRef();

	for(int i=0; i<other.rowCount(); ++i){
		if(other.data(UrlRole).isValid())
			appendRow(new Feed(*dynamic_cast<Feed*>(other.child(i))));
		else
			appendRow(new Branch(*dynamic_cast<Branch*>(other.child(i))));
	}
}

Branch::~Branch(){
	//FeedListItemModel* rssData = data(RssRole).value<FeedListItemModel*>();
	//delete rssData;
	//data(RssRole).fromValue(NULL);
}

void Branch::setText(const QString &text){
	QString str;
	str.append(text);
	str.remove(",");
	QStandardItem::setText(str);
	setData(QVariant(str), SaveRole);
}

void Branch::setData(const QVariant &value, int role){
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

void Branch::loadUrl(){
	Feed* feed;
	Branch* branch;
	for(int i=0; i<rowCount(); ++i){
		if((feed = dynamic_cast<Feed*>(child(i))) != NULL){
			feed->loadUrl();
		}
		else{
			branch = dynamic_cast<Branch*>(child(i));
			branch->loadUrl();
		}
	}
}
