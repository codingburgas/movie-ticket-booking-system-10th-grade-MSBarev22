#pragma once

class Hall {
private:
    int hallNumber;
    int totalSeats;
public:
    Hall(int number, int seats);
    int getHallNumber() const;
    int getTotalSeats() const;
};