#include "Payment.h"
#include <iostream>

bool Payment::processPayment(const std::string& method, double amount) {
    std::cout << "Processing payment of $" << amount << " via " << method << std::endl;
    return true;
} 