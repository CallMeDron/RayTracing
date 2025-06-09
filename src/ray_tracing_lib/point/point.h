#pragma once

#include "../safe_double/safe_double.h"
#include "../vector/vector.h"

#include <iostream>

namespace NRayTracingLib {

class TVector;
class TLine;

class TPoint {
  public:
    TSafeDouble X, Y, Z;

    TPoint();
    explicit TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z);

    bool operator==(const TPoint& other) const noexcept;
    bool operator!=(const TPoint& other) const noexcept;

    TVector operator-(const TPoint& other) const noexcept;
    TPoint operator+(const TVector& vector) const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const TPoint& point);
    void print() const;

    TSafeDouble distToPoint(const TPoint& point) const noexcept;
    TSafeDouble distToLine(const TLine& line) const noexcept;
};

} // namespace NRayTracingLib