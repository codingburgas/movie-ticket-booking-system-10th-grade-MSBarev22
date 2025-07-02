#include "User.h"

User::User(const std::string& username, const std::string& password, UserType type)
    : username(username), password(password), type(type) {}

std::string User::getUsername() const { return username; }
UserType User::getType() const { return type; }
bool User::checkPassword(const std::string& pwd) const { return pwd == password; } 