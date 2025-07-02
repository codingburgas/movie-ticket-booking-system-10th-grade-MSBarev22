#pragma once
#include <string>

enum class UserType { CUSTOMER, AGENT, ADMIN };

class User {
protected:
    std::string username;
    std::string password;
    UserType type;
public:
    User(const std::string& username, const std::string& password, UserType type);
    virtual ~User() = default;
    std::string getUsername() const;
    UserType getType() const;
    bool checkPassword(const std::string& pwd) const;
}; 