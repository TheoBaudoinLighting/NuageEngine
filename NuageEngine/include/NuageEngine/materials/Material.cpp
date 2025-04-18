#include "NuageEngine/materials/Material.hpp"
#include <glm/gtc/random.hpp>
#include <cmath>

namespace Nuage {

glm::vec3 Material::emitted(float, float, const glm::vec3&) const { 
    return glm::vec3(0.0f); 
}

Lambertian::Lambertian(const glm::vec3& a) : albedo(a) {}

bool Lambertian::scatter(const Ray& r_in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const {
    glm::vec3 scatter_dir = rec.normal + glm::normalize(glm::ballRand(1.0f));
    if (glm::dot(scatter_dir, scatter_dir) < 1e-8f) 
        scatter_dir = rec.normal;
        
    scattered = Ray(rec.p, scatter_dir);
    attenuation = albedo;
    return true;
}

Dielectric::Dielectric(float index) : ir(index) {}

float Dielectric::reflectance(float cosine, float ref_idx) {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * powf(1 - cosine, 5);
}

bool Dielectric::scatter(const Ray& r_in, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const {
    attenuation = glm::vec3(1.0f);
    float ref_ratio = rec.front_face ? (1.0f / ir) : ir;
    
    glm::vec3 unit_dir = glm::normalize(r_in.dir);
    float cos_theta = fmin(glm::dot(-unit_dir, rec.normal), 1.0f);
    float sin_theta = sqrtf(1.0f - cos_theta * cos_theta);
    
    if (ref_ratio * sin_theta > 1.0f || reflectance(cos_theta, ref_ratio) > glm::linearRand(0.0f, 1.0f)) {
        glm::vec3 reflected = glm::reflect(unit_dir, rec.normal);
        scattered = Ray(rec.p, reflected);
    }
    else {
        glm::vec3 refracted = glm::refract(unit_dir, rec.normal, ref_ratio);
        scattered = Ray(rec.p, refracted);
    }
    
    return true;
}

DiffuseLight::DiffuseLight(const glm::vec3& e) : emit(e) {}

bool DiffuseLight::scatter(const Ray&, const HitRecord&, glm::vec3&, Ray&) const { 
    return false; 
}

glm::vec3 DiffuseLight::emitted(float, float, const glm::vec3&) const { 
    return emit; 
}

} 