#include "TicketCenter.h"
#include <fstream>
#include "MyString.h"
#include "Event.h"

int getNumberOfLines(std::fstream& file)
{
	int count = 0;

	unsigned currPosition = file.tellg();
	file.seekg(0, std::ios::beg);

	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1023);

		count++;
		file.peek();
	}

	file.clear();
	file.seekg(currPosition, std::ios::beg);
	return count;
}

void TicketCenter::free()
{
	delete[] halls;
}

void TicketCenter::copyFrom(const TicketCenter& other)
{
	hallsCount = other.hallsCount;

	halls = new Hall[hallsCount];
	for (size_t i = 0; i < hallsCount; i++)
	{
		halls[i] = other.halls[i];
	}
	events = other.events;
	reservations = other.reservations;
}

int TicketCenter::getHallIndex(unsigned number)
{
	for (size_t i = 0; i < hallsCount; i++)
	{
		if (halls[i].getNumber() == number)
			return i;
	}
	return -1;
}

TicketCenter::TicketCenter(const char* filePath) : events(eventsFile), reservations(reservationsFile)
{
	std::fstream file(filePath, std::ios::in);
	if (!file.is_open())
		throw std::exception("Error reading from file!");

	hallsCount = getNumberOfLines(file) - 1;

	//първият ред от файла е заглавен ред, затова го прочитаме и пропускаме
	char buff[1024];
	file.getline(buff, 1023);

	halls = new Hall[hallsCount];
	for (size_t i = 0; i < hallsCount; i++)
	{
		file >> halls[i];
		//std::cout << halls[i];
	}
	
	try
	{
		file.close();
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}

TicketCenter::TicketCenter(const TicketCenter& other) : events(other.events), reservations(other.reservations)
{
	copyFrom(other);
}

TicketCenter::TicketCenter(TicketCenter&& other) : events(other.events), reservations(other.reservations)
{
	hallsCount = other.hallsCount;
	halls = other.halls;

	other.halls = nullptr;
}

TicketCenter::~TicketCenter()
{
	free();
}

TicketCenter& TicketCenter::operator=(const TicketCenter& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

TicketCenter& TicketCenter::operator=(TicketCenter&& other)
{
	if (this != &other)
	{
		free();
		hallsCount = other.hallsCount;
		halls = other.halls;

		other.halls = nullptr;
	}
	return *this;
}

void TicketCenter::newEvent()
{
	MyString name;
	Date date;
	unsigned hallNum;

	std::cout << "Enter event name: ";
	std::cin >> name;
	std::cout << "Enter event date: "; //fix exceptions catching issues
	std::cin >> date;

	unsigned hallIndex;
	do
	{
		std::cout << "Enter event hall number: ";
		std::cin >> hallNum;
		hallIndex = getHallIndex(hallNum);
	} while (hallIndex == -1);

	if (!isHallBuzy(halls[hallIndex], date))
	{
		Event newEvent(name, date, halls[hallIndex]);
		std::cout << newEvent << std::endl;
		std::cin.ignore();
		events.add(newEvent);
	}
	else
		std::cout << "Hall is buzy on this date!";
	//add validation
}

bool TicketCenter::isHallBuzy(const Hall& hall, const Date& date) const
{
	for (size_t i = 0; i < events.count; i++)
	{
		if (events.data->hall == hall && events.data->date == date)
			return true;
	}
	return false;
}

