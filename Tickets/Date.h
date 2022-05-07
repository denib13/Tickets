#pragma once
#include <iostream>

class Date
{
	unsigned day;
	unsigned month;
	unsigned year;

	bool isLeapYear();

	unsigned daysInMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

public:
	Date();
	Date(unsigned day, unsigned month, unsigned year);

	void setDay(unsigned day);
	void setMonth(unsigned month);
	void setYear(unsigned year);

	unsigned getDay() const;
	unsigned getMonth() const;
	unsigned getYear() const;

	friend std::istream& operator>>(std::istream& stream, Date& date);
	friend std::ostream& operator<<(std::ostream& stream, const Date& date);
};