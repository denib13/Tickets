#pragma once

enum Status
{
	available,
	reserved,
	sold
};
class Seats {
	Status** seats;
	unsigned rows;
	unsigned cols;

	void free();
	void copyFrom(const Seats& other);
public:
	Seats();
	Seats(unsigned rows, unsigned cols);
	Seats(const Seats& other);
	Seats(Seats&& other);
	~Seats();
	
	const Status getStatus(unsigned row, unsigned col) const;

	Seats& operator=(const Seats& other);
	Seats& operator=(Seats&& other);

	void changeStatus(unsigned row, unsigned seat, Status newStatus);
	void print() const;
};