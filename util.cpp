#include "util.h"

QString wordWrap(const QString &str, int wrapLength, int &countLine)
{
	QString tempStr= str;
	int len = str.length();
	int pos = (wrapLength > len-1) ? len-1 : wrapLength;

	while(pos < len-1) {
		int tempPos = pos;
		while(tempStr.at(tempPos) != ' ' && tempPos > 0)
			tempPos--;
		tempStr.replace(tempPos,1,"<br />");
		countLine++;
		pos += tempPos;
	}
	return tempStr;
}

qulonglong hash(const char *str, unsigned long long salt){
	const unsigned long long mulp = 2654435789;
	salt ^= 104395301;
	while (*str)
		 salt += (*str++ * mulp) ^ (salt >> 23);
	return salt;
}

const char* c_str(QString str1){
	QByteArray ba = str1.toLatin1();
	const char* c_str2 = ba.data();
	return c_str2;
}
