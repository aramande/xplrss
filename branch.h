#ifndef BRANCH_H
#define BRANCH_H

#include <QStandardItem>

class Branch : public QStandardItem
{
	public:
		explicit Branch(const QString &label);
		explicit Branch(const Branch &other);
		~Branch();
		void setText(const QString &text);
		void setData(const QVariant &value, int role);
};

#endif // BRANCH_H
