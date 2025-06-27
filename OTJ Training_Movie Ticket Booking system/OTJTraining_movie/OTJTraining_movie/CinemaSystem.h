#ifndef CINEMASYSTEM_H
#define CINEMASYSTEM_H

#include <string>
#include <vector>
#include <map>

struct Seat {
    bool reserved;
    std::string type; // silver, gold, platinum
};

struct Show {
    std::string time;
    std::vector<std::vector<Seat>> seats;
    double price;
};

struct Hall {
    std::string name;
    std::vector<Show> shows;
};

struct Movie {
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
    std::vector<Hall> halls;
};

struct Cinema {
    std::string name;
    std::vector<Movie> movies;
};

struct City {
    std::string name;
    std::vector<Cinema> cinemas;
};

class CinemaSystem {
private:
    std::vector<City> cities;
    std::string currentUser;
    bool loggedIn;

    void loadSampleData();
    void loginMenu();
    void registerUser();
    void loginUser();
    void adminPanel();
    void userMenu();
    void showCities();
    void showCinemas(int cityIndex);
    void showMovies(int cityIndex, int cinemaIndex);
    void showMovieDetails(const Movie& movie);
    void bookTickets(Movie& movie, Hall& hall, Show& show);
    void showReceipt(const std::string& movieTitle, const std::string& time, const std::vector<std::pair<int, int>>& seats, double total);

public:
    CinemaSystem();
    void run();
};

#endif