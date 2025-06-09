#pragma once

#include "../point/point.h"
#include "../vector/vector.h"

#include <iostream>
#include <optional>

namespace NRayTracingLib {

class TLine;

class TPlane {
  public:
    TPoint Point;
    TVector Normal;

    TPlane(const TPoint& point, const TVector& normal);
    explicit TPlane(const TPoint& point, const TVector& normal);
    explicit TPlane(const TPoint& point, const TVector& vector1, const TVector& vector2);
    explicit TPlane(const TPoint& point1, const TPoint& point2, const TPoint& point3);
    explicit TPlane(const TPoint& point, const TLine& line);
    explicit TPlane(const TLine& line1, const TLine& line2);

    TSafeDouble distToPoint(const TPoint& point) const noexcept;
    bool containsPoint(const TPoint& point) const noexcept;
    bool containsLine(const TLine& line) const;

    bool operator==(const TPlane& other) const;
    bool operator!=(const TPlane& other) const;

    TSafeDouble cos(const TPlane& other) const;
    bool isParallel(const TPlane& other) const;
    bool isPerpendicular(const TPlane& other) const;

    std::optional<TPoint> intersection(const TLine& line) const;
    std::optional<TLine> intersection(const TPlane& plane) const;

    // friend std::ostream& operator<<(std::ostream& os, const TLine& line);
    // void print() const;
};

} // namespace NRayTracingLib