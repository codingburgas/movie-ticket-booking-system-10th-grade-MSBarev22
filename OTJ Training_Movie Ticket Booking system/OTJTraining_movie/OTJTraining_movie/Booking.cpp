#include "Booking.h"

Booking::Booking(User* user, Show* show, const std::vector<Seat*>& seats, const std::string& bookingId)
    : user(user), show(show), seats(seats), bookingId(bookingId) {}

std::string Booking::getBookingId() const { return bookingId; } 