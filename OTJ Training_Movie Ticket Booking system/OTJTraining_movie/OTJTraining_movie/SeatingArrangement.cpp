#include "SeatingArrangement.h"
#include <iostream>

SeatingArrangement::SeatingArrangement() {

    for (int r = 0; r < 3; ++r) {
        for (int n = 0; n < 10; ++n) {
            seats.emplace_back(r, n, SeatType::SILVER);
        }
    }
}

std::vector<Seat>& SeatingArrangement::getSeats() { return seats; }

void SeatingArrangement::display() const {
    for (const auto& seat : seats) {
        std::cout << (seat.isBooked() ? "[X]" : "[O]");
        if ((seat.getNumber() + 1) % 10 == 0) std::cout << std::endl;
    }
} 