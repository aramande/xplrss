#include "feedtreeview.h"
#include "feedtree.h"
#include "branch.h"
#include "feed.h"
#include "util.h"
#include <QDebug>
#include <QMimeData>
#include <QApplication>
#include <QDrag>

FeedTreeView::FeedTreeView(QWidget *parent) :
	QTreeView(parent)
{
	_mainWin = dynamic_cast<XplRSS*>(parent);
	setHeaderHidden(true);
	setDragEnabled(true);
	setAcceptDrops(true);
	setDropIndicatorShown(true);
	setEditTriggers(QAbstractItemView::DoubleClicked);
}

void FeedTreeView::editorDestroyed(QObject *editor){
	QTreeView::editorDestroyed(editor);
}

void FeedTreeView::commitData(QWidget* editor){
	QTreeView::commitData(editor);
	_mainWin->saveFeedTree();
	//qDebug() << "Hello, committing data~";
}

void FeedTreeView::dropEvent(QDropEvent *event){
	if (dragDropMode() == InternalMove) {
	  if (event->source() != this || !(event->possibleActions() & Qt::MoveAction))
			return;
	}
	FeedTree* m = dynamic_cast<FeedTree*>(model());
	if(!m) return;
	QStandardItem *source = m->itemFromIndex(indexAt(dragStartPosition));
	QStandardItem *target = m->itemFromIndex(indexAt(event->pos()));
	if(target){
		if(event->dropAction() & Qt::MoveAction){
			if(source->data(RssRole).isValid()){
				target->appendRow(new Feed(*dynamic_cast<Feed*>(source)));
			}
			else{
				target->appendRow(new Branch(source->data(SaveRole).toString()));
			}
			event->accept();
			qDebug() << "Moving" << source->data(SaveRole).toString() << "to" << target->data(SaveRole).toString();
		}
	}
	else{

	}
	stopAutoScroll();
	setState(NoState);
}

void FeedTreeView::mousePressEvent(QMouseEvent *event){
	dragStartPosition = event->pos();
	QTreeView::mousePressEvent(event);
}

void FeedTreeView::mouseMoveEvent(QMouseEvent *event){
	QTreeView::mouseMoveEvent(event);

}
