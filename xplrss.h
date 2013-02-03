#ifndef XPLRSS_H
#define XPLRSS_H

#include <QMainWindow>

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
};

#endif // XPLRSS_H
