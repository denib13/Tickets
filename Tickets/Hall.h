#pragma once
#include "Date.h"
#include <iostream>

class Hall
{
	unsigned number;
	unsigned rows;
	unsigned seats;

public:
	Hall();
	Hall(unsigned number, unsigned rows, unsigned seats);

	unsigned getNumber() const;
	unsigned getRows() const;
	unsigned getSeatsCount() const;

	void setNumber(unsigned number);
	void setRows(unsigned rows);
	void setSeats(unsigned seats);

	friend std::istream& operator>>(std::istream& stream, Hall& hall);
	friend std::ostream& operator<<(std::ostream& stream, const Hall& hall);
};
bool operator==(const Hall& lhs, const Hall& rhs);