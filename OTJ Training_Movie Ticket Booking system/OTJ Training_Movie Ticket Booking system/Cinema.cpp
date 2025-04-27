#include "Cinema.h"

Cinema::Cinema(const std::string& name, const std::string& city)
    : cinemaName(name), cityName(city) {
}

void Cinema::addHall(const Hall& hall) {
    halls.push_back(hall);
}

std::string Cinema::getCinemaName() const {
    return cinemaName;
}

std::string Cinema::getCityName() const {
    return cityName;
}