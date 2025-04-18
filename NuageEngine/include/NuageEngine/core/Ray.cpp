#include "NuageEngine/core/Ray.hpp"

namespace Nuage {

glm::vec3 Ray::at(float t) const { 
    return orig + dir * t; 
}

} 