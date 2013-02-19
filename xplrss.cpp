#include "xplrss.h"
#include "ui_xplrss.h"
#include "htmldelegate.h"
#include "rssmodel.h"
#include <QScrollBar>
#include <QListView>
#include <QDir>

XplRSS::XplRSS(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::XplRSS)
{
	ui->setupUi(this);
	ui->splitter->setSizes(QList<int>() << 200 << 390);

	//delete ui->listView;
	//ui->listView = new ListView();
	QString feedTreeFile = QString("%1/.xplrss/feedtree.cfg").arg(QDir::homePath());
	QFile testFile(feedTreeFile);
	if(!testFile.exists()){
		qDebug() <<	"Can't read feedtree file, generating it.";
		QDir dir;
		if(!dir.exists(QDir::homePath() + "/.xplrss")){
			 dir.mkdir(QDir::homePath() + "/.xplrss");
		}
		testFile.open(QFile::WriteOnly | QFile::Text);
		testFile.write("Default\n");
		testFile.flush();
		testFile.close();
	}

	feedTree = new FeedTree(feedTreeFile);
	feedList = new RssModel("http://davidr64.tumblr.com/rss"); // TODO: make dynamic later
	HTMLDelegate* delegate = new HTMLDelegate(ui->listView);

	QString css = "QListView { background: darkblue; }";

	ui->treeView->setModel(feedTree);
	ui->treeView->setHeaderHidden(true);
	ui->treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

	ui->listView->setModel(feedList);
	ui->listView->setItemDelegate(delegate);
	ui->listView->setResizeMode(QListView::Adjust);
	ui->listView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	ui->listView->setWordWrap(true);
	ui->listView->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
	ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->listView->setSelectionMode(QAbstractItemView::NoSelection);
	setStyleSheet(css);

	//Mouselistener connectors
	connect(ui->listView, SIGNAL(pressed(QModelIndex)), feedList, SLOT(pressed(QModelIndex)));
	connect(ui->treeView, SIGNAL(pressed(QModelIndex)), feedTree, SLOT(pressed(QModelIndex)));

	//Timer for the delay of scrollbug
	timer = new QTimer(this);
	timer->setSingleShot(true);

	//Scrollbug connectors
	connect(ui->listView, SIGNAL(clicked(QModelIndex)), this, SLOT(delay()));
	connect(feedList, SIGNAL(loaded()), this, SLOT(delay()));
	connect(timer, SIGNAL(timeout()), this, SLOT(scrollFix()));
}

XplRSS::~XplRSS()
{
	delete ui;
}

void XplRSS::resizeEvent(QResizeEvent * event){
	delay();
	if(event) return;
}

//This is a delay before the scrollfix
void XplRSS::delay(){
	timer->start(100);
}

//Fixes the scrollbug
void XplRSS::scrollFix(){
	//qDebug() << "Hello?";
	ui->listView->verticalScrollBar()->setSingleStep(25);
}

void XplRSS::on_actionAdd_Feed_triggered()
{
	QMessageBox::information(this, "Adding feed", "Adding feed options go here! Yay!");
	// TODO: To be implemented
}

void XplRSS::on_actionOptions_triggered()
{
	QMessageBox::information(this, "Options", "Options go here! Yay!");
}

void XplRSS::on_actionAbout_triggered()
{
	QMessageBox about(QMessageBox::NoIcon,"About XplRSS", "<strong>XplRSS &copy; 2013 Aramande and Hackular.com</strong>"
							"<p>This software is released under the GNU GPL v2 and is free to use and modify.<br />"
							"Any bugs are merely features that are yet to be implemented, please be patient.</p>");
	about.setTextFormat(Qt::RichText);
	about.exec();
}
