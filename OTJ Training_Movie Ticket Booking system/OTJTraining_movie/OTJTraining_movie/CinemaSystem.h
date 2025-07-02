#pragma once
#include <vector>
#include <memory>
#include <string>
#include "Cinema.h"
#include "Movie.h"

class CinemaSystem {
private:
    std::vector<std::unique_ptr<Cinema>> cinemas;
    std::vector<Movie> movies;
    bool isAdmin = false;
    std::string currentUserRole;
public:
    CinemaSystem();
    void displayWelcome() const;
    void run();
    void registerUser();
    bool loginUser();
    void userMenu();
    void listCinemas();
    void listHalls(Cinema& cinema);
    void listShows(Hall& hall);
    void listMovies();
    void bookSeats(Show& show);
    void showAdminMenu();
};