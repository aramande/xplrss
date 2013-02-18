#ifndef UTIL_H
#define UTIL_H

#include <QString>
QString wordWrap(const QString &str, int wrapLength, int &countLine);
uint hash(const char *str);
const char* c_str(QString str1);

#endif // UTIL_H
