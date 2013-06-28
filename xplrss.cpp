#include "xplrss.h"
#include "ui_xplrss.h"
#include "htmldelegate.h"
#include "addfeedwidget.h"
#include "sorter.h"
#include "rssmodel.h"
#include "branch.h"
#include <QScrollBar>
#include <QListView>
#include <string>


XplRSS::XplRSS(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::XplRSS)
{
	setWindowTitle("XplRSS");
	feedTreeView = new FeedTreeView(this);
	_feedListView = new FeedListView(this);
	ui->setupUi(this);
	ui->splitter->addWidget(feedTreeView);
	ui->splitter->addWidget(_feedListView);
	ui->splitter->setSizes(QList<int>() << 200 << 390);
	_feedTreeFile = QString("%1/.xplrss/feedtree.cfg").arg(QDir::homePath());
	QFile file(_feedTreeFile);
	qDebug() << _feedTreeFile << file.exists();
	if(file.exists()){
		qDebug() << "Loading feedtree...";
		feedTree = new FeedTree(_feedTreeFile, this);
	}
	else{
		feedTree = new FeedTree(this);
	}
	feedList = new FeedListItemModel(new RssModel("http://davidr64.tumblr.com/rss", QSet<QString>(), this)); // TODO: make dynamic later
	//feedList = new FeedListItemModel();
	HTMLDelegate* delegate = new HTMLDelegate(_feedListView);
	QString css = "QListView { background: darkblue; }";
	_sorter = new Sorter();

	feedTreeView->setModel(feedTree);

	_sorter->setSourceModel(feedList);
	_feedListView->setModel(_sorter);

	_feedListView->setItemDelegate(delegate);
	_feedListView->setResizeMode(QListView::Adjust);
	_feedListView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	_feedListView->setWordWrap(true);
	_feedListView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	_feedListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	_feedListView->setSelectionMode(QAbstractItemView::NoSelection);
	setStyleSheet(css);


	for(int i=0; i<feedTree->rowCount(); ++i){
		feedTree->item(i)->data(RssRole).value<FeedListItemModel*>()->loadUrl();
	}

	//Mouselistener connectors
	connect(_feedListView, SIGNAL(pressed(QModelIndex)), feedList, SLOT(pressed(QModelIndex)));
	connect(_feedListView, SIGNAL(clicked(QModelIndex)), feedList, SLOT(clicked(QModelIndex)));
	connect(feedTreeView, SIGNAL(pressed(QModelIndex)), feedTree, SLOT(pressed(QModelIndex)));

	//Timer for the delay of scrollbug
	timer = new QTimer(this);
	timer->setSingleShot(true);

	//Scrollbug connectors
	connect(_feedListView, SIGNAL(clicked(QModelIndex)), this, SLOT(delay()));
	connect(feedList, SIGNAL(loaded(QStandardItemModel*)), this, SLOT(delay()));
	connect(timer, SIGNAL(timeout()), this, SLOT(scrollFix()));
}

XplRSS::~XplRSS()
{
	delete ui;
	//delete feedListView;
	//delete feedTreeView;
}

void XplRSS::resizeEvent(QResizeEvent * event){
	Q_UNUSED(event)
	delay();
}

void XplRSS::closeEvent(QCloseEvent *event){
	Q_UNUSED(event)
	saveFeedTree();
}

//This is a delay before the scrollfix
void XplRSS::delay(){
	timer->start(100);
}

//Fixes the scrollbug
void XplRSS::scrollFix(){
	_feedListView->verticalScrollBar()->setSingleStep(25);
}

void XplRSS::addToFeedTree(QStandardItem* item){
	feedTree->appendRow(item);
	if(addFeedWidget != NULL){
		delete addFeedWidget;
		addFeedWidget = NULL;
	}
	saveFeedTree();
}

void XplRSS::saveFeedTree(){
	// TODO: Call this when stuff has been moved
	QFile file(_feedTreeFile);
	QDir dir;
	if(!dir.exists(QDir::homePath() + "/.xplrss")){
		 dir.mkdir(QDir::homePath() + "/.xplrss");
	}
	file.open(QFile::WriteOnly | QFile::Text);
	for(int i=0; i<feedTree->rowCount(); i++){
		recSaveFeedTree(feedTree->item(i), 0, file);
	}
	file.flush();
	file.close();
	qDebug() << "INFO: Feedtree was saved to file";
//#endif
}

void XplRSS::recSaveFeedTree(QStandardItem* item, int level, QFile& file){
		for(int k=0; k<level; k++){
			file.write(">");
		}
		Feed* temp = dynamic_cast<Feed*>(item);
		if(temp) temp->updateSaveText();

		QString line = item->data(SaveRole).toString();
		qDebug() << line;
		file.write(c_str(line));
		file.write("\n");

		if(item->hasChildren()){
			for(int i=0; i<item->rowCount(); i++){
				recSaveFeedTree(item->child(i), level+1, file);
			}
		}
}

void XplRSS::loadFeed(FeedListItemModel *rssData){
	feedList = rssData;
	//_feedListView->setModel(rssData);
	_sorter->setSourceModel(rssData);
	_feedListView->scrollToTop();
	delay();
}

void XplRSS::on_actionAdd_Feed_triggered()
{
	addFeedWidget = new AddFeedWidget(this);
}

void XplRSS::on_actionOptions_triggered()
{
	QMessageBox::information(this, "Options", "Options go here! Yay!");
}

void XplRSS::on_actionAbout_triggered()
{
	QMessageBox about(QMessageBox::NoIcon,"About XplRSS", "<h1>XplRSS v1.0</h1><strong>XplRSS &copy; 2013 Aramande and Hackular.com</strong>"
							"<p>This software is released under the GNU GPL v2 and is free to use and modify.<br />"
							"Any bugs are merely features that are yet to be implemented, please be patient.</p>");
	about.setTextFormat(Qt::RichText);
	about.exec();
}

void XplRSS::on_actionDate_Ascending_triggered(){
	 _sorter->setSortRole(DateRole);
	 _sorter->sort(0);
}
void XplRSS::on_actionDate_Descending_triggered(){
	_sorter->setSortRole(DateRole);
	_sorter->sort(0, Qt::DescendingOrder);
}
void XplRSS::on_actionRead_Ascending_triggered(){
	_sorter->setSortRole(ReadRole);
	_sorter->sort(0);
}
void XplRSS::on_actionRead_Descending_triggered(){
	_sorter->setSortRole(ReadRole);
	_sorter->sort(0, Qt::DescendingOrder);
}
void XplRSS::on_actionQuit_triggered()
{
	 saveFeedTree();
	 this->destroy();
	 qApp->quit();
}

void XplRSS::on_actionAdd_Branch_triggered()
{
	 Q
}
