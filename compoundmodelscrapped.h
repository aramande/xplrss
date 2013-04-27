#ifndef COMPOUNDMODEL_H
#define COMPOUNDMODEL_H

#include "rssmodel.h"
#include <QObject>

class CompoundModel : public RssModel
{
		Q_OBJECT
	public:
		explicit CompoundModel(Branch *branch, QWidget *parent = 0);

		QVariant data(const QModelIndex &index, int role) const;
		QMap<int, QVariant> itemData(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent=QModelIndex()) const;
		void loadUrl(const QString &urlstring = "");
		QModelIndex index(int row, int column, const QModelIndex &parent) const;
		QMimeData* mimeData( const QList<QStandardItem *> items ) const;
	private:
		Branch *_branch;
		QList<RssModel*> _content;
		int _rowCount;
	protected:
	signals:
		
	public slots:
		void gotFeed(QStandardItemModel* model);
		void gotRowInsert(const QModelIndex& parent, int start, int end);
};

#endif // COMPOUNDMODEL_H
