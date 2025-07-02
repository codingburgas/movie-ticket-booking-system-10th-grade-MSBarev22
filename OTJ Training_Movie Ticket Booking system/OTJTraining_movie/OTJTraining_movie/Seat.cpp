#include "Seat.h"

Seat::Seat(int row, int number, SeatType type) : row(row), number(number), type(type), booked(false) {}

bool Seat::isBooked() const { return booked; }
void Seat::book() { booked = true; }
SeatType Seat::getType() const { return type; }
int Seat::getRow() const { return row; }
int Seat::getNumber() const { return number; } 