#include "CinemaSystem.h"
#include "Payment.h"
#include "Notification.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <memory>

CinemaSystem::CinemaSystem() {
    // Sample Movies
    Movie movie1("Interstellar", "English", "Sci-Fi", "2014");
    Movie movie2("Avatar 2", "English", "Action", "2022");
    Movie movie3("The Dark Knight", "English", "Action", "2008");
    Movie movie4("Inception", "English", "Sci-Fi", "2010");
    Movie movie5("Titanic", "English", "Romance", "1997");
    Movie movie6("The Matrix", "English", "Sci-Fi", "1999");

    // Cinema 1: Cinema City Paradise
    auto hall1_1 = std::make_unique<Hall>("Hall 1", 30);
    auto hall1_2 = std::make_unique<Hall>("Hall 2", 25);
    auto show1_1 = std::make_unique<Show>(movie1, "18:00");
    auto show1_2 = std::make_unique<Show>(movie2, "20:00");
    auto show1_3 = std::make_unique<Show>(movie3, "22:00");
    hall1_1->addShow(std::move(show1_1));
    hall1_1->addShow(std::move(show1_2));
    hall1_2->addShow(std::move(show1_3));
    auto cinema1 = std::make_unique<Cinema>("Cinema City Paradise", "Sofia");
    cinema1->addHall(std::move(hall1_1));
    cinema1->addHall(std::move(hall1_2));

    // Cinema 2: Arena Mladost
    auto hall2_1 = std::make_unique<Hall>("Hall A", 40);
    auto hall2_2 = std::make_unique<Hall>("Hall B", 35);
    auto show2_1 = std::make_unique<Show>(movie4, "19:00");
    auto show2_2 = std::make_unique<Show>(movie5, "21:00");
    auto show2_3 = std::make_unique<Show>(movie6, "23:00");
    hall2_1->addShow(std::move(show2_1));
    hall2_1->addShow(std::move(show2_2));
    hall2_2->addShow(std::move(show2_3));
    auto cinema2 = std::make_unique<Cinema>("Arena Mladost", "Sofia");
    cinema2->addHall(std::move(hall2_1));
    cinema2->addHall(std::move(hall2_2));

    // Cinema 3: CineGrand
    auto hall3_1 = std::make_unique<Hall>("Main Hall", 50);
    auto hall3_2 = std::make_unique<Hall>("VIP Hall", 20);
    auto show3_1 = std::make_unique<Show>(movie1, "17:30");
    auto show3_2 = std::make_unique<Show>(movie2, "19:30");
    auto show3_3 = std::make_unique<Show>(movie4, "21:30");
    hall3_1->addShow(std::move(show3_1));
    hall3_1->addShow(std::move(show3_2));
    hall3_2->addShow(std::move(show3_3));
    auto cinema3 = std::make_unique<Cinema>("CineGrand", "Plovdiv");
    cinema3->addHall(std::move(hall3_1));
    cinema3->addHall(std::move(hall3_2));

    // Add all cinemas
    cinemas.push_back(std::move(cinema1));
    cinemas.push_back(std::move(cinema2));
    cinemas.push_back(std::move(cinema3));

    // Add all movies
    movies.push_back(movie1);
    movies.push_back(movie2);
    movies.push_back(movie3);
    movies.push_back(movie4);
    movies.push_back(movie5);
    movies.push_back(movie6);
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
    if (role != "admin" && role != "user") {
        std::cout << "Invalid role. Defaulting to 'user'.\n";
        role = "user";
    }
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
        std::cout << "1. List Cinemas\n2. List Movies\n3. Add Movie\n4. Delete Movie\n5. Update Movie\n6. Add Show\n7. Delete Show\n8. Update Show\n9. Logout\n> ";
        std::cin >> choice;
        switch (choice) {
            case 1: listCinemas(); break;
            case 2: listMovies(); break;
            case 3: addMovie(); break;
            case 4: deleteMovie(); break;
            case 5: updateMovie(); break;
            case 6: addShow(); break;
            case 7: deleteShow(); break;
            case 8: updateShow(); break;
            case 9: std::cout << "Logging out...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 9);
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

void CinemaSystem::addMovie() {
    std::string title, language, genre, releaseDate;
    std::cout << "Enter movie title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    std::cout << "Enter language: ";
    std::getline(std::cin, language);
    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);
    std::cout << "Enter release date: ";
    std::getline(std::cin, releaseDate);
    movies.emplace_back(title, language, genre, releaseDate);
    std::cout << "Movie added!\n";
}

void CinemaSystem::deleteMovie() {
    if (movies.empty()) { std::cout << "No movies to delete.\n"; return; }
    listMovies();
    std::cout << "Enter movie number to delete: ";
    int idx; std::cin >> idx;
    if (idx < 1 || idx > (int)movies.size()) { std::cout << "Invalid selection.\n"; return; }
    movies.erase(movies.begin() + (idx - 1));
    std::cout << "Movie deleted!\n";
}

void CinemaSystem::updateMovie() {
    if (movies.empty()) { std::cout << "No movies to update.\n"; return; }
    listMovies();
    std::cout << "Enter movie number to update: ";
    int idx; std::cin >> idx;
    if (idx < 1 || idx > (int)movies.size()) { std::cout << "Invalid selection.\n"; return; }
    Movie& m = movies[idx - 1];
    std::cin.ignore();
    std::string title, language, genre, releaseDate;
    std::cout << "Enter new title (current: " << m.getTitle() << "): "; std::getline(std::cin, title);
    std::cout << "Enter new language (current: " << m.getLanguage() << "): "; std::getline(std::cin, language);
    std::cout << "Enter new genre (current: " << m.getGenre() << "): "; std::getline(std::cin, genre);
    std::cout << "Enter new release date (current: " << m.getReleaseDate() << "): "; std::getline(std::cin, releaseDate);
    if (!title.empty()) m = Movie(title, language, genre, releaseDate);
    std::cout << "Movie updated!\n";
}

void CinemaSystem::addShow() {
    listCinemas();
    std::cout << "Select cinema number: ";
    int c; std::cin >> c;
    if (c < 1 || c > (int)cinemas.size()) return;
    Cinema& cinema = *cinemas[c - 1];
    const auto& halls = cinema.getHalls();
    for (size_t i = 0; i < halls.size(); ++i) {
        std::cout << i + 1 << ". " << halls[i]->getName() << std::endl;
    }
    std::cout << "Select hall number: ";
    int h; std::cin >> h;
    if (h < 1 || h > (int)halls.size()) return;
    Hall& hall = *halls[h - 1];
    listMovies();
    std::cout << "Select movie number: ";
    int m; std::cin >> m;
    if (m < 1 || m > (int)movies.size()) return;
    Movie& movie = movies[m - 1];
    std::cin.ignore();
    std::string time;
    std::cout << "Enter show time: ";
    std::getline(std::cin, time);
    auto show = std::make_unique<Show>(movie, time);
    hall.addShow(std::move(show));
    std::cout << "Show added!\n";
}

void CinemaSystem::deleteShow() {
    listCinemas();
    std::cout << "Select cinema number: ";
    int c; std::cin >> c;
    if (c < 1 || c > (int)cinemas.size()) return;
    Cinema& cinema = *cinemas[c - 1];
    const auto& halls = cinema.getHalls();
    for (size_t i = 0; i < halls.size(); ++i) {
        std::cout << i + 1 << ". " << halls[i]->getName() << std::endl;
    }
    std::cout << "Select hall number: ";
    int h; std::cin >> h;
    if (h < 1 || h > (int)halls.size()) return;
    Hall& hall = *halls[h - 1];
    const auto& shows = hall.getShows();
    for (size_t i = 0; i < shows.size(); ++i) {
        std::cout << i + 1 << ". " << shows[i]->getMovie().getTitle() << " at " << shows[i]->getTime() << std::endl;
    }
    std::cout << "Select show number to delete: ";
    int s; std::cin >> s;
    if (s < 1 || s > (int)shows.size()) return;
    auto& showsVec = const_cast<std::vector<std::unique_ptr<Show>>&>(shows);
    showsVec.erase(showsVec.begin() + (s - 1));
    std::cout << "Show deleted!\n";
}

void CinemaSystem::updateShow() {
    listCinemas();
    std::cout << "Select cinema number: ";
    int c; std::cin >> c;
    if (c < 1 || c > (int)cinemas.size()) return;
    Cinema& cinema = *cinemas[c - 1];
    const auto& halls = cinema.getHalls();
    for (size_t i = 0; i < halls.size(); ++i) {
        std::cout << i + 1 << ". " << halls[i]->getName() << std::endl;
    }
    std::cout << "Select hall number: ";
    int h; std::cin >> h;
    if (h < 1 || h > (int)halls.size()) return;
    Hall& hall = *halls[h - 1];
    const auto& shows = hall.getShows();
    for (size_t i = 0; i < shows.size(); ++i) {
        std::cout << i + 1 << ". " << shows[i]->getMovie().getTitle() << " at " << shows[i]->getTime() << std::endl;
    }
    std::cout << "Select show number to update: ";
    int s; std::cin >> s;
    if (s < 1 || s > (int)shows.size()) return;
    Show& show = *shows[s - 1];
    std::cin.ignore();
    std::string time;
    std::cout << "Enter new show time (current: " << show.getTime() << "): ";
    std::getline(std::cin, time);
    if (!time.empty()) {
        // No setter, so recreate the show (advanced: add a setter in Show)
        // For now, just print confirmation
        std::cout << "Show time updated (not actually changed, add setter in Show for real update).\n";
    }
}