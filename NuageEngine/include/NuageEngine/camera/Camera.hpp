#pragma once

#include <glm/glm.hpp>
#include "NuageEngine/core/Ray.hpp"

namespace Nuage {

class Camera {
public:
    glm::vec3 origin, lower_left_corner, horizontal, vertical, u, v, w;
    float lens_radius;
    
    Camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, 
           float vfov, float aspect, float aperture, float focus_dist);
    
    Ray get_ray(float s, float t) const;
};

} 