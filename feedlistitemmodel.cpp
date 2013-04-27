#include "feedlistitemmodel.h"

FeedListItemModel::FeedListItemModel(Branch* branch) : QAbstractItemModel(),
	_instance(NULL){
	if(branch == NULL) THROW("Tried to copy empty FeedListItemModel.");
	_branch = branch;
	loadUrl();
}

FeedListItemModel::FeedListItemModel(RssModel *instance) : 	QAbstractItemModel(),
	_branch(NULL){
	if(instance == NULL) THROW("Tried to copy empty FeedListItemModel.");
	_instance = instance;
	loadUrl();
}

FeedListItemModel* FeedListItemModel::link(){
	if(_instance) return new FeedListItemModel(_instance);
	else if(_branch) return new FeedListItemModel(_branch);
	return NULL;
}

void FeedListItemModel::loadUrl(){
	// TODO: Load the stuff here
	if(_branch){
		int counter = 0;
		for(int i=0; i<_branch->rowCount();++i){
			FeedListItemModel* model = _branch->child(i)->data(RssRole).value<FeedListItemModel*>();
			model->loadUrl();
			counter += model->rowCount();
		}
		_rowCount = counter;
	}
	else if(_instance){
		connect(_instance, SIGNAL(loaded(QStandardItemModel*)), this, SLOT(feedLoaded(QStandardItemModel*)));
		_instance->loadUrl();
		_rowCount = _instance->rowCount();
	}
}

QModelIndex FeedListItemModel::index(int row, int column, const QModelIndex &parent) const{
	if(_branch){
		int tempRow = row;
		for(int i=0; i<_branch->rowCount() && tempRow >= 0;++i){
			FeedListItemModel* model = _branch->child(i)->data(RssRole).value<FeedListItemModel*>();
			if(model->rowCount() > tempRow){
				return model->index(tempRow, column, parent);
			}
			tempRow -= model->rowCount();
		}
		return QModelIndex();
	}
	return createIndex(row,column,_instance);
}

QModelIndex FeedListItemModel::parent(const QModelIndex &child) const{
	return QModelIndex();
}

int FeedListItemModel::rowCount(const QModelIndex &parent) const{
	if(_rowCount >= 0) return _rowCount; //saves a bit on calculations, set _rowCount to negative to recount.
	else return 0;
}

int FeedListItemModel::columnCount(const QModelIndex &parent) const{
	return 1;
}

QVariant FeedListItemModel::data(const QModelIndex &index, int role) const{
	if(!index.isValid()) return QVariant();
	RssModel* model = reinterpret_cast<RssModel*>(index.internalPointer());
	return model->data(model->index(index.row(), index.column()),role);
}

QMap<int, QVariant> FeedListItemModel::itemData(const QModelIndex &index) const{
	QMap<int, QVariant> data;

	return data;
}

void FeedListItemModel::feedLoaded(QStandardItemModel *model){
	emit loaded(model);
}

void FeedListItemModel::pressed(QModelIndex &index){
	RssModel* model = reinterpret_cast<RssModel*>(index.internalPointer());
	model->pressed(createIndex(index.row(), index.column(), (quintptr)NULL));
}
