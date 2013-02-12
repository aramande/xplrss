#ifndef XPLRSS_H
#define XPLRSS_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QList>

#include "feedtree.h"

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
    QStandardItemModel *feedList;
};

#endif // XPLRSS_H
