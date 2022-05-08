#include "Date.h"
#include <iostream>

bool Date::isLeapYear()
{
	return (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0));
}

Date::Date()
{
	day = month = year = 0;
}

Date::Date(unsigned day, unsigned month, unsigned year)
{
	setMonth(month);
	setYear(year);
	setDay(day);
}

void Date::setDay(unsigned day)
{
	if (day == 0)
		throw std::exception("Out of range exception");
	else if (month == 2)
	{
		if (isLeapYear() && day <= 29)
			this->day = day;
		else if(day <= daysInMonth[1])
			this->day = day;
		else
			throw std::exception("Out of range exception");
	}
	else
	{
		if (day <= daysInMonth[month - 1])
			this->day = day;
		else
			throw std::exception("Out of range exception");
	}
}

void Date::setMonth(unsigned month)
{
	if (1 <= month && month <= 12)
		this->month = month;
	else
		throw std::exception("Out of range exception");
}

void Date::setYear(unsigned year)
{
	if (year < 2022)
		throw std::exception("Out of range exception");
	else
		this->year = year;
}

unsigned Date::getDay() const
{
	return day;
}

unsigned Date::getMonth() const
{
	return month;
}

unsigned Date::getYear() const
{
	return year;
}

std::istream& operator>>(std::istream& stream, Date& date)
{
	unsigned day, month, year;
	stream >> day;
	stream.ignore();
	stream >> month;
	stream.ignore();
	stream >> year;
	date.setYear(year);
	date.setMonth(month);
	date.setDay(day);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Date& date)
{
	if (date.day < 10)
		stream << '0';
	stream << date.day << "/";
	if (date.month < 10)
		stream << '0';
	stream << date.month << "/" << date.year;
	return stream;
}

bool operator==(const Date& lhs, const Date& rhs)
{
	return (lhs.getDay() == rhs.getDay() && lhs.getMonth() == rhs.getMonth()
		&& lhs.getYear() == rhs.getYear());
}
