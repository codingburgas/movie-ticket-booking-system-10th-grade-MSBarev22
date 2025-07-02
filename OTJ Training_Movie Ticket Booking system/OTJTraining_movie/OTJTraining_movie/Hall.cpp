#include "Hall.h"

Hall::Hall(const std::string& name, int capacity) : name(name), capacity(capacity) {}

void Hall::addShow(std::unique_ptr<Show> show) {
    shows.push_back(std::move(show));
}

std::string Hall::getName() const {
    return name;
}

int Hall::getCapacity() const {
    return capacity;
}

const std::vector<std::unique_ptr<Show>>& Hall::getShows() const {
    return shows;
} 