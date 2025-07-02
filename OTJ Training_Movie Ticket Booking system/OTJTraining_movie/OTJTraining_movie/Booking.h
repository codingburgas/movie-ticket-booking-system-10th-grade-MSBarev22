#pragma once
#include <string>
#include "User.h"
#include "Show.h"
#include "Seat.h"

class Booking {
private:
    User* user;
    Show* show;
    std::vector<Seat*> seats;
    std::string bookingId;
public:
    Booking(User* user, Show* show, const std::vector<Seat*>& seats, const std::string& bookingId);
    std::string getBookingId() const;
}; 