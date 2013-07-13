#include "feedlistview.h"

FeedListView::FeedListView(QWidget *parent) :
	QListView(parent)
{
}

QModelIndex FeedListView::indexAt(const QPoint &p) const{
	//qDebug() << "indexAt" << p;
	QModelIndex original = QListView::indexAt(p);
	//qDebug() << original;
	return original;
}

void FeedListView::mousePressEvent(QMouseEvent *event){
	//qDebug() << event->button() << indexAt(event->pos());
	emit pressed(indexAt(event->pos()));
	QListView::mousePressEvent(event);
}

bool FeedListView::event(QEvent *e){
//	qDebug() << "Event type:" << e->type();
//	switch(e->type()){
//		case QEvent::MouseButtonRelease:
//		case QEvent::MouseButtonPress:
//		case QEvent::MouseMove:
//			qDebug() << "Event type:" << e->type();
//			break;
//	}
	return QListView::event(e);
}
