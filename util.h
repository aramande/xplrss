#ifndef UTIL_H
#define UTIL_H

#include <QString>

#define ATTR_READER(type,variable) inline type variable () const {return _##variable ; }
#define ATTR_WRITER(type,variable) inline void variable (type variable){ _##variable = variable ; }
#define ATTR_ACCESSOR(type,variable) ATTR_READER(type,variable) ATTR_WRITER(type,variable)


enum{
	RssRole = Qt::UserRole + 2,
	UrlRole,
	SaveRole,
	TextRole
};

QString wordWrap(const QString &str, int wrapLength, int &countLine);
qulonglong hash(const char *str, unsigned long long salt = 0);
const char* c_str(QString str1);
#endif // UTIL_H
