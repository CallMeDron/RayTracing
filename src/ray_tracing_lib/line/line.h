#pragma once

#include "../point/point.h"
#include "../vector/vector.h"

#include <iostream>
#include <optional>

namespace NRayTracingLib {

class TLine {
  public:
    TPoint Point;
    TVector Vector;

    explicit TLine(const TPoint& point1, const TPoint& point2);
    explicit TLine(const TPoint& point, const TVector& vector);

    TSafeDouble cos(const TLine& other) const;
    bool isParallel(const TLine& other) const;
    bool isPerpendicular(const TLine& other) const;

    TSafeDouble distToPoint(const TPoint& point) const noexcept;
    bool containsPoint(const TPoint& point) const noexcept;

    bool operator==(const TLine& other) const;
    bool operator!=(const TLine& other) const;

    std::optional<TPoint> intersection(const TLine& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TLine& line);
    void print() const;
};

} // namespace NRayTracingLib