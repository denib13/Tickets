#include "Hall.h"
#include <iomanip>

Hall::Hall()
{
	number = rows = seats = 0;
}

Hall::Hall(unsigned number, unsigned rows, unsigned seats)
{
	this->number = number;
	this->rows = rows;
	this->seats = seats;
}

unsigned Hall::getNumber() const
{
	return number;
}

unsigned Hall::getRows() const
{
	return rows;
}

unsigned Hall::getSeatsCount() const
{
	return seats;
}

void Hall::setNumber(unsigned number)
{
	if (number == 0)
		throw std::exception("A hall's number cannot be zero!");
	else
		this->number = number;
}

void Hall::setRows(unsigned rows)
{
	if (rows == 0)
		throw std::exception("A hall's number of rows cannot be zero!");
	else
		this->rows = rows;
}

void Hall::setSeats(unsigned seats)
{
	if (seats == 0)
		throw std::exception("Number of seats per row in a hall cannot be zero!");
	else
		this->seats = seats;
}

std::istream& operator>>(std::istream& stream, Hall& hall)
{
	unsigned number = 0, rows = 0, seats = 0;
	stream >> number >> rows >> seats;
	try
	{
		hall.setNumber(number);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	try
	{
		hall.setRows(rows);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	try
	{
		hall.setSeats(seats);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Hall& hall)
{
	stream << hall.number << std::setw(8) << hall.rows << std::setw(8) << hall.seats << std::endl;
	return stream;
}
