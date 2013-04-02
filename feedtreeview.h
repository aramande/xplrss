#ifndef FEEDTREEVIEW_H
#define FEEDTREEVIEW_H

#include <QTreeView>
#include <QDropEvent>
#include "xplrss.h"
class XplRSS;
class FeedTreeView : public QTreeView
{
		Q_OBJECT
	public:
		explicit FeedTreeView(QWidget *parent = 0);

		void dropEvent(QDropEvent *event);
		void mousePressEvent(QMouseEvent *event);
		void mouseMoveEvent(QMouseEvent *event);
	private:
		QPoint dragStartPosition;
		XplRSS *_mainWin;
	signals:
		
	protected slots:
		void editorDestroyed(QObject *editor);
		void commitData(QWidget *editor);
};

#endif // FEEDTREEVIEW_H
