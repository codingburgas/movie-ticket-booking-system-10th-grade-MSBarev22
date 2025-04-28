#pragma once
#include <string>

class Movie {
private:
    std::string title;
    std::string language;
    std::string genre;
    std::string releaseDate;
    std::string projectionTime;
public:
    Movie(const std::string& title, const std::string& language, const std::string& genre, const std::string& releaseDate, const std::string& projectionTime);
    std::string getTitle() const;
    std::string getLanguage() const;
    std::string getGenre() const;
    std::string getReleaseDate() const;
    std::string getProjectionTime() const;
};
