#ifndef SORTER_H
#define SORTER_H

#include <QtCore>
#include <QSortFilterProxyModel>

class Sorter : public QSortFilterProxyModel
{
	Q_OBJECT
public:
	explicit Sorter(QObject *parent = 0);
	void setSourceModel(QAbstractItemModel *sourceModel);
signals:
	
public slots:
	
};

#endif // SORTER_H
