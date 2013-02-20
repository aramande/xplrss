#include "addfeedwidget.h"

AddFeedWidget::AddFeedWidget(QWidget *parent) :
	QWidget(parent)
{
	QVBoxLayout *layout = new QVBoxLayout(this);
	QHBoxLayout *buttonLayout = new QHBoxLayout();
	QHBoxLayout *lowerLayout = new QHBoxLayout();
	feedSelect = new QRadioButton("Feed");
	folderSelect = new QRadioButton("Category");
	inputField = new QLineEdit("Feed URL or Folder name");
	QPushButton *add = new QPushButton("Add");

	layout->addWidget(new QLabel("Adding: "));
	layout->addSpacerItem(new QSpacerItem(0,0));
	buttonLayout->addWidget(feedSelect);
	buttonLayout->addWidget(folderSelect);
	buttonLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
	layout->addLayout(buttonLayout);
	layout->addWidget(inputField);
	lowerLayout->addSpacerItem(new QSpacerItem(0,0,QSizePolicy::Expanding));
	lowerLayout->addWidget(add);
	layout->addLayout(lowerLayout);

	connect(add, SIGNAL(clicked()), this, SLOT(added()));

	setLayout(layout);
	show();
}

void AddFeedWidget::added(){
	qDebug() << "Feed added!" << inputField->text();
	this->destroy(true);
}
