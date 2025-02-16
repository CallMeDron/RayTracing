#pragma once

#include "../point/point.h"
#include "../vector/vector.h"

#include <iostream>
#include <optional>

namespace NGeometry3D {

class TLine {
  public:
    TPoint Point1;
    TPoint Point2;
    TVector Vector;

    TLine(const TPoint& point1, const TPoint& point2);
    TLine(const TPoint& point, const TVector& vector);

    TSafeDouble cos(const TLine& other) const;
    bool isParallel(const TLine& other) const;
    bool isPerpendicular(const TLine& other) const;

    // TSafeDouble distToPoint(const TPoint& point) const;
    // bool containsPoint(const TPoint& point) const;

    // bool operator==(const TLine& other) const;
    // bool operator!=(const TLine& other) const;

    // std::optional<TPoint> intersection(const TLine& other) const;
};

} // namespace NGeometry3D