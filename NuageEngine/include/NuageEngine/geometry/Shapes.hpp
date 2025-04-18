#pragma once

#include <memory>
#include <glm/glm.hpp>
#include "NuageEngine/core/Hittable.hpp"
#include "NuageEngine/materials/Material.hpp"

namespace Nuage {

class Sphere : public Hittable {
public:
    glm::vec3 center;
    float radius;
    std::shared_ptr<Material> mat_ptr;
    
    Sphere(const glm::vec3& c, float r, std::shared_ptr<Material> m);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

class YZRect : public Hittable {
public:
    float y0, y1, z0, z1, k;
    std::shared_ptr<Material> mp;
    bool flip;
    
    YZRect(float _y0, float _y1, float _z0, float _z1, float _k, std::shared_ptr<Material> m, bool _flip = false);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

class XZRect : public Hittable {
public:
    float x0, x1, z0, z1, k;
    std::shared_ptr<Material> mp;
    bool flip;
    
    XZRect(float _x0, float _x1, float _z0, float _z1, float _k, std::shared_ptr<Material> m, bool _flip = false);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

class XYRect : public Hittable {
public:
    float x0, x1, y0, y1, k;
    std::shared_ptr<Material> mp;
    
    XYRect(float _x0, float _x1, float _y0, float _y1, float _k, std::shared_ptr<Material> m);
    bool hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const override;
};

} 