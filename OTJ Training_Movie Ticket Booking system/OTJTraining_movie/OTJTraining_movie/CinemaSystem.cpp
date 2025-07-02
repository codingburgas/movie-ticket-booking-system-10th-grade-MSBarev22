#include "CinemaSystem.h"
#include "Payment.h"
#include "Notification.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <memory>

CinemaSystem::CinemaSystem() {
    // Optionally, add some sample data for demonstration
    // Sample Movie
    Movie movie1("Interstellar", "English", "Sci-Fi", "2014");
    Movie movie2("Avatar 2", "English", "Action", "2022");

    // Sample Halls
    auto hall1 = std::make_unique<Hall>("Hall 1", 30);
    auto hall2 = std::make_unique<Hall>("Hall 2", 30);

    // Sample Shows
    auto show1 = std::make_unique<Show>(movie1, "18:00");
    auto show2 = std::make_unique<Show>(movie2, "20:00");

    hall1->addShow(std::move(show1));
    hall2->addShow(std::move(show2));

    // Sample Cinema
    auto cinema1 = std::make_unique<Cinema>("Cinema City Paradise", "Sofia");
    cinema1->addHall(std::move(hall1));
    cinema1->addHall(std::move(hall2));

    cinemas.push_back(std::move(cinema1));
    movies.push_back(movie1);
    movies.push_back(movie2);
}

void CinemaSystem::displayWelcome() const {
    std::cout << "Welcome to the Movie Ticket Booking System!" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
}

void CinemaSystem::run() {
    int choice;
    do {
        std::cout << "\n1. Register\n2. Login\n3. Exit\n> ";
        std::cin >> choice;
        switch (choice) {
            case 1: registerUser(); break;
            case 2: if (loginUser()) {
                if (isAdmin) showAdminMenu();
                else userMenu();
            } break;
            case 3: std::cout << "Goodbye!\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void CinemaSystem::registerUser() {
    std::ofstream out("users.txt", std::ios::app);
    std::string user, pass, role;
    std::cout << "Choose username: ";
    std::cin >> user;
    std::cout << "Choose password: ";
    std::cin >> pass;
    std::cout << "Enter role (admin/user): ";
    std::cin >> role;
    if (role != "admin" && role != "user") role = "user";
    out << user << " " << pass << " " << role << "\n";
    std::cout << "Registration successful!\n";
}

bool CinemaSystem::loginUser() {
    std::ifstream in("users.txt");
    std::string user, pass, u, p, r;
    std::cout << "Username: ";
    std::cin >> user;
    std::cout << "Password: ";
    std::cin >> pass;
    while (in >> u >> p >> r) {
        if (u == user && p == pass) {
            std::cout << "Login successful!\n";
            isAdmin = (r == "admin");
            currentUserRole = r;
            return true;
        }
    }
    std::cout << "Login failed. Try again.\n";
    return false;
}

void CinemaSystem::userMenu() {
    int choice;
    do {
        std::cout << "\n1. List Cinemas\n2. List Movies\n3. Logout\n> ";
        std::cin >> choice;
        switch (choice) {
        case 1: listCinemas(); break;
        case 2: listMovies(); break;
        case 3: std::cout << "Logging out...\n"; break;
        default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void CinemaSystem::showAdminMenu() {
    int choice;
    do {
        std::cout << "\n--- Admin Menu ---\n";
        std::cout << "1. List Cinemas\n2. List Movies\n3. Logout\n> ";
        std::cin >> choice;
        switch (choice) {
            case 1: listCinemas(); break;
            case 2: listMovies(); break;
            case 3: std::cout << "Logging out...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 3);
}

void CinemaSystem::listCinemas() {
    std::cout << "\nAvailable Cinemas:" << std::endl;
    for (size_t i = 0; i < cinemas.size(); ++i) {
        std::cout << i + 1 << ". " << cinemas[i]->getName() << " (" << cinemas[i]->getCity() << ")" << std::endl;
    }
    std::cout << "Select a cinema (0 to go back): ";
    int c;
    std::cin >> c;
    if (c < 1 || c >(int)cinemas.size()) return;
    listHalls(*cinemas[c - 1]);
}

void CinemaSystem::listHalls(Cinema& cinema) {
    const auto& halls = cinema.getHalls();
    std::cout << "\nHalls in " << cinema.getName() << ":" << std::endl;
    for (size_t i = 0; i < halls.size(); ++i) {
        std::cout << i + 1 << ". " << halls[i]->getName() << std::endl;
    }
    std::cout << "Select a hall (0 to go back): ";
    int h;
    std::cin >> h;
    if (h < 1 || h >(int)halls.size()) return;
    listShows(*halls[h - 1]);
}

void CinemaSystem::listShows(Hall& hall) {
    const auto& shows = hall.getShows();
    std::cout << "\nShows in " << hall.getName() << ":" << std::endl;
    for (size_t i = 0; i < shows.size(); ++i) {
        std::cout << i + 1 << ". " << shows[i]->getMovie().getTitle() << " at " << shows[i]->getTime() << std::endl;
    }
    std::cout << "Select a show (0 to go back): ";
    int s;
    std::cin >> s;
    if (s < 1 || s >(int)shows.size()) return;
    bookSeats(*shows[s - 1]);
}

void CinemaSystem::listMovies() {
    std::cout << "\nAvailable Movies:" << std::endl;
    for (size_t i = 0; i < movies.size(); ++i) {
        std::cout << i + 1 << ". " << movies[i].getTitle() << " (" << movies[i].getReleaseDate() << ") - " << movies[i].getGenre() << std::endl;
    }
    std::cout << "(Press Enter to continue)";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void CinemaSystem::bookSeats(Show& show) {
    SeatingArrangement* seating = show.getSeating();
    seating->display();
    std::cout << "\nEnter seat row and number to book (e.g., 1 1), 0 0 to finish:\n";
    std::vector<Seat*> selectedSeats;
    while (true) {
        int row, num;
        std::cout << "Seat (row number): ";
        std::cin >> row >> num;
        if (row == 0 && num == 0) break;
        auto& seats = seating->getSeats();
        bool found = false;
        for (auto& seat : seats) {
            if (seat.getRow() == row - 1 && seat.getNumber() == num - 1) {
                if (seat.isBooked()) {
                    std::cout << "Seat already booked!\n";
                }
                else {
                    seat.book();
                    selectedSeats.push_back(&seat);
                    std::cout << "Seat booked.\n";
                }
                found = true;
                break;
            }
        }
        if (!found) std::cout << "Invalid seat.\n";
    }
    if (selectedSeats.empty()) {
        std::cout << "No seats selected.\n";
        return;
    }
    double total = 0.0;
    for (auto* seat : selectedSeats) {
        switch (seat->getType()) {
        case SeatType::SILVER: total += 10; break;
        case SeatType::GOLD: total += 15; break;
        case SeatType::PLATINUM: total += 20; break;
        }
    }
    std::cout << "Total price: $" << total << "\n";
    std::cout << "Pay with credit card? (y/n): ";
    char pay;
    std::cin >> pay;
    if (pay == 'y' || pay == 'Y') {
        Payment::processPayment("credit card", total);
        Notification::send("Booking confirmed!");
    }
    else {
        std::cout << "Booking cancelled.\n";
        for (auto* seat : selectedSeats) seat->book(); // Optionally, unbook if you add an unbook() method
    }
}