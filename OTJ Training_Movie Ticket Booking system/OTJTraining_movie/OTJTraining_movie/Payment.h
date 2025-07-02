#pragma once
#include <string>

class Payment {
public:
    static bool processPayment(const std::string& method, double amount);
}; 