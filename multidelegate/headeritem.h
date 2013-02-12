#ifndef HEADERITEM_H
#define HEADERITEM_H

class QString;

class HeaderItem
{
	public:

		HeaderItem(QString text = "");
		~HeaderItem();

		void paint(QPainter*, const QStyleOptionViewItem&, const QModelIndex&) const;

	private:
		QString itemText;
};

Q_DECLARE_METATYPE(HeaderItem)

#endif
