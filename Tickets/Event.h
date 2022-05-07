#pragma once
#include "MyString.h"
#include "Date.h"
#include "Hall.h"

class Event
{
	MyString name;
	Date date;
	Hall hall;

public:
	Event(const MyString&, const Date&, const Hall&);
};