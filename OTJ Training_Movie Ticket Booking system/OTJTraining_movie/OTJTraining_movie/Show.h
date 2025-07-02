#pragma once
#include <string>
#include <memory>
#include "Movie.h"
#include "SeatingArrangement.h"

class Show {
private:
    Movie movie;
    std::string time;
    std::unique_ptr<SeatingArrangement> seating;
public:
    Show(const Movie& movie, const std::string& time);
    ~Show();
    std::string getTime() const;
    const Movie& getMovie() const;
    SeatingArrangement* getSeating() const;
}; 