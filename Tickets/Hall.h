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

	void setNumber(unsigned);
	void setRows(unsigned);
	void setSeats(unsigned);

	friend std::istream& operator>>(std::istream&, Hall&);
	friend std::ostream& operator<<(std::ostream&, const Hall&);
};