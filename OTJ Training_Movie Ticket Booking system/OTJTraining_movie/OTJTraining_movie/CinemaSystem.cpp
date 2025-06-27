#include "CinemaSystem.h"
#include <iostream>
#include <fstream>
#include <iomanip>

CinemaSystem::CinemaSystem() {
    loggedIn = false;
    loadSampleData();
}

void CinemaSystem::loadSampleData() {
    cities.clear();


    City sofia;
    sofia.name = "Sofia";

    // Cinema 1
    Cinema cin1;
    cin1.name = "Cinema City Paradise";

    Movie m1;
    m1.title = "Interstellar";
    m1.language = "English";
    m1.genre = "Sci-Fi";
    m1.releaseDate = "2014";

    Hall h1;
    h1.name = "Hall 1";
    Show s1;
    s1.time = "18:00";
    s1.price = 12.50;
    s1.seats.resize(5, std::vector<Seat>(5, { false, "silver" }));
    h1.shows.push_back(s1);

    m1.halls.push_back(h1);
    cin1.movies.push_back(m1);

   
    Movie m2;
    m2.title = "Avatar 2";
    m2.language = "English";
    m2.genre = "Action";
    m2.releaseDate = "2022";

    Hall h2;
    h2.name = "Hall 2";
    Show s2;
    s2.time = "20:00";
    s2.price = 15.00;
    s2.seats.resize(5, std::vector<Seat>(5, { false, "gold" }));
    h2.shows.push_back(s2);

    m2.halls.push_back(h2);
    cin1.movies.push_back(m2);

    sofia.cinemas.push_back(cin1);

    
    Cinema cin2;
    cin2.name = "Arena Mladost";
    cin2.movies.push_back(m1);
    cin2.movies.push_back(m2);

    sofia.cinemas.push_back(cin2);
    cities.push_back(sofia);
}
void CinemaSystem::run() {
    loginMenu();
    if (loggedIn)
        userMenu();
}

void CinemaSystem::loginMenu() {
    int choice;
    do {
        std::cout << "\n--- Welcome to the Movie Booking System ---\n";
        std::cout << "1. Register\n2. Login\n3. Exit\n> ";
        std::cin >> choice;

        switch (choice) {
        case 1: registerUser(); break;
        case 2: loginUser(); break;
        case 3: return;
        default: std::cout << "Invalid choice.\n";
        }
    } while (!loggedIn);
}

void CinemaSystem::registerUser() {
    std::ofstream out("users.txt", std::ios::app);
    std::string user, pass;
    std::cout << "Choose username: ";
    std::cin >> user;
    std::cout << "Choose password: ";
    std::cin >> pass;
    out << user << " " << pass << "\n";
    std::cout << "Registration successful!\n";
}

void CinemaSystem::loginUser() {
    std::ifstream in("users.txt");
    std::string user, pass, u, p;
    std::cout << "Username: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;

    while (in >> u >> p) {
        if (u == user && p == pass) {
            std::cout << "Login successful!\n";
            currentUser = user;
            loggedIn = true;
            return;
        }
    }
    std::cout << "Login failed. Try again.\n";
}

void CinemaSystem::userMenu() {
    int cityChoice;
    showCities();
    std::cout << "Choose city: ";
    std::cin >> cityChoice;
    if (cityChoice < 1 || cityChoice > cities.size()) return;

    int cinemaChoice;
    showCinemas(cityChoice - 1);
    std::cout << "Choose cinema: ";
    std::cin >> cinemaChoice;
    if (cinemaChoice < 1 || cinemaChoice > cities[cityChoice - 1].cinemas.size()) return;

    int movieChoice;
    showMovies(cityChoice - 1, cinemaChoice - 1);
    std::cout << "Choose movie: ";
    std::cin >> movieChoice;

    Cinema& cinema = cities[cityChoice - 1].cinemas[cinemaChoice - 1];
    if (movieChoice < 1 || movieChoice > cinema.movies.size()) return;

    showMovieDetails(cinema.movies[movieChoice - 1]);
}
void CinemaSystem::showCities() {
    std::cout << "\nCities:\n";
    for (size_t i = 0; i < cities.size(); i++) {
        std::cout << i + 1 << ". " << cities[i].name << "\n";
    }
}

void CinemaSystem::showCinemas(int cityIndex) {
    std::cout << "\nCinemas in " << cities[cityIndex].name << ":\n";
    for (size_t i = 0; i < cities[cityIndex].cinemas.size(); i++) {
        std::cout << i + 1 << ". " << cities[cityIndex].cinemas[i].name << "\n";
    }
}

void CinemaSystem::showMovies(int cityIndex, int cinemaIndex) {
    std::cout << "\nMovies in " << cities[cityIndex].cinemas[cinemaIndex].name << ":\n";
    const auto& movies = cities[cityIndex].cinemas[cinemaIndex].movies;
    for (size_t i = 0; i < movies.size(); i++) {
        std::cout << i + 1 << ". " << movies[i].title << " (" << movies[i].releaseDate << ") - " << movies[i].genre << "\n";
    }
}

void CinemaSystem::showMovieDetails(const Movie& movie) {
    std::cout << "\nMovie: " << movie.title << "\nLanguage: " << movie.language << "\nGenre: " << movie.genre << "\nRelease Date: " << movie.releaseDate << "\n";
    std::cout << "Available Halls and Shows:\n";

    for (size_t h = 0; h < movie.halls.size(); h++) {
        std::cout << "Hall " << h + 1 << ": " << movie.halls[h].name << "\n";
        for (size_t s = 0; s < movie.halls[h].shows.size(); s++) {
            std::cout << "  Show " << s + 1 << ": " << movie.halls[h].shows[s].time << ", Price: $" << movie.halls[h].shows[s].price << "\n";
        }
    }

    int hallChoice, showChoice;
    std::cout << "Choose hall number: ";
    std::cin >> hallChoice;
    if (hallChoice < 1 || hallChoice >(int)movie.halls.size()) return;
    std::cout << "Choose show number: ";
    std::cin >> showChoice;
    if (showChoice < 1 || showChoice >(int)movie.halls[hallChoice - 1].shows.size()) return;

   
    Movie& modifiableMovie = const_cast<Movie&>(movie);
    bookTickets(modifiableMovie, modifiableMovie.halls[hallChoice - 1], modifiableMovie.halls[hallChoice - 1].shows[showChoice - 1]);
}

void CinemaSystem::bookTickets(Movie& movie, Hall& hall, Show& show) {
    std::cout << "\nSeat layout (X = reserved, O = available):\n";


    for (size_t i = 0; i < show.seats.size(); i++) {
        for (size_t j = 0; j < show.seats[i].size(); j++) {
            if (show.seats[i][j].reserved)
                std::cout << "X ";
            else
                std::cout << "O ";
        }
        std::cout << "\n";
    }

    std::cout << "Seat types: silver - $10, gold - $15, platinum - $20\n";

    std::cout << "Enter seat coordinates to book (row and column, 1-based). Enter 0 0 to finish.\n";

    std::vector<std::pair<int, int>> selectedSeats;
    double total = 0.0;

    while (true) {
        int r, c;
        std::cout << "Seat (row col): ";
        std::cin >> r >> c;
        if (r == 0 && c == 0) break;

        if (r < 1 || r >(int)show.seats.size() || c < 1 || c >(int)show.seats[0].size()) {
            std::cout << "Invalid seat position.\n";
            continue;
        }
        Seat& seat = show.seats[r - 1][c - 1];
        if (seat.reserved) {
            std::cout << "Seat already reserved.\n";
            continue;
        }

        seat.reserved = true;
        selectedSeats.emplace_back(r, c);

       
        if (seat.type == "silver")
            total += 10;
        else if (seat.type == "gold")
            total += 15;
        else if (seat.type == "platinum")
            total += 20;

        std::cout << "Seat (" << r << "," << c << ") reserved.\n";
    }

    if (selectedSeats.empty()) {
        std::cout << "No seats selected. Booking cancelled.\n";
        return;
    }

    std::cout << "Total to pay: $" << total << "\n";

    
    std::cout << "Pay with credit card? (y/n): ";
    char payChoice;
    std::cin >> payChoice;
    if (payChoice == 'y' || payChoice == 'Y') {
        std::cout << "Payment successful!\n";
        showReceipt(movie.title, show.time, selectedSeats, total);
    }
    else {
        std::cout << "Payment cancelled, seats released.\n";
       
        for (auto& seatPos : selectedSeats) {
            show.seats[seatPos.first - 1][seatPos.second - 1].reserved = false;
        }
    }
}

void CinemaSystem::showReceipt(const std::string& movieTitle, const std::string& time, const std::vector<std::pair<int, int>>& seats, double total) {
    std::cout << "\n--- DIGITAL RECEIPT ---\n";
    std::cout << "Movie: " << movieTitle << "\n";
    std::cout << "Show time: " << time << "\n";
    std::cout << "Seats booked: ";
    for (const auto& seat : seats) {
        std::cout << "(" << seat.first << "," << seat.second << ") ";
    }
    std::cout << "\nTotal Paid: $" << total << "\n";
    std::cout << "Thank you for your purchase!\n";
}