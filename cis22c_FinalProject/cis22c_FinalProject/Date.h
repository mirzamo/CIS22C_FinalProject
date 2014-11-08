#ifndef DATE_H
#define DATE_H

#include <string>
#include <sstream>

class Date
{
private:
    int m_day, m_month, m_year;

public:

    Date(int d, int m, int y)
    {
        m_day = d;
        m_month = m;
        m_year = y;
    }

    int getDay() const
    {
        return m_day;
    }

    int getMonth() const
    {
        return m_month;
    }

    int getYear() const
    {
        return m_year;
    }

    virtual std::string  to_string()
    {
        std::stringstream s;
        s << getMonth() << "/" << getDay() << "/" << getYear() ;
        return s.str();
    }
};
#endif

