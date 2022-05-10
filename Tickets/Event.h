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
	Event(const MyString& name, const Date& date, const Hall& hall);

	const MyString getName() const;
	const Date getDate() const;
	const Hall getHall() const;

	void setName(const MyString& name);
	void setDate(const Date& date);
	void setHall(const Hall& hall);

	friend std::istream& operator>>(std::istream& stream, Event& event);
	friend std::ostream& operator<<(std::ostream& stream, const Event& event);
};
bool operator==(const Event& lhs, const Event& rhs);