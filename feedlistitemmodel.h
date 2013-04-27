#ifndef FEEDLISTITEMMODEL_H
#define FEEDLISTITEMMODEL_H

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

	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex &child) const;
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QMap<int, QVariant> itemData(const QModelIndex &index) const;

private:
	RssModel* _instance;
	Branch* _branch;
	int _rowCount;
signals:
	void loaded(QStandardItemModel* model);
public slots:
	void feedLoaded(QStandardItemModel* model);
	void pressed(QModelIndex &index);
};

#endif // FEEDLISTITEMMODEL_H
