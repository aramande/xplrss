#ifndef XPLRSS_H
#define XPLRSS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QList>
#include <QTimer>

#include "feedtree.h"
#include "rssmodel.h"

namespace Ui {
class XplRSS;
}

class XplRSS : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit XplRSS(QWidget *parent = 0);
    ~XplRSS();
    
private:
    Ui::XplRSS *ui;
    FeedTree *feedTree;
	 RssModel *feedList;
	 QTimer* timer;

	 void resizeEvent(QResizeEvent * event);

public slots:
	 void delay();
	 void scrollFix();
	private slots:
	 void on_actionAdd_Feed_triggered();
	 void on_actionOptions_triggered();
	 void on_actionAbout_triggered();
};

#endif // XPLRSS_H
