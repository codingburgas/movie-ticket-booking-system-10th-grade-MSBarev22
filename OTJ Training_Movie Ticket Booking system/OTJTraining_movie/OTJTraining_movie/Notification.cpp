#include "Notification.h"
#include <iostream>

void Notification::send(const std::string& message) {
    std::cout << "Notification: " << message << std::endl;
} 