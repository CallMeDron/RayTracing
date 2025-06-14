#pragma once

#include "common.h"
#include "figure.h"
#include "point.h"
#include "vector.h"

namespace NRayTracingLib {

class TLine;

class TPlane : public TFigure {
  public:
    TPoint Point;
    TVector Normal;

    TPlane();
    explicit TPlane(const TPoint& point, const TVector& normal);
    explicit TPlane(const TPoint& point, const TVector& vector1, const TVector& vector2);
    explicit TPlane(const TPoint& point1, const TPoint& point2, const TPoint& point3);
    explicit TPlane(const TPoint& point, const TLine& line);
    explicit TPlane(const TLine& line1, const TLine& line2);

    TSafeDouble distToPoint(const TPoint& point) const;
    bool containsPoint(const TPoint& point) const;
    bool containsLine(const TLine& line) const;

    bool operator==(const TPlane& other) const;
    bool operator!=(const TPlane& other) const;

    TSafeDouble cos(const TPlane& other) const;
    bool isParallel(const TPlane& other) const;
    bool isParallel(const TVector& vector) const;
    bool isPerpendicular(const TPlane& other) const;

    std::optional<std::pair<TPoint, TPointContainment>> intersection(const TLine& line) const override;
    std::optional<TLine> intersection(const TPlane& plane) const;

    friend std::ostream& operator<<(std::ostream& os, const TPlane& plane);
};

} // namespace NRayTracingLib