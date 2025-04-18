#include "NuageEngine/core/Hittable.hpp"
#include <glm/glm.hpp>

namespace Nuage {

void HitRecord::set_face_normal(const Ray& r, const glm::vec3& outward_normal) {
    front_face = glm::dot(r.dir, outward_normal) < 0;
    normal = front_face ? outward_normal : -outward_normal;
}

void HittableList::add(std::shared_ptr<Hittable> obj) { 
    objects.push_back(obj); 
}

bool HittableList::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    HitRecord temp;
    bool hit_any = false;
    float closest = t_max;
    
    for (auto& o : objects) {
        if (o->hit(r, t_min, closest, temp)) {
            hit_any = true;
            closest = temp.t;
            rec = temp;
        }
    }
    
    return hit_any;
}

} 