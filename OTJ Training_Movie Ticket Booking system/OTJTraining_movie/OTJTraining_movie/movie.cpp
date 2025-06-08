#include "movie.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

vector<Movie> movies;

void loadSeats(Movie& movie) {
    ifstream in("seats_" + to_string(movie.id) + ".txt");
    if (!in) return;
    for (auto& row : movie.seats) {
        for (auto& seat : row) {
            in >> seat;
        }
    }
    in.close();
}

void saveSeats(const Movie& movie) {
    ofstream out("seats_" + to_string(movie.id) + ".txt");
    for (const auto& row : movie.seats) {
        for (const auto& seat : row) {
            out << seat << " ";
        }
        out << endl;
    }
    out.close();
}

void initMovies() {
    movies = {
        {1, "Avengers", vector<vector<char>>(5, vector<char>(10, 'A'))},
        {2, "Inception", vector<vector<char>>(5, vector<char>(10, 'A'))},
        {3, "Interstellar", vector<vector<char>>(5, vector<char>(10, 'A'))}
    };
    for (auto& m : movies) loadSeats(m);
}

void showMovies() {
    cout << "\nAvailable Movies:\n";
    for (auto& m : movies) {
        cout << m.id << ". " << m.title << endl;
    }
}

Movie* selectMovie() {
    int choice;
    showMovies();
    cout << "Enter movie number: "; cin >> choice;
    for (auto& m : movies) {
        if (m.id == choice) return &m;
    }
    return nullptr;
}

void showSeats(Movie& movie) {
    cout << "\nSeat Layout (A = available, X = booked):\n";
    for (int i = 0; i < movie.seats.size(); ++i) {
        for (int j = 0; j < movie.seats[i].size(); ++j) {
            cout << setw(2) << movie.seats[i][j] << "(" << i << "," << j << ") ";
        }
        cout << endl;
    }
}

void reserveSeat(Movie& movie) {
    int row, col;
    showSeats(movie);
    cout << "Enter seat row: "; cin >> row;
    cout << "Enter seat column: "; cin >> col;
    if (row >= 0 && row < movie.seats.size() &&
        col >= 0 && col < movie.seats[0].size()) {
        if (movie.seats[row][col] == 'A') {
            movie.seats[row][col] = 'X';
            saveSeats(movie);
            cout << "Seat reserved.\n";
        }
        else {
            cout << "Seat already booked.\n";
        }
    }
    else {
        cout << "Invalid seat coordinates.\n";
    }
}
