#include "Event.h"
#include <iomanip>

Event::Event() : date(), hall(), seats()
{
	name = "Empty event";
}

Event::Event(const MyString& name, const Date& date, const Hall& hall)
{
	setName(name);
	setDate(date);
	setHall(hall);
}

const MyString Event::getName() const
{
	return name;
}

const Date Event::getDate() const
{
	return date;
}

const Hall Event::getHall() const
{
	return hall;
}

void Event::setName(const MyString& name)
{
	this->name = name;
}

void Event::setDate(const Date& date)
{
	this->date = date;
}

void Event::setHall(const Hall& hall)
{
	this->hall = hall;
	Seats seats(hall.getRows(), hall.getSeatsCount());
	this->seats = seats;
}

std::istream& operator>>(std::istream& stream, Event& event)
{
	Date date;
	Hall hall;

	char nameString[256];
	stream.getline(nameString, 255, '|');
	stream.ignore();
	stream >> date;
	stream.ignore();
	stream>>hall;
	stream.ignore();

	MyString name(nameString);
	event.setName(name);
	event.setDate(date);
	event.setHall(hall);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Event& event)
{
	stream << event.name << '|' << event.date << '|' << event.hall/* << std::endl*/;
	return stream;
}

bool operator==(const Event& lhs, const Event& rhs)
{
	return(lhs.getName() == rhs.getName() && lhs.getDate() == rhs.getDate() 
		&& lhs.getHall() == rhs.getHall());
}
