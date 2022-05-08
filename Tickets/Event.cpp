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
	stream << event.name << std::setw(8) << event.date << std::setw(8) << event.hall.getNumber() << std::endl;
	return stream;
}
