#include "Movie.h"

Movie::Movie(const std::string& title, const std::string& language, const std::string& genre, const std::string& releaseDate)
    : title(title), language(language), genre(genre), releaseDate(releaseDate) {}

std::string Movie::getTitle() const { return title; }
std::string Movie::getLanguage() const { return language; }
std::string Movie::getGenre() const { return genre; }
std::string Movie::getReleaseDate() const { return releaseDate; } 