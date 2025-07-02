#include "Cinema.h"

Cinema::Cinema(const std::string& name, const std::string& city) : name(name), city(city) {}

void Cinema::addHall(std::unique_ptr<Hall> hall) {
    halls.push_back(std::move(hall));
}

std::string Cinema::getName() const {
    return name;
}

std::string Cinema::getCity() const {
    return city;
}

const std::vector<std::unique_ptr<Hall>>& Cinema::getHalls() const {
    return halls;
} 