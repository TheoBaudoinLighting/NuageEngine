#include "NuageEngine/renderer/Render.hpp"
#include "NuageEngine/core/Utils.hpp"
#include "NuageEngine/materials/Material.hpp"

namespace Nuage {

glm::vec3 ray_color(const Ray& r, const Hittable& world, int depth) {
    if (depth <= 0) return glm::vec3(0.0f);
    
    HitRecord rec;
    if (world.hit(r, 0.001f, INF, rec)) {
        glm::vec3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.p);
        glm::vec3 attenuation;
        Ray scattered;
        
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return emitted + attenuation * ray_color(scattered, world, depth - 1);
            
        return emitted;
    }
    
    return glm::vec3(0.0f);
}

} 