#include "feedtree.h"
#include "rssmodel.h"
#include <QDebug>
#include <QApplication>


FeedTree::FeedTree(const QString &filename, QObject *parent) : QStandardItemModel(parent)
{
	_filename = filename;
	_parent = dynamic_cast<XplRSS*>(parent);
	read();
}

FeedTree::FeedTree(QObject *parent) : QStandardItemModel(parent){}

void FeedTree::read(){
	//read the file
	QFile file(_filename);
	if(!file.open(QIODevice::ReadOnly | QIODevice::Text)){
		QMessageBox::warning(0, "Error", file.errorString());
	}
	char *value = new char[LINEBUFLEN];
	int level = 0;
	int prevLevel = 0;
	std::stack<QStandardItem*> last;
	last.push(invisibleRootItem());

	while(file.readLine(value, LINEBUFLEN) > 0){
		if(strlen(value) == 0) continue;
		value[strlen(value)-1] = '\0';
		level = 0;
		while(value[level] == '>'){
			++level;
		}
		char* pointer = value + level;
		if(last.size()>1){
			for(int i=0;i<prevLevel-level+1;++i){
				last.pop();
			}
		}

		QStandardItem *item = toFeed(QString(pointer));
		if(!item) item = toBranch(QString(pointer));

		last.top()->appendRow(item);
		last.push(item);
		prevLevel = level;
	}

	delete[] value;
	file.close();
}

//Returns null if failed to parse line as a feed
Feed* FeedTree::toFeed(const QString &line){
	QStringList list = line.split(",");
	if(list.length() == 3){
		// TODO: Look through tree to see if same url exists twice, then link

		return new Feed(list[1], list[0], list[2], _parent);
	}
	return NULL;
}

//Returns a branch, always run after to feed if feed returns null
Branch* FeedTree::toBranch(const QString &line){
	return new Branch(line);
}

void FeedTree::pressed(QModelIndex index){
	if(!index.isValid()) return;
	Qt::MouseButtons mouse = QApplication::mouseButtons(); // TODO: account for which button is used
	QStandardItem* item = itemFromIndex(index);
	if(item->data(RssRole).isValid()){ // If has feed
		_parent->loadFeed(item->data(RssRole).value<RssModel*>());
	}

}

void FeedTree::update(){
	read();
}

Qt::ItemFlags FeedTree::flags(const QModelIndex &index) const{
	Qt::ItemFlags defaultFlags = Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
	if (index.isValid() && dynamic_cast<Branch*>(itemFromIndex(index)) != NULL){
		//qDebug() << "Branch" << index << defaultFlags;
		return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
	}
	else if (index.isValid() && dynamic_cast<Feed*>(itemFromIndex(index)) != NULL){
		//qDebug() << "Feed" << index << defaultFlags;
		return Qt::ItemIsDragEnabled | defaultFlags;
	}
	else
		qDebug() << "What's this?";
		return Qt::ItemIsDropEnabled | defaultFlags;
}

Qt::DropActions FeedTree::supportedDropActions() const{
	return Qt::LinkAction | Qt::MoveAction;
}

bool FeedTree::setData(const QModelIndex &index, const QVariant &value, int role){
	if(value.isValid() && value.toString() != ""){
		QStandardItem *item =itemFromIndex(index);
		item->setData(value, TextRole);
		emit dataChanged(index, index, QVector<int>() << role);
		return true;
	}
	return false;
}
