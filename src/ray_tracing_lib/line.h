#pragma once

#include "common.h"
#include "plane.h"
#include "point.h"
#include "vector.h"

namespace NRayTracingLib {

class TLine {
  public:
    TPoint Point;
    TVector Vector;

    TLine();
    explicit TLine(const TPoint& point1, const TPoint& point2);
    explicit TLine(const TPoint& point, const TVector& vector);

    TSafeDouble cos(const TLine& other) const;
    bool isParallel(const TLine& other) const;
    bool isPerpendicular(const TLine& other) const;

    virtual TSafeDouble distToPoint(const TPoint& point) const;
    bool containsPoint(const TPoint& point) const;

    bool operator==(const TLine& other) const;
    bool operator!=(const TLine& other) const;

    std::optional<TPoint> intersection(const TLine& other) const;
    virtual std::optional<TPoint> intersection(const TPlane& plane) const;

    friend std::ostream& operator<<(std::ostream& os, const TLine& line);
};

class TRay : public TLine {
  public:
    TRay();
    explicit TRay(const TPoint& point1, const TPoint& point2);
    explicit TRay(const TPoint& point, const TVector& vector);

    TSafeDouble distToPoint(const TPoint& point) const override;

    std::optional<TPoint> intersection(const TPlane& plane) const override;

    friend std::ostream& operator<<(std::ostream& os, const TRay& ray);
};

} // namespace NRayTracingLib