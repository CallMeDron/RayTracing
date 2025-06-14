#pragma once

#include "line.h"

namespace NRayTracingLib {

class TRay : public TLine {
  public:
    explicit TRay(const TPoint& point1, const TPoint& point2);
    explicit TRay(const TPoint& point, const TVector& vector);

    TSafeDouble distToPoint(const TPoint& point) const override;

    std::optional<TPoint> intersection(const TPlane& plane) const override;

    friend std::ostream& operator<<(std::ostream& os, const TRay& ray);
};

} // namespace NRayTracingLib