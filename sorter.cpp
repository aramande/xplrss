#include "sorter.h"

Sorter::Sorter(QObject *parent) :
	QSortFilterProxyModel(parent)
{
}

void Sorter::setSourceModel(QAbstractItemModel *model){
	qDebug() << model;
	QSortFilterProxyModel::setSourceModel(model);
}
