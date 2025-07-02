#pragma once
#include <string>

enum class SeatType { SILVER, GOLD, PLATINUM };

class Seat {
private:
    int row;
    int number;
    SeatType type;
    bool booked;
public:
    Seat(int row, int number, SeatType type);
    bool isBooked() const;
    void book();
    SeatType getType() const;
    int getRow() const;
    int getNumber() const;
}; 