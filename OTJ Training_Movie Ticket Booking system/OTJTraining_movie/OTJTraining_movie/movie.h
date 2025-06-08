#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
using namespace std;

struct Movie {
    int id;
    string title;
    vector<vector<char>> seats;
};

void initMovies();
void showMovies();
Movie* selectMovie();
void showSeats(Movie& movie);
void reserveSeat(Movie& movie);

#endif
