#pragma once

#include "vec3.h"
#include <iostream>

using color = vec3;

double linear_to_gamma(double linear_component);

void write_color(std::ostream& out, const color& pixel_color);