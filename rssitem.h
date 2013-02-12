#ifndef RSSITEM_H
#define RSSITEM_H

#include <QStandardItem>

class RssItem : public QStandardItem
{
	bool _read, _hidden, _expanded;
	QString _title, _date, _author, _content, _summary, _itemLink, _id;
public:
	RssItem(const QString &title, const QString &date, const QString &content, const QString &summary, const QString &author, const QString &itemLink, bool read = false, const QString &id = "");
	void setRead(bool value = true);
	void setHidden(bool value);
	void setExpanded(bool value);
	void setText(const QString &title, const QString &date, const QString &content, const QString &summary, const QString &author, const QString itemLink);
	void setText(const QString &junk = "");
	const QString& id();
	const QString& date();
	const QString& title();
	const QString& content();
	const QString& itemLink();
	const QString& summary();
	const QString& author();
	bool read();
};

#endif // RSSITEM_H
