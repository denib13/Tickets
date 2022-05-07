#pragma once
#include "Hall.h"

class TicketCenter
{
	Hall* halls;
	unsigned count;

	void free();
	void copyFrom(const TicketCenter&);
	int getHallIndex(unsigned);
public:
	TicketCenter(const char*);
	TicketCenter(const TicketCenter&);
	TicketCenter(TicketCenter&&);
	~TicketCenter();

	TicketCenter& operator=(const TicketCenter&);
	TicketCenter& operator=(TicketCenter&&);

	void newEvent();
	void freeSeats();
	void reserveTicket();
	void cancelReservation();
	void buyTicket();
	void listOfReservations();
	void listOfBoughtTickets();
};