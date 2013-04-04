#include "branch.h"
#include "util.h"
#include "compoundmodel.h"
#include <QDebug>

Branch::Branch(const QString &label) : QStandardItem(label)
{
	setData(QVariant(label),SaveRole);
	setData(QVariant::fromValue(new CompoundModel(this)), RssRole);
}

Branch::~Branch(){
	RssModel* rssData = data(RssRole).value<RssModel*>();
	rssData->delRef();
	if(!rssData->ref()) delete rssData;
	data(RssRole).fromValue(NULL);
}

void Branch::setText(const QString &text){
	qDebug() << text << "this?";
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
