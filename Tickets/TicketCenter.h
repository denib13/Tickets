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
	void copyFrom(const TicketCenter&);
	int getHallIndex(unsigned) const;
	bool isHallBuzy(const Hall& hall, const Date& date) const;
	size_t findEvent(const MyString& name, const Date& date) const;
	size_t findReservation(const Event& event, unsigned row, unsigned seat) const;
public:
	TicketCenter(const char*);
	TicketCenter(const TicketCenter&);
	TicketCenter(TicketCenter&&);
	~TicketCenter();

	TicketCenter& operator=(const TicketCenter&);
	TicketCenter& operator=(TicketCenter&&);

	void newEvent();
	void availableSeats();
	void reserveTicket();
	void cancelReservation();
	void buyTicket();
	void listOfReservations();
	void listOfBoughtTickets();
};