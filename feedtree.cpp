#include "feedtree.h"
#include <QDebug>

FeedTree::FeedTree(const QString &filename, QObject *parent) : QStandardItemModel(parent)
{
	_filename = filename;
	read();
}

void FeedTree::read(){
	//read the file
	QFile file(_filename);
	if(!file.open(QIODevice::ReadOnly)){
		QMessageBox::warning(0, "Error", file.errorString());
	}
	char *value = new char[512];
	int level = 0;
	int prevLevel = 0;
	std::stack<QStandardItem*> last;
	last.push(invisibleRootItem());

	while(file.readLine(value, 512) > 0){
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

		QStandardItem *item = new QStandardItem(pointer);
		last.top()->appendRow(item);
		last.push(item);
		prevLevel = level;
	}

	delete[] value;
	file.close();
}

void FeedTree::update(){
	read();
}
