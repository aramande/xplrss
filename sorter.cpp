#include "sorter.h"

Sorter::Sorter(QObject *parent) :
	QSortFilterProxyModel(parent)
{
}

void Sorter::setSourceModel(QAbstractItemModel *model){
	QSortFilterProxyModel::setSourceModel(model);
	qDebug() << model;
}
