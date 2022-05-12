#include "Reservation.h"
#include <iomanip>

Reservation::Reservation() : event(), password(), note()
{
	row = seat = 0;
	seatStatus = available;
}

Reservation::Reservation(const Event& event, unsigned row, unsigned seat, Status seatStatus,
	const MyString& password, const MyString& note)
{
	setEvent(event);
	setPassword(password);
	setNote(note);
	setRow(row);
	setSeat(seat);
	setStatus(seatStatus);
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

void Reservation::setStatus(Status newStatus)
{
	seatStatus = newStatus;
}

std::istream& operator>>(std::istream& stream, Reservation& reservation)
{
	Event event;
	MyString note;
	unsigned row, seat, status;

	stream >> event;
	stream >> row;
	stream.ignore();
	stream >> seat;
	stream.ignore();
	stream >> status;
	stream.ignore();

	char passwordString[256];
	stream.getline(passwordString, 255, '|');
	stream >> note;
	MyString password(passwordString);

	if (status == 1)
		reservation.setStatus(reserved);
	else if (status == 2)
		reservation.setStatus(sold);

	reservation.setEvent(event);
	reservation.setRow(row);
	reservation.setSeat(seat);
	reservation.setPassword(password);
	reservation.setNote(note);
	return stream;
}

std::ostream& operator<<(std::ostream& stream, const Reservation& reservation)
{
	stream << reservation.event << '|' << reservation.row << '|' 
		<< reservation.seat << '|' << reservation.seatStatus << '|' << reservation.password << '|' << reservation.note;
	return stream;
}
