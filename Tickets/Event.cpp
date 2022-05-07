#include "Event.h"

Event::Event(const MyString& name, const Date& date, const Hall& hall)
{
	this->name = name;
	this->date = date;
	this->hall = hall;
}