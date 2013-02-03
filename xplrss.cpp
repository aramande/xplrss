#include "xplrss.h"
#include "ui_xplrss.h"

XplRSS::XplRSS(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::XplRSS)
{
    ui->setupUi(this);
}

XplRSS::~XplRSS()
{
    delete ui;
}
