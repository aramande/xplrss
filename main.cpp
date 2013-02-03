#include "xplrss.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    XplRSS w;
    w.show();
    
    return a.exec();
}
