#ifndef FEEDLISTVIEW_H
#define FEEDLISTVIEW_H

#include <QtCore>
#include <QListView>
#include <QMouseEvent>

class FeedListView : public QListView
{
	Q_OBJECT
public:
	explicit FeedListView(QWidget *parent = 0);
	QModelIndex indexAt(const QPoint &p) const;
protected:
	void mousePressEvent(QMouseEvent *event);
	bool event(QEvent *e);
signals:
public slots:
	
};

#endif // FEEDLISTVIEW_H
