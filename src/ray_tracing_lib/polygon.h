#pragma once

#include "point.h"

#include <vector>

namespace NRayTracingLib {

class TPolygon {
  public:
    std::vector<TPoint> Points;

    explicit TPolygon(std::vector<TPoint> points);
};

} // namespace NRayTracingLib