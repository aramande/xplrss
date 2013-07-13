
#ifndef FEEDLISTITEMMODEL_H
#define FEEDLISTITEMMODEL_H

#include <QtCore>
#include <QApplication>
#include <QStandardItemModel>
#include "rssmodel.h"
#include "branch.h"
#include "util.h"

class RssModel;

class FeedListItemModel : public QAbstractItemModel
{
	Q_OBJECT
public:
	explicit FeedListItemModel(Branch* branch);
	explicit FeedListItemModel(RssModel* instance);

	FeedListItemModel* link();
	void loadUrl();

	QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &child) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QMap<int, QVariant> itemData(const QModelIndex &index) const;
	RssModel* instance(const QModelIndex& index = QModelIndex()) const;

private:
	RssModel* _instance;
	Branch* _branch;
	int _rowCount;
	Qt::MouseButtons _mousePressed;
public:
	ATTR_READER(Qt::MouseButtons, mousePressed)
signals:
	void loaded(QStandardItemModel* model);
public slots:
	void feedLoaded(QStandardItemModel* model);
	void clicked(const QModelIndex &index);
	void pressed(const QModelIndex &index);
};

#endif // FEEDLISTITEMMODEL_H
