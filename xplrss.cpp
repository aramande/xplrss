#include "xplrss.h"
#include "ui_xplrss.h"
#include "htmldelegate.h"
#include "rssmodel.h"
#include <QScrollBar>
#include <QListView>

XplRSS::XplRSS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XplRSS)
{
    ui->setupUi(this);
    ui->splitter->setSizes(QList<int>() << 200 << 390);

	 //delete ui->listView;
	 //ui->listView = new ListView();

	 feedTree = new FeedTree(":/db/tree.txt");
	 feedList = new RssModel("http://davidr64.tumblr.com/rss");
	 HTMLDelegate* delegate = new HTMLDelegate(ui->listView);

	 QString css = "QListView { background: darkblue; }";

	 ui->treeView->setModel(feedTree);
    ui->treeView->setHeaderHidden(true);
    ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	 ui->listView->setModel(feedList);
	 ui->listView->setItemDelegate(delegate);
	 ui->listView->setResizeMode(QListView::Adjust);
	 ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	 //ui->listView->verticalScrollBar()->setRange(0, 0);
	 //ui->listView->verticalScrollBar()->setPageStep(1);

	 ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	 ui->listView->setWordWrap(true);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	 ui->listView->setSelectionMode(QAbstractItemView::NoSelection);
	 setStyleSheet(css);

	 connect(ui->listView, SIGNAL(pressed(QModelIndex)), feedList, SLOT(pressed(QModelIndex)));

	 //timer = new QTimer(this);
	 //timer->setSingleShot(true);
	 //timer->start(3000);
	 connect(feedList, SIGNAL(loaded()), this, SLOT(scrollFix()));
	 connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(scrollFix()));
}

XplRSS::~XplRSS()
{
    delete ui;
}

void XplRSS::scrollFix(){
	qDebug() << "Hello?";
	ui->listView->verticalScrollBar()->setSingleStep(25);
	//timer->start(5000);
}
