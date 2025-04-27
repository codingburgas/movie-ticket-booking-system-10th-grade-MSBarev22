#include "Hall.h"

Hall::Hall(int number, int seats)
    : hallNumber(number), totalSeats(seats) {
}

int Hall::getHallNumber() const {
    return hallNumber;
}

int Hall::getTotalSeats() const {
    return totalSeats;
}