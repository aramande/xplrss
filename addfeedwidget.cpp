#include "addfeedwidget.h"
#include "xplrss.h"
#include "feed.h"
#include "branch.h"

AddFeedWidget::AddFeedWidget(QWidget *parent) :
	QWidget(NULL)
{
	_parent = parent;
	QVBoxLayout *layout = new QVBoxLayout(this);
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	QHBoxLayout *lowerLayout = new QHBoxLayout();
	feedSelect = new QRadioButton("Feed");
	branchSelect = new QRadioButton("Branch");
	inputField = new QLineEdit("");
	QPushButton *add = new QPushButton("Add");

	layout->addSpacerItem(new QSpacerItem(0,0));
	buttonLayout->addWidget(feedSelect);
	buttonLayout->addWidget(branchSelect);
	buttonLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
	layout->addLayout(buttonLayout);
	layout->addWidget(new QLabel("Feed URL or Branch name:"));
	layout->addWidget(inputField);
	lowerLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
	lowerLayout->addWidget(add);
	layout->addLayout(lowerLayout);

	connect(add, SIGNAL(clicked()), this, SLOT(added()));

	setLayout(layout);

	show();
}

void AddFeedWidget::added(){
	qDebug() << "Adding a new item.";
	destroy(true);
	XplRSS* mainWin = static_cast<XplRSS*>(_parent);
	if(feedSelect->isChecked()){
		qDebug() << "Feed added!" << inputField->text();
		mainWin->addToFeedTree(new Feed(inputField->text(), "", "", mainWin));
	}
	else if(branchSelect->isChecked()){
		qDebug() << "Branch added!" << inputField->text();
		mainWin->addToFeedTree(new Branch(inputField->text()));
	}
}
