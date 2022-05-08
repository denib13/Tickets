#pragma once
#include "Event.h"
#include "MyString.h"
#include <iostream>

class Reservation
{
	Event event;
	MyString password;
	MyString note;
	unsigned row;
	unsigned seat;
public:
	friend class TicketCenter;
	Reservation();
	Reservation(const Event&, unsigned, unsigned, const MyString&, const MyString&);

	void setEvent(const Event&);
	void setPassword(const MyString&);
	void setNote(const MyString&);
	void setRow(unsigned);
	void setSeat(unsigned);

	friend std::istream& operator>>(std::istream&, Reservation&);
	friend std::ostream& operator<<(std::ostream&, const Reservation&);
};