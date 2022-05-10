#pragma once
#include "MyString.h"
#include "Date.h"
#include "Hall.h"
#include "Seats.h"
#include <iostream>

class Event
{
	MyString name;
	Date date;
	Hall hall;
	Seats seats;
public:
	friend class TicketCenter;
	Event();
	Event(const MyString&, const Date&, const Hall&);

	const MyString getName() const;
	const Date getDate() const;
	const Hall getHall() const;

	void setName(const MyString&);
	void setDate(const Date&);
	void setHall(const Hall&);

	friend std::istream& operator>>(std::istream&, Event&);
	friend std::ostream& operator<<(std::ostream&, const Event&);
};
bool operator==(const Event&, const Event&);