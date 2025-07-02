#pragma once
#include <string>

class Notification {
public:
    static void send(const std::string& message);
}; 