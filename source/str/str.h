#ifndef STRINGS_H
#define STRINGS_H

#include <sstream>
#include <string>

namespace str
{
	class string : public std::string
	{
		public:

			string ();

			template <class T>
			string (T t);

			template <class T>
			string& operator = (T t);

			template <class T>
			string& operator += (T t);

			template <class T>
			string& operator << (T t);
	};


	template <class T>
	string::string (T t)
	{
		*this = t;
	}

	template <class T>
	string& string::operator = (T t)
	{
		std::ostringstream oss;
		oss << t;
		this->assign(oss.str());
		return *this;
	}

	template <class T>
	string& string::operator += (T t)
	{
		std::ostringstream oss;
		oss << t;
		this->append(oss.str());
		return *this;
	}

	template <class T>
	string& string::operator << (T t)
	{
		*this += t;
		return *this;
	}
}


#endif // STRINGS_H
