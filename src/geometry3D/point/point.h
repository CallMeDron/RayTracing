#pragma once

#include "../safeDouble/safeDouble.h"
#include "../vector/vector.h"

#include <iostream>

namespace NGeometry3D {

class TVector;

class TPoint {
  public:
    TSafeDouble X, Y, Z;

    TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z);

    bool operator==(const TPoint& other) const;
    bool operator!=(const TPoint& other) const;

    TVector operator-(const TPoint& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TPoint& point);
    void print() const;
};

} // namespace NGeometry3D