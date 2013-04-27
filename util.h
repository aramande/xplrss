#ifndef UTIL_H
#define UTIL_H

#include <QString>
#include <exception>

#define ATTR_READER(type,variable) inline type variable () const {return _##variable ; }
#define ATTR_WRITER(type,variable) inline void variable (type variable){ _##variable = variable ; }
#define ATTR_ACCESSOR(type,variable) ATTR_READER(type,variable) ATTR_WRITER(type,variable)

#define THROW(message) throw Exception(message, __FILE__, __LINE__);

template <typename T> class Iter;
template <typename T> class LinkedIter;

enum{
	RssRole = Qt::UserRole + 2,
	UrlRole,
	SaveRole,
	TextRole,
	ReadRole,
	DateRole,
	ContentRole
};

QString wordWrap(const QString &str, int wrapLength, int &countLine);
qulonglong hash(const char *str, unsigned long long salt = 0);
const char* c_str(QString str1);

template <typename T>
class Iterable{
	public:
		virtual T get(int pos) const = 0;
		virtual Iter<T> begin() const = 0;
		virtual Iter<T> end() const = 0;
};

template <typename T>
class Iter
{
	public:
		Iter (const Iterable<T>* p_vec, int pos) : _pos( pos ) , _p_vec( p_vec ) { }

		// these three methods form the basis of an iterator for use with
		// a range-based for loop
		bool operator!=(const Iter& other) const{
			return _pos != other._pos;
		}

		// this method must be defined after the definition of IntVector
		// since it needs to use it

		T operator*() const{
			return _p_vec->get( _pos );
		}

		const Iter<T>& operator++(){
			++_pos;
			// although not strictly necessary for a range-based for loop
			// following the normal convention of returning a value from
			// operator++ is a good idea.
			return *this;
		}

	private:
		int _pos;
		const Iterable<T> *_p_vec;
};

class Exception : public std::exception{
	const char* _message;
public:
	Exception (const char* message, const char* file, int line) noexcept;
	Exception (const QString& message, const char* file, int line) noexcept;
	Exception (const std::exception&) noexcept;
	Exception& operator= (const std::exception&) noexcept;
	~Exception ();
	virtual const char* what() const noexcept;
};

#endif // UTIL_H
