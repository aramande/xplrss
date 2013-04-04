#include "compoundmodel.h"
#include "QModelIndex"

CompoundModel::CompoundModel(Branch *branch, QWidget *parent) :
	RssModel(parent), _branch(branch){
	_content = QList<RssModel*>();
	//loadUrl();
}

QVariant CompoundModel::data(const QModelIndex &index, int role) const{
	qDebug() << "Data";
}

QMap<int, QVariant> CompoundModel::itemData(const QModelIndex &index) const{
	qDebug() << "ItemData";
	if(!index.isValid()) return QMap<int, QVariant>();
	if(index.row() >= _rowCount) return QMap<int, QVariant>();

	int currentRow = index.row();
	for(int i=0; i < _content.length(); ++i){
		RssModel* model = _content.at(i);
		if(currentRow >= model->rowCount()){
			currentRow -= model->rowCount();
		}
		else{
			auto index = createIndex(currentRow, 0, this->_branch->index().internalId());
			return model->itemData(index);
		}
	}
	return QMap<int, QVariant>();
}
int CompoundModel::rowCount(const QModelIndex &parent) const{
	if(parent.isValid()) itemFromIndex(parent)->rowCount();
	return _rowCount;
}

RssItem* CompoundModel::get(int id) const{
	return dynamic_cast<RssItem*>(item(id));
}
Iter<RssItem*> CompoundModel::begin() const{
	return Iter<RssItem*>(this, 0);
}
Iter<RssItem*> CompoundModel::end() const{
	return Iter<RssItem*>(this, rowCount());
}

void CompoundModel::loadUrl(const QString &urlstring){
	Q_UNUSED(urlstring)
	_content = QList<RssModel*>();
	_rowCount = 0;
	for(int row = 0; row < _branch->rowCount(); ++row){
		_content.append(_branch->child(row)->data(RssRole).value<RssModel*>());
		_content.back()->loadUrl();
		_rowCount += _content.back()->rowCount();
	}
}
