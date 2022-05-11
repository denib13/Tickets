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
	Status seatStatus;
public:
	friend class TicketCenter;
	Reservation();
	Reservation(const Event& event, unsigned row, unsigned seat, Status seatStatus, const MyString& password, const MyString& note);

	void setEvent(const Event& event);
	void setPassword(const MyString& password);
	void setNote(const MyString& note);
	void setRow(unsigned row);
	void setSeat(unsigned seat);
	void setStatus(Status newStatus);

	friend std::istream& operator>>(std::istream& stream, Reservation& reservation);
	friend std::ostream& operator<<(std::ostream& stream, const Reservation& reservation);
};