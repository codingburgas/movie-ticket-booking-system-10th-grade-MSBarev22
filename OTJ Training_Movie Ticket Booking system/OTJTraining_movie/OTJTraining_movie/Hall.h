#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Show.h"

class Hall {
private:
    std::string name;
    int capacity;
    std::vector<std::unique_ptr<Show>> shows;
public:
    Hall(const std::string& name, int capacity);
    Hall(const Hall&) = delete;
    Hall& operator=(const Hall&) = delete;
    void addShow(std::unique_ptr<Show> show);
    std::string getName() const;
    int getCapacity() const;
    const std::vector<std::unique_ptr<Show>>& getShows() const;
}; 