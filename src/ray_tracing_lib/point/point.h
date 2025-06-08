#pragma once

#include "../safe_double/safe_double.h"
#include "../vector/vector.h"

#include <iostream>

namespace NRayTracingLib {

class TVector;

class TPoint {
  public:
    TSafeDouble X, Y, Z;

    TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z);

    bool operator==(const TPoint& other) const;
    bool operator!=(const TPoint& other) const;

    TVector operator-(const TPoint& other) const;
    TPoint operator+(const TVector& vector) const;

    friend std::ostream& operator<<(std::ostream& os, const TPoint& point);
    void print() const;
};

} // namespace NRayTracingLib