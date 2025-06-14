#pragma once

#include "common.h"
#include "safe_double.h"
#include "vector.h"

namespace NRayTracingLib {

class TVector;
class TLine;

class TPoint {
  public:
    TSafeDouble X, Y, Z;

    TPoint();
    explicit TPoint(TSafeDouble x, TSafeDouble y, TSafeDouble z);
    explicit TPoint(const TVector& vector);

    bool operator==(const TPoint& other) const;
    bool operator!=(const TPoint& other) const;

    TVector operator-(const TPoint& other) const;
    TPoint operator+(const TVector& vector) const;

    bool operator<(const TPoint& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TPoint& point);

    TSafeDouble distToPoint(const TPoint& point) const;
    TSafeDouble distToLine(const TLine& line) const;
};

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

template <>
struct hash<TPoint> {
    size_t operator()(const TPoint& point) const;
};

} // namespace std