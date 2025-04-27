#pragma once
#include <string>
#include <vector>
#include "Hall.h"

class Cinema {
private:
    std::string cinemaName;
    std::string cityName;
    std::vector<Hall> halls;
public:
    Cinema(const std::string& name, const std::string& city);
    void addHall(const Hall& hall);
    std::string getCinemaName() const;
    std::string getCityName() const;
};