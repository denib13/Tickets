#pragma once
#include "Hall.h"
#include "Reservation.h"
#include "List.hpp"

class TicketCenter
{
	Hall* halls;
	List<Event> events;
	List<Reservation> reservations;
	unsigned hallsCount;

	char hallsFile[10] = "halls.txt";
	char eventsFile[11] = "events.txt";
	char reservationsFile[17] = "reservations.txt";

	void free();
	void copyFrom(const TicketCenter& other);
	int getHallIndex(unsigned hallNumber) const;
	bool isHallBuzy(const Hall& hall, const Date& date) const;
	size_t findEvent(const MyString& name, const Date& date) const;
	size_t findReservation(const Event& event, unsigned row, unsigned seat) const;
	void writeEventsToFile(const char* filePath) const;
	void writeReservationsToFile(const char* filePath) const;
	void loadEventsList(const char* filePath);
	void loadReservationsList(const char* filePath);
public:
	TicketCenter();
	TicketCenter(const TicketCenter& other);
	TicketCenter(TicketCenter&& other);
	~TicketCenter();

	TicketCenter& operator=(const TicketCenter& other);
	TicketCenter& operator=(TicketCenter&& other);

	void newEvent();
	void availableSeats();
	void reserveTicket();
	void cancelReservation();
	void buyTicket();
	void listOfReservations();
	void listOfBoughtTickets();
	void run();
};
