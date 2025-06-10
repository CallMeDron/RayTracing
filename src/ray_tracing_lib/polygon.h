#pragma once

#include "plane.h"
#include "point.h"

#include <vector>

namespace NRayTracingLib {

using TPoints = std::vector<TPoint>;

class TPolygon {
  public:
    TPoints Points;

    explicit TPolygon(const TPoints& points);

  private:
    bool IsLine() const;
    void SortByPolarAngle(const TPlane& plane);
    void RemoveExtraPoints();
    bool IsConvex() const;
};

class TRectangle : public TPolygon {
  public:
    explicit TRectangle(const TPoints& points);
};

} // namespace NRayTracingLib