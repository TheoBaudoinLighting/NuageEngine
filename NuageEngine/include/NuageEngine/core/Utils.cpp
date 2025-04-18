#include "NuageEngine/core/Utils.hpp"

namespace Nuage {

const float INF = std::numeric_limits<float>::infinity();

float clampf(float x, float mini, float maxi) {
    if (x < mini) return mini;
    if (x > maxi) return maxi;
    return x;
}

} 