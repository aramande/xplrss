#ifndef COMPOUNDMODEL_H
#define COMPOUNDMODEL_H

#include "rssmodel.h"
#include <QObject>

class CompoundModel : public RssModel
{
		Q_OBJECT
	public:
		explicit CompoundModel(Branch *branch, QWidget *parent = 0);

		RssItem* get(int) const;
		Iter<RssItem*> begin() const;
		Iter<RssItem*> end() const;
		QVariant data(const QModelIndex &index, int role) const;
		QMap<int, QVariant> itemData(const QModelIndex &index) const;
		int rowCount(const QModelIndex &parent=QModelIndex()) const;
		void loadUrl(const QString &urlstring = "");
	private:
		Branch *_branch;
		QList<RssModel*> _content;
		int _rowCount;
	protected:
	signals:
		
	public slots:
		
};

#endif // COMPOUNDMODEL_H
