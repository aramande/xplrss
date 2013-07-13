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
	char* c_str2 = new char[ba.length()];
	strcpy(c_str2,ba.data());
	return c_str2;
}

Exception::Exception (const char* message, const char *file, int line) noexcept{
	QString temp;
	if(strlen(message) == 0)
		temp = QString("Exception at %1 (%2)").arg(QString(file), QString(line));
	else
		temp = QString("Exception at %1 (%2): %3").arg(QString(file), QString(line), QString(message));
	_message = c_str(temp);
}
Exception::Exception (const QString& message, const char *file, int line) noexcept{
	QString temp = QString("Exception at %1 (%2): %3").arg(QString(file), QString(line), message);
	_message = c_str(temp);
}
Exception::Exception (const std::exception& other) noexcept : _message(other.what()){}
Exception& Exception::operator= (const std::exception& other) noexcept{
	_message = other.what();
	return *this;
}
Exception::~Exception () noexcept{}

const char* Exception::what() const noexcept{
	return _message;
}
