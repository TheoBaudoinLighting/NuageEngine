#pragma once

#include <glm/glm.hpp>
#include "NuageEngine/core/Ray.hpp"
#include "NuageEngine/core/Hittable.hpp"

namespace Nuage {

class Material {
public:
    virtual bool scatter(const Ray& r_in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
    virtual glm::vec3 emitted(float u, float v, const glm::vec3& p) const;
};

class Lambertian : public Material {
public:
    glm::vec3 albedo;
    
    Lambertian(const glm::vec3& a);
    bool scatter(const Ray& r_in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const override;
};

class Dielectric : public Material {
public:
    float ir;
    
    Dielectric(float index);
    static float reflectance(float cosine, float ref_idx);
    bool scatter(const Ray& r_in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const override;
};

class DiffuseLight : public Material {
public:
    glm::vec3 emit;
    
    DiffuseLight(const glm::vec3& e);
    bool scatter(const Ray& r_in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const override;
    glm::vec3 emitted(float u, float v, const glm::vec3& p) const override;
};

} 