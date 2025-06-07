#include "hittable_list.h"

hittable_list::hittable_list() {}

hittable_list::hittable_list(std::shared_ptr<hittable> object) {
    add(object);
}

void hittable_list::clear() {
    objects.clear();
}

void hittable_list::add(std::shared_ptr<hittable> object) {
    objects.push_back(object);
}

bool hittable_list::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_tmax;

    for (const auto& object : objects) {
        if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
