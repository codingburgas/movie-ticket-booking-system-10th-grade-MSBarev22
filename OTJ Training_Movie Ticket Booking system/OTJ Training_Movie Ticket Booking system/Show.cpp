#include "Show.h"

Show::Show(const Movie& m, const Hall& h, const std::string& time)
    : movie(m), hall(h), showTime(time) {
}

std::string Show::getShowTime() const {
    return showTime;
}