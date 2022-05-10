#include "Seats.h"
#include <iostream>

void Seats::free()
{
	for (size_t i = 0; i < rows; i++)
	{
		delete[] seats[i];
	}
	delete[] seats;
}

void Seats::copyFrom(const Seats& other)
{
	rows = other.rows;
	cols = other.cols;

	seats = new Status * [rows];
	for (size_t i = 0; i < rows; i++)
	{
		seats[i] = new Status[cols];
		for (size_t j = 0; j < cols; j++)
		{
			seats[i][j] = other.seats[i][j];
		}
	}
}

Seats::Seats()
{
	rows = cols = 0;
	seats = nullptr;
}

Seats::Seats(unsigned rows, unsigned cols)
{
	this->rows = rows;
	this->cols = cols;

	seats = new Status*[rows];
	for (size_t i = 0; i < rows; i++)
	{
		seats[i] = new Status[cols];
		for (size_t j = 0; j < cols; j++)
		{
			seats[i][j] = Status::available;
		}
	}
}

Seats::Seats(const Seats& other)
{
	copyFrom(other);
}

Seats::Seats(Seats&& other)
{
	rows = other.rows;
	cols = other.cols;
	seats = other.seats;

	other.seats = nullptr;
}

Seats::~Seats()
{
	free();
}

const Status Seats::getStatus(unsigned row, unsigned col) const
{
	if (0 < row && row <= rows && 0 < col && col <= cols)
		return seats[row - 1][col - 1];
	throw std::exception("Seat does not exist!");
}

Seats& Seats::operator=(const Seats& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Seats& Seats::operator=(Seats&& other)
{
	if (this != &other)
	{
		free();
		rows = other.rows;
		cols = other.cols;
		seats = other.seats;

		other.seats = nullptr;
	}
	return *this;
}

void Seats::changeStatus(unsigned row, unsigned seat, Status newStatus)
{
	seats[row - 1][seat - 1] = newStatus;
}

void Seats::print() const
{
	std::cout << "available seats = o, sold seats = x: " << std::endl;
	for (size_t i = 0; i < rows; i++)
	{
		for (size_t j = 0; j < cols; j++)
		{
			if (seats[i][j] == Status::sold)
				std::cout << "x ";
			else
				std::cout << "o ";
		}
		std::cout << std::endl;
	}
}
