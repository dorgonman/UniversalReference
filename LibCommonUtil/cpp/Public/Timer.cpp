#include "Timer.h"

double Timer::elapsed() const {
    return std::chrono::duration_cast<second_>
        (clock_::now() - beg_).count();
}
