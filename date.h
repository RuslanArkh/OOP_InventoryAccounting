#ifndef DATE_H
#define DATE_H
#include <iostream>

class Date
{
public:

	Date();
	Date(int _year, int _month, int _day);
	Date(const char* _yyyyMMDD, char _sep = '/');
	void Print(char _sep = '/');
	bool IsLeapYear() const;

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

	/* Lection 3 */
	//	Declaration of Copy Constructor
	Date(const Date & _d);
	/* End of lection 3 */

	/* Lection 4 */
	bool operator == (const Date & d) const;
	bool operator != (const Date & d) const;
	bool operator < (const Date & d) const;
	bool operator <= (const Date & d) const;
	bool operator > (const Date & d) const;
	bool operator >= (const Date & d) const;

	/* End of lection 4 */

	/* Lection 5 */
	const char * ToString(char _sep) const;

private:

	bool IsValid() const;

	int m_Year, m_Month, m_Day;

	/* Lection 5 */
	//	Буфер для строкового представления. Можно изменять даже в строковых методах
	mutable char m_tempBuf[11];
	//	Флаг валидности содержимого буфера
	mutable bool m_BufferValid;

	struct StringRepr
	{
		char m_tempBuf[11];
		bool m_isValid;
	};
	StringRepr * m_pStringRepr;
};

inline int Date::GetYear() const
{
	return m_Year;
}

inline int Date::GetMonth() const
{
	return m_Month;
}

inline int Date::GetDay() const
{
	return m_Day;
}

inline bool Date::operator == (const Date & d) const
{
	/*return	m_Year == d.GetYear() && 
			m_Month == d.GetMonth() && 
			m_Day == d.GetDay();*/
	return !(d < *this) && !(*this < d);
}

inline bool Date::operator != (const Date & d) const
{
	//return !(*this == d);
	return (d < *this) || (*this < d);
}



//	GLOBAL OPERATORS

/*
inline bool operator == (const Date & d1, const Date & d2)
{
	return	d1.GetYear() == d2.GetYear() &&
			d1.GetMonth() == d2.GetMonth() &&
			d1.GetDay() == d2.GetDay();
}

inline bool operator != (const Date & d1, const Date & d2)
{
	return !(d1 == d2);
}
*/

std::ostream & operator << (std::ostream & o, const Date & d);
std::istream & operator >> (std::istream & i, Date & d);

#endif