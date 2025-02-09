#pragma once

#include "../point/point.h"
#include "../safeDouble/safeDouble.h"
#include "../vector/vector.h"

#include <iostream>

namespace NGeometry3D {

// class TPoint;
// class TVector;

class Line {
public:
  TPoint Point;
  TVector Vector;

  Line(const TPoint& point, const TVector& vector);
};

} // namespace NGeometry3D