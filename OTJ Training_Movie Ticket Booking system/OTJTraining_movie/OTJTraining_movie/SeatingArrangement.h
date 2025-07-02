#pragma once
#include <vector>
#include "Seat.h"

class SeatingArrangement {
private:
    std::vector<Seat> seats;
public:
    SeatingArrangement();
    std::vector<Seat>& getSeats();
    void display() const;
}; 