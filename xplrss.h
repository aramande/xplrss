#ifndef XPLRSS_H
#define XPLRSS_H

#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QMainWindow>
#include <QListView>
#include <QTimer>
#include <QList>

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
	QSortFilterProxyModel *_sorter;
	FeedTree *feedTree;
	RssModel *feedList;
	QWidget *addFeedWidget;
	QTimer *timer;
	QString _feedTreeFile;

	void resizeEvent(QResizeEvent *event);
	void recSaveFeedTree(QStandardItem *item, int level, QFile &file);
	void closeEvent(QCloseEvent *event);
public:
	ATTR_READER(QListView*, feedListView)
	ATTR_READER(QSortFilterProxyModel*, sorter)
public slots:
	void delay();
	void scrollFix();
private slots:
	void on_actionAdd_Feed_triggered();
	void on_actionOptions_triggered();
	void on_actionAbout_triggered();
	void on_actionDate_Ascending_triggered();
	void on_actionDate_Descending_triggered();
	void on_actionRead_Ascending_triggered();
	void on_actionRead_Descending_triggered();
	void on_actionQuit();
};

#endif // XPLRSS_H

