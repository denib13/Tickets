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
	void copyFrom(const Seats&);
public:
	Seats();
	Seats(unsigned, unsigned);
	Seats(const Seats&);
	Seats(Seats&&);
	~Seats();
	
	const Status getStatus(unsigned, unsigned) const;

	Seats& operator=(const Seats&);
	Seats& operator=(Seats&&);

	void changeStatus(unsigned, unsigned, Status);
	void print() const;
};