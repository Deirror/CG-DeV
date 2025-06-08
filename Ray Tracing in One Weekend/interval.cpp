#include "interval.h"

interval::interval()
    : min(+infinity), max(-infinity) {}

interval::interval(double min, double max)
    : min(min), max(max) {}

double interval::size() const {
    return max - min;
}

bool interval::contains(double x) const {
    return min <= x && x <= max;
}

bool interval::surrounds(double x) const {
    return min < x && x < max;
}

double interval::clamp(double x) const {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

const interval interval::empty    = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, +infinity);
