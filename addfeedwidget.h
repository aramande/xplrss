#ifndef ADDFEEDWIDGET_H
#define ADDFEEDWIDGET_H

#include <QtCore>
#include <QtGui>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QLabel>
#include <QDebug>
#include <QPushButton>
#include <QSpacerItem>
#include <QLineEdit>
#include <QDir>

class AddFeedWidget : public QWidget
{
		Q_OBJECT
	public:
		explicit AddFeedWidget(QWidget *parent = 0);
	private:
		QRadioButton *feedSelect;
		QRadioButton *folderSelect;
		QLineEdit *inputField;

	signals:
		
	public slots:
		void added();
};

#endif // ADDFEEDWIDGET_H
