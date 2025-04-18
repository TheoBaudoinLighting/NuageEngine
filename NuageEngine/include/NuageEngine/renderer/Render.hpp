#pragma once

#include "NuageEngine/core/Ray.hpp"
#include "NuageEngine/core/Hittable.hpp"

namespace Nuage {

glm::vec3 ray_color(const Ray& r, const Hittable& world, int depth);

} 