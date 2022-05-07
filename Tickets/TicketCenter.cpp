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
	count = other.count;

	halls = new Hall[count];
	for (size_t i = 0; i < count; i++)
	{
		halls[i] = other.halls[i];
	}
}

int TicketCenter::getHallIndex(unsigned number)
{
	for (size_t i = 0; i < count; i++)
	{
		if (halls[i].getNumber() == number)
			return i;
	}
	return -1;
}

TicketCenter::TicketCenter(const char* filePath)
{
	std::fstream file(filePath, std::ios::in);
	if (!file.is_open())
		throw std::exception("Error reading from file!");

	count = getNumberOfLines(file) - 1;

	//първият ред от файла е заглавен ред, затова го прочитаме и пропускаме
	char buff[1024];
	file.getline(buff, 1023);

	halls = new Hall[count];
	for (size_t i = 0; i < count; i++)
	{
		file >> halls[i];
		std::cout << halls[i];
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

TicketCenter::TicketCenter(const TicketCenter& other)
{
	copyFrom(other);
}

TicketCenter::TicketCenter(TicketCenter&& other)
{
	count = other.count;
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
		count = other.count;
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
	//не трябва да са всички данни, само номер на залата! не създаваме обект, намираме го
	//има ли в тази зала друго представление на тази дата?
	//add validation
	Event newEvent(name, date, halls[hallIndex]);
	//write to file
}

