#pragma once
#include "MyString.h"
#include "Date.h"
#include "Hall.h"
#include <iostream>

class Event
{
	MyString name;
	Date date;
	Hall hall;

public:
	friend class TicketCenter;
	Event();
	Event(const MyString&, const Date&, const Hall&);

	void setName(const MyString&);
	void setDate(const Date&);
	void setHall(const Hall&);

	friend std::istream& operator>>(std::istream&, Event&);
	friend std::ostream& operator<<(std::ostream&, const Event&);
};