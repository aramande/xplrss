#ifndef FEEDTREE_H
#define FEEDTREE_H

#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QMessageBox>
#include <stack>

class FeedTree : public QStandardItemModel
{
	Q_OBJECT
public:
	explicit FeedTree(const QString &filename, QObject *parent = 0);

private:
	QString _filename;
	void read();
signals:

public slots:
	void pressed(QModelIndex);
	void update();
};

#endif // FEEDTREE_H
