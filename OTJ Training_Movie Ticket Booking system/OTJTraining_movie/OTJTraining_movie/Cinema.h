#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Hall.h"

class Cinema {
private:
    std::string name;
    std::string city;
    std::vector<std::unique_ptr<Hall>> halls;
public:
    Cinema(const std::string& name, const std::string& city);
    Cinema(const Cinema&) = delete;
    Cinema& operator=(const Cinema&) = delete;
    void addHall(std::unique_ptr<Hall> hall);
    std::string getName() const;
    std::string getCity() const;
    const std::vector<std::unique_ptr<Hall>>& getHalls() const;
}; 