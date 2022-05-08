#include "Reservation.h"
#include <iomanip>

Reservation::Reservation() : event(), password(), note()
{
	row = seat = 0;
}

Reservation::Reservation(const Event& event, unsigned row, unsigned seat, 
	const MyString& password, const MyString& note)
{
	setEvent(event);
	setPassword(password);
	setNote(note);
	setRow(row);
	setSeat(seat);
}

void Reservation::setEvent(const Event& event)
{
	this->event = event;
}

void Reservation::setPassword(const MyString& password)
{
	this->password = password;
}

void Reservation::setNote(const MyString& note)
{
	this->note = note;
}

void Reservation::setRow(unsigned row)
{
	if (0 < row && row <= event.getHall().getRows())
		this->row = row;
	else
		throw std::exception("Invalid row number!");
}

void Reservation::setSeat(unsigned seat)
{
	if (0 < seat && seat <= event.getHall().getSeatsCount())
		this->seat = seat;
	else
		throw std::exception("Invalid seat number!");
}

std::istream& operator>>(std::istream& stream, Reservation& reservation)
{
	Event event;
	unsigned row, seat;
	MyString password;
	MyString note;
	stream >> event >> row >> seat >> password >> note;
	reservation.setEvent(event);
	reservation.setRow(row);
	reservation.setSeat(seat);
	reservation.setPassword(password);
	reservation.setNote(note);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Reservation& reservation)
{
	stream << reservation.event << std::setw(8)<< reservation.row << std::setw(8) << reservation.seat << std::setw(8) << reservation.password << std::setw(8) << reservation.note << std::endl;
	return stream;
}
