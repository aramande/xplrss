#ifndef XPLRSS_H
#define XPLRSS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QListView>
#include <QList>
#include <QTimer>

#include "feedtreeview.h"
#include "feedtree.h"
#include "rssmodel.h"
#include "branch.h"
#include "feed.h"
#include "util.h"

namespace Ui {
class XplRSS;
}
class FeedTreeView;
class FeedTree;
class RssModel;

class XplRSS : public QMainWindow
{
	Q_OBJECT
public:
	explicit XplRSS(QWidget *parent = 0);
	~XplRSS();
	void addToFeedTree(QStandardItem *item);
	void saveFeedTree();
	void loadFeed(RssModel *rssData);
    
private:
	Ui::XplRSS *ui;
	FeedTreeView *feedTreeView;
	QListView *_feedListView;
	FeedTree *feedTree;
	RssModel *feedList;
	QWidget *addFeedWidget;
	QTimer *timer;
	QString _feedTreeFile;

	void resizeEvent(QResizeEvent *event);
	void recSaveFeedTree(QStandardItem *item, int level, QFile &file);
public:
	ATTR_READER(QListView*, feedListView)
public slots:
	void delay();
	void scrollFix();
private slots:
	void on_actionAdd_Feed_triggered();
	void on_actionOptions_triggered();
	void on_actionAbout_triggered();
};

#endif // XPLRSS_H
