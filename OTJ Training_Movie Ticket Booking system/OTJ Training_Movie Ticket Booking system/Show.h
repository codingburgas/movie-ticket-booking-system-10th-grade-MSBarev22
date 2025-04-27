#pragma once
#include <string>
#include "Movie.h"
#include "Hall.h"

class Show {
private:
    Movie movie;
    Hall hall;
    std::string showTime;
public:
    Show(const Movie& m, const Hall& h, const std::string& time);
    std::string getShowTime() const;
};