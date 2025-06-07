#pragma once

#include <algorithm> 
#include <cmath>   

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    sphere(const point3& center, double radius);

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override;

private:
    point3 center;
    double radius;
};