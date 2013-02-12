#include "xplrss.h"
#include "ui_xplrss.h"
#include "htmldelegate.h"
#include "rssmodel.h"

XplRSS::XplRSS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XplRSS)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>() << 200 << 390);

	 //delete ui->listView;
	 //ui->listView = new HTMLListView();

	 feedTree = new FeedTree(":/db/tree.txt");
	 feedList = new RssModel("http://davidr64.tumblr.com/rss");
	 HTMLDelegate* delegate = new HTMLDelegate();

	 QString css = "QListView { background: #228; }";
	 //css += "QListView::item { margin: 15px 0px 15px 0px; }";

	 ui->treeView->setModel(feedTree);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	 ui->listView->setModel(feedList);
	 ui->listView->setItemDelegate(delegate);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	 ui->listView->setSelectionMode(QAbstractItemView::NoSelection);
	 setStyleSheet(css);

	 connect(ui->listView, SIGNAL(pressed(QModelIndex)), feedList, SLOT(pressed(QModelIndex)));
}

XplRSS::~XplRSS()
{
    delete ui;
}
