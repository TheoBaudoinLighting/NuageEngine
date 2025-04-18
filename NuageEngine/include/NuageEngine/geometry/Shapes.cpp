#include "NuageEngine/geometry/Shapes.hpp"
#include <cmath>

namespace Nuage {

Sphere::Sphere(const glm::vec3& c, float r, std::shared_ptr<Material> m) 
    : center(c), radius(r), mat_ptr(m) {}

bool Sphere::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    glm::vec3 oc = r.orig - center;
    float a = glm::dot(r.dir, r.dir);
    float half_b = glm::dot(oc, r.dir);
    float c = glm::dot(oc, oc) - radius * radius;
    float disc = half_b * half_b - a * c;
    
    if (disc < 0) return false;
    
    float sqrtd = sqrtf(disc);
    float root = (-half_b - sqrtd) / a;
    
    if (root < t_min || root > t_max) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || root > t_max) return false;
    }
    
    rec.t = root;
    rec.p = r.at(rec.t);
    glm::vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = mat_ptr;
    
    return true;
}

YZRect::YZRect(float _y0, float _y1, float _z0, float _z1, float _k, std::shared_ptr<Material> m, bool _flip)
    : y0(_y0), y1(_y1), z0(_z0), z1(_z1), k(_k), mp(m), flip(_flip) {}

bool YZRect::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    float t = (k - r.orig.x) / r.dir.x;
    
    if (t < t_min || t > t_max) return false;
    
    float y = r.orig.y + t * r.dir.y;
    float z = r.orig.z + t * r.dir.z;
    
    if (y < y0 || y > y1 || z < z0 || z > z1) return false;
    
    rec.u = (y - y0) / (y1 - y0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.p = r.at(t);
    glm::vec3 outward = flip ? glm::vec3(-1, 0, 0) : glm::vec3(1, 0, 0);
    rec.set_face_normal(r, outward);
    rec.mat_ptr = mp;
    
    return true;
}

XZRect::XZRect(float _x0, float _x1, float _z0, float _z1, float _k, std::shared_ptr<Material> m, bool _flip)
    : x0(_x0), x1(_x1), z0(_z0), z1(_z1), k(_k), mp(m), flip(_flip) {}

bool XZRect::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    float t = (k - r.orig.y) / r.dir.y;
    
    if (t < t_min || t > t_max) return false;
    
    float x = r.orig.x + t * r.dir.x;
    float z = r.orig.z + t * r.dir.z;
    
    if (x < x0 || x > x1 || z < z0 || z > z1) return false;
    
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (z - z0) / (z1 - z0);
    rec.t = t;
    rec.p = r.at(t);
    glm::vec3 outward = flip ? glm::vec3(0, -1, 0) : glm::vec3(0, 1, 0);
    rec.set_face_normal(r, outward);
    rec.mat_ptr = mp;
    
    return true;
}

XYRect::XYRect(float _x0, float _x1, float _y0, float _y1, float _k, std::shared_ptr<Material> m)
    : x0(_x0), x1(_x1), y0(_y0), y1(_y1), k(_k), mp(m) {}

bool XYRect::hit(const Ray& r, float t_min, float t_max, HitRecord& rec) const {
    float t = (k - r.orig.z) / r.dir.z;
    
    if (t < t_min || t > t_max) return false;
    
    float x = r.orig.x + t * r.dir.x;
    float y = r.orig.y + t * r.dir.y;
    
    if (x < x0 || x > x1 || y < y0 || y > y1) return false;
    
    rec.u = (x - x0) / (x1 - x0);
    rec.v = (y - y0) / (y1 - y0);
    rec.t = t;
    rec.p = r.at(t);
    rec.set_face_normal(r, glm::vec3(0, 0, 1));
    rec.mat_ptr = mp;
    
    return true;
}

} 