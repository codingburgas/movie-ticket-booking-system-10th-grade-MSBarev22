#include "Show.h"

Show::Show(const Movie& movie, const std::string& time)
    : movie(movie), time(time), seating(std::make_unique<SeatingArrangement>()) {}

Show::~Show() = default;

std::string Show::getTime() const { return time; }
const Movie& Show::getMovie() const { return movie; }
SeatingArrangement* Show::getSeating() const { return seating.get(); } 