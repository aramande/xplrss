#include "compoundmodel.h"
#include "QModelIndex"

CompoundModel::CompoundModel(Branch *branch, QWidget *parent) :
	RssModel(parent), _branch(branch){
	_content = QList<RssModel*>();
	qRegisterMetaTypeStreamOperators<CompoundModel*>("CompoundModel*");
	connect(this, SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(gotRowInsert(QModelIndex,int,int)));
}

QVariant CompoundModel::data(const QModelIndex &index, int role) const{
	QMap<int, QVariant> temp = itemData(index);
	if(temp.contains(role))
		return temp[role];
	return QVariant();
}

QMap<int, QVariant> CompoundModel::itemData(const QModelIndex &index) const{
//	qDebug() << "ItemData";
	if(!index.isValid()) return QMap<int, QVariant>();
	if(index.row() >= _rowCount) return QMap<int, QVariant>();
	if(index.data(RssRole).canConvert<RssModel*>()){
		return index.data(RssRole).value<RssModel*>()->itemData(index);
	}

//	int currentRow = index.row();
//	for(int i=0; i < _content.length(); ++i){
//		RssModel* model = _content.at(i);
//		if(currentRow >= model->rowCount()){
//			currentRow -= model->rowCount();
//		}
//		else{
//			auto index = createIndex(currentRow, 0, this->_branch->index().internalId());

//		}
//	}
	return QMap<int, QVariant>();
}
int CompoundModel::rowCount(const QModelIndex &parent) const{
	if(parent.isValid()) itemFromIndex(parent)->rowCount();
	return _rowCount;
}

void CompoundModel::loadUrl(const QString &urlstring){
	Q_UNUSED(urlstring)
	clear();
	_content = QList<RssModel*>();
	_rowCount = 0;
	for(int row = 0; row < _branch->rowCount(); ++row){
		RssModel* temp = _branch->child(row)->data(RssRole).value<RssModel*>();
		connect(temp, SIGNAL(loaded(QStandardItemModel*)),this, SLOT(gotFeed(QStandardItemModel*)));
		_content.append(temp);
		temp->loadUrl();
		_rowCount += temp->rowCount();
	}
}

QModelIndex CompoundModel::index(int row, int column, const QModelIndex &parent) const{
	qDebug() << "Index!" << row << column;
	if(row >= _rowCount) return QModelIndex();
	int currentRow = row;
	for(int i=0; i < _content.length(); ++i){
		RssModel* model = _content.at(i);
		if(currentRow < model->rowCount()){
			//QModelIndex temp = model->index(currentRow,0);
			//temp = model->index(currentRow,0);
			return model->index(currentRow,0);
		}
		currentRow -= model->rowCount();
	}
	return QStandardItemModel::index(row, column, parent);
}

void CompoundModel::gotFeed(QStandardItemModel *model){
	qDebug() << "Got feed!";
	int prev = _rowCount;
	insertRows(_rowCount, model->rowCount());
	//for(int i=0; i<model->rowCount();++i)
	//	setItem(i+prev, model->item(i));
	emit loaded(model);
}

void CompoundModel::gotRowInsert(const QModelIndex &parent, int start, int end){
	qDebug() << "Inserted a row at" << start << "With parent" << parent;
}

QDataStream &operator<<(QDataStream &out, CompoundModel * const &rhs) {
	out.writeRawData(reinterpret_cast<const char*>(&rhs), sizeof(rhs));
	return out;
}

QDataStream &operator>>(QDataStream &in, CompoundModel *&rhs) {
	in.readRawData(reinterpret_cast<char*>(&rhs), sizeof(rhs));
	return in;
}

QMimeData* CompoundModel::mimeData(const QList<QStandardItem *> items ) const
{
	Q_UNUSED(items)
	return new QMimeData();
}
