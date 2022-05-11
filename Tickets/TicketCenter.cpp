#include "TicketCenter.h"
#include <fstream>
#include <iomanip>
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

int TicketCenter::getHallIndex(unsigned hallNumber) const
{
	for (size_t i = 0; i < hallsCount; i++)
	{
		if (halls[i].getNumber() == hallNumber)
			return i;
	}
	return -1;
}

void TicketCenter::writeEventsToFile(const char* filePath) const
{
	std::fstream file(filePath, std::ios::out | std::ios::trunc);
	if (!file.is_open())
		throw std::exception("Error writing to file!");
	
	for (size_t i = 0; i < events.count; i++)
	{
		file << events.data[i] << '\n';
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
void TicketCenter::writeReservationsToFile(const char* filePath) const
{
	std::fstream file(filePath, std::ios::out | std::ios::trunc);
	if (!file.is_open())
		throw std::exception("Error writing to file!");

	for (size_t i = 0; i < reservations.count; i++)
	{
		file << reservations.data[i] << '\n';
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
void TicketCenter::loadReservationsList(const char* filePath)
{
	std::fstream file(filePath, std::ios::in);
	if (!file.is_open())
		throw std::exception("Error reading from file!");

	unsigned size = getNumberOfLines(file);//ako ima zaglaven red da e -1
	file.seekg(0, std::ios::beg);
	////първият ред от файла е заглавен ред, затова го прочитаме и пропускаме
	//char buff[1024];
	//file.getline(buff, 1023);

	for (size_t i = 0; i < size; i++)
	{
		Reservation newReservation;
		file >> newReservation;
		reservations.add(newReservation);
		size_t eventIndex = findEvent(newReservation.event.name, newReservation.event.date);
		events[eventIndex].seats.changeStatus(newReservation.row, newReservation.seat, newReservation.seatStatus);
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

void TicketCenter::loadEventsList(const char* filePath)
{
	std::fstream file(filePath, std::ios::in);
	if (!file.is_open())
		throw std::exception("Error reading from file!");

	unsigned size = getNumberOfLines(file);//ako ima zaglaven red da e -1
	file.seekg(0, std::ios::beg);
	////първият ред от файла е заглавен ред, затова го прочитаме и пропускаме
	//char buff[1024];
	//file.getline(buff, 1023);

	for (size_t i = 0; i < size; i++)
	{
		Event newEvent;
		file >> newEvent;
		events.add(newEvent);
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

TicketCenter::TicketCenter(const char* filePath)
{
	loadEventsList(eventsFile);
	loadReservationsList(reservationsFile);

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
	writeEventsToFile(eventsFile);
	writeReservationsToFile(reservationsFile);
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
		//just for testing purposes
		std::cout << newEvent << std::endl;
		std::cin.ignore();
		events.add(newEvent);
	}
	else
	{
		std::cout << "Hall is buzy on this date!" << std::endl;
		std::cin.ignore();
	}
		
	//add validation
}

void TicketCenter::availableSeats()
{
	MyString eventName;
	Date eventDate;
	std::cout << "Enter event name: ";
	std::cin >> eventName;
	std::cout << "Enter event date: ";
	std::cin >> eventDate;

	size_t eventIndex = findEvent(eventName, eventDate);
	if (eventIndex != -1)
	{
		events[eventIndex].seats.print();
		std::cin.ignore();
	}
	else
		std::cout << "Such event does not exist!";
}

void TicketCenter::reserveTicket()
{
	MyString eventName, password, note;
	Date eventDate;
	unsigned row, seat;

	std::cout << "Enter event name: ";
	std::cin >> eventName;
	std::cout << "Enter event date: ";
	std::cin >> eventDate;

	size_t eventIndex = findEvent(eventName, eventDate);
	if (eventIndex != -1)
	{
		std::cout << "Enter row: ";
		std::cin >> row;
		std::cout << "Enter seat: ";
		std::cin >> seat;
		std::cin.ignore();
		
		if (events[eventIndex].seats.getStatus(row, seat) == available)
		{
			std::cout << "Enter password: ";
			std::cin >> password;
			std::cout << "Enter note or press enter to skip: ";
			std::cin >> note;

			Reservation newReservation(events[eventIndex], row, seat, reserved, password, note);
			std::cout << newReservation;
			reservations.add(newReservation);
			events[eventIndex].seats.changeStatus(row, seat, reserved);
		}
		else
			std::cout << "Seat is not available!" << std::endl;
	}
	else
		std::cout << "Such event does not exist!";
}

void TicketCenter::cancelReservation()
{
	MyString eventName;
	Date eventDate;
	unsigned row, seat;
	MyString password;

	std::cout << "Enter event name: ";
	std::cin >> eventName;
	std::cout << "Enter event date: ";
	std::cin >> eventDate;

	size_t eventIndex = findEvent(eventName, eventDate);
	if (eventIndex != -1)
	{
		std::cout << "Enter row: ";
		std::cin >> row;
		std::cout << "Enter seat: ";
		std::cin >> seat;
		std::cin.ignore();

		size_t reservationIndex = findReservation(events[eventIndex], row, seat);
		if (reservationIndex != -1)
		{
			std::cout << "Enter password: ";
			std::cin >> password;
			if (reservations[reservationIndex].password == password)
			{
				reservations.removeAtIndex(reservationIndex);
				events[eventIndex].seats.changeStatus(row, seat, available);
			}
			else
				std::cout << "Wrong password!";
		}
		else
			std::cout << "Such reservation does not exist!";
	}
	else
		std::cout << "Such event does not exist!";
}

void TicketCenter::buyTicket()
{
	MyString eventName;
	Date eventDate;
	unsigned row, seat;

	std::cout << "Enter event name: ";
	std::cin >> eventName;
	std::cout << "Enter event date: ";
	std::cin >> eventDate;

	size_t eventIndex = findEvent(eventName, eventDate);
	if (eventIndex != -1)
	{
		std::cout << "Enter row: ";
		std::cin >> row;
		std::cout << "Enter seat: ";
		std::cin >> seat;
		std::cin.ignore();

		Status seatStatus = events[eventIndex].seats.getStatus(row, seat);
		if (seatStatus == available)
		{
			Reservation newReservation(events[eventIndex], row, seat, sold, "", "");
			reservations.add(newReservation);
			events[eventIndex].seats.changeStatus(row, seat, sold);
		}
		else if (seatStatus == reserved)
		{
			MyString password;
			std::cout << "Seat is reserved. Enter reservation password: ";
			std::cin >> password;

			size_t reservationIndex = findReservation(events[eventIndex], row, seat);
			if (reservations[reservationIndex].password == password)
			{
				reservations[reservationIndex].seatStatus = sold;
				events[eventIndex].seats.changeStatus(row, seat, sold);
			}
			else
				std::cout << "Wrong password!";
		}
		else
			std::cout << "Seat is already sold!";
	}
	else
		std::cout << "Such event does not exist!";
}

void TicketCenter::listOfBoughtTickets()//not how it should function
{
	MyString hallName;

	std::cout << "Enter hall number or ALL: ";
	std::cin >> hallName;

	if (hallName == "ALL")
	{
		std::cout << "Name" << std::setw(8) << "Date" << std::setw(8) << "Hall number" << std::setw(8) << "Rows" << std::setw(8) << "Seats" << std::setw(8) << "Sold Seats" << std::endl;
		for (size_t i = 0; i < events.count; i++)
		{
			std::cout << events[i] << std::setw(8) << events[i].seats.getSoldSeatsCount() << std::endl;
		}
	}
	else
	{
		int hallNumber = atoi(hallName.getString());
		size_t hallIndex = getHallIndex(hallNumber);
		if (hallIndex != -1)
		{
			std::cout << "Name" << std::setw(8) << "Date" << std::setw(8) << "Hall number" << std::setw(8) << "Rows" << std::setw(8) << "Seats" << std::setw(8) << "Sold Seats" << std::endl;
			for (size_t i = 0; i < events.count; i++)
			{
				if (events[i].hall.getNumber() == hallNumber)
					std::cout << events[i] << std::setw(8) << events[i].seats.getSoldSeatsCount() << std::endl;
			}
		}
		else
			std::cout << "Such hall does not exist!";
 	}
}


bool TicketCenter::isHallBuzy(const Hall& hall, const Date& date) const
{
	for (size_t i = 0; i < events.count; i++)
	{
		if (events.data[i].hall == hall && events.data[i].date == date)
			return true;
	}
	return false;
}

size_t TicketCenter::findEvent(const MyString& name, const Date& date) const
{
	for (size_t i = 0; i < events.count; i++)
	{
		if (events.data[i].name == name && events.data[i].date == date)
			return i;
	}
	return -1;
}

size_t TicketCenter::findReservation(const Event& event, unsigned row, unsigned seat) const
{
	for (size_t i = 0; i < reservations.count; i++)
	{
		if (reservations.data[i].event == event && reservations.data[i].row == row &&
			reservations.data[i].seat == seat)
			return i;
	}
	return -1;
}

