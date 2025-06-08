#include "user.h"
#include "movie.h"
#include <iostream>
using namespace std;

int main() {
    loadUsers();
    initMovies();

    cout << "Welcome to Movie Booking System\n1. Login\n2. Sign Up\nChoose: ";
    int opt; cin >> opt;
    string user;
    if (opt == 1) {
        if (!login(user)) return 0;
    }
    else if (opt == 2) {
        signup();
        if (!login(user)) return 0;
    }

    cout << "\nWelcome, " << user << "!\n";
    Movie* selected = selectMovie();
    if (selected) reserveSeat(*selected);
    else cout << "Invalid movie selected.\n";

    return 0;
}
