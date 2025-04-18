#pragma once

#include <glm/glm.hpp>

namespace Nuage {

struct Ray {
    glm::vec3 orig, dir;
    
    Ray() : orig(glm::vec3(0.0f)), dir(glm::vec3(0.0f)) {}
    Ray(const glm::vec3& o, const glm::vec3& d) : orig(o), dir(d) {}
    
    glm::vec3 at(float t) const;
};

} 