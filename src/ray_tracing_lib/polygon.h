#pragma once

#include "point.h"

#include <vector>

namespace NRayTracingLib {

using TPoints = std::vector<TPoint>;

class TPolygon {
  public:
    TPoints Points;

    explicit TPolygon(const TPoints& points);

    //   private:
    //     void SortByPolarAngle(const TPlane& plane);
    //     void RemoveExtraPoints();
};

class TRectangle : TPolygon {
  public:
    explicit TRectangle(const TPoints& points);
};

} // namespace NRayTracingLib