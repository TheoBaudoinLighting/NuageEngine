#include "NuageEngine/camera/Camera.hpp"
#include <glm/gtc/random.hpp>
#include <cmath>

namespace Nuage {

Camera::Camera(glm::vec3 lookfrom, glm::vec3 lookat, glm::vec3 vup, 
              float vfov, float aspect, float aperture, float focus_dist) {
    float theta = vfov * 3.1415926535897932385f / 180.0f;
    float h = tan(theta / 2);
    float viewport_height = 2.0f * h;
    float viewport_width = aspect * viewport_height;
    
    w = glm::normalize(lookfrom - lookat);
    u = glm::normalize(glm::cross(vup, w));
    v = glm::cross(w, u);
    
    origin = lookfrom;
    horizontal = focus_dist * viewport_width * u;
    vertical = focus_dist * viewport_height * v;
    lower_left_corner = origin - horizontal / 2.0f - vertical / 2.0f - focus_dist * w;
    lens_radius = aperture / 2.0f;
}

Ray Camera::get_ray(float s, float t) const {
    glm::vec2 rd2 = lens_radius * glm::diskRand(1.0f);
    glm::vec3 offset = u * rd2.x + v * rd2.y;
    return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
}

} 