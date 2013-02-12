#ifndef SECTIONITEM_H
#define SECTIONITEM_H

class QString;

class SectionItem
{
	public:

		SectionItem(QString text = "");
		~SectionItem();

		void paint(QObject *parent, QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;
		QSize sizeHint(QObject *parent, const QStyleOptionViewItem& option, const QModelIndex& index) const;

	private:
		QString itemText;
};

Q_DECLARE_METATYPE(SectionItem)

#endif
