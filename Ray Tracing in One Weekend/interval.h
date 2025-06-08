#pragma once

#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

class interval {
  public:
    double min, max;

    interval();                       
    interval(double min, double max); 

    double size() const;
    bool contains(double x) const;
    bool surrounds(double x) const;
    double clamp(double x) const; 

    static const interval empty;
    static const interval universe;
};