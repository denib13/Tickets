#include "Event.h"
#include <iomanip>

Event::Event() : date(), hall()
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
}

std::istream& operator>>(std::istream& stream, Event& event)
{
	MyString name;
	Date date;
	Hall hall;
	stream >> name >> date >> hall;
	event.setName(name);
	event.setDate(date);
	event.setHall(hall);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Event& event)
{
	stream << event.name << std::setw(8) << event.date << std::setw(8) << event.hall << std::endl;
	return stream;
}

bool operator==(const Event& lhs, const Event& rhs)
{
	return(lhs.getName() == rhs.getName() && lhs.getDate() == rhs.getDate() 
		&& lhs.getHall() == rhs.getHall());
}
