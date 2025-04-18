#pragma once

#include <vector>
#include <memory>
#include "NuageEngine/core/Ray.hpp"

namespace Nuage {

class Material;

struct HitRecord {
    glm::vec3 p;
    glm::vec3 normal;
    float t;
    bool front_face;
    std::shared_ptr<Material> mat_ptr;
    float u, v;
    
    void set_face_normal(const Ray& r, const glm::vec3& outward_normal);
};

class Hittable {
public:
    virtual bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const = 0;
};

class HittableList : public Hittable {
public:
    std::vector<std::shared_ptr<Hittable>> objects;
    
    void add(std::shared_ptr<Hittable> obj);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

} 