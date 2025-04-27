#include "Movie.h"

Movie::Movie(const std::string& t, const std::string& l, const std::string& g, const std::string& r)
    : title(t), language(l), genre(g), releaseDate(r) {
}

std::string Movie::getTitle() const { return title; }
std::string Movie::getLanguage() const { return language; }
std::string Movie::getGenre() const { return genre; }
std::string Movie::getReleaseDate() const { return releaseDate; }