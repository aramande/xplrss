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

uint hash(const char *str){
	 uint h = 0;
	 while (*str)
		 h = h << 1 ^ *str++;
	 return h;
}

const char* c_str(QString str1){
	QByteArray ba = str1.toLatin1();
	const char* c_str2 = ba.data();
	return c_str2;
}
