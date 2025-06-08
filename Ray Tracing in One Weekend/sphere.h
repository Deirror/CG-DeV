#pragma once

#include <algorithm> 
#include <cmath>   
#include <memory>

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
    sphere(const point3& center, double radius);

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override;

    sphere(const point3& center, double radius, std::shared_ptr<material> mat);

private:
    point3 center;
    double radius;
    std::shared_ptr<material> mat;
};