#pragma once

#include "safe_double.h"
#include "vector.h"

#include <iostream>

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
    void print() const;

    TSafeDouble distToPoint(const TPoint& point) const;
    TSafeDouble distToLine(const TLine& line) const;
};

} // namespace NRayTracingLib

namespace std {

using namespace NRayTracingLib;

template <>
struct hash<TPoint> {
    size_t operator()(const TPoint& point) const {
        size_t seed = 0;
        auto hashFunction = hash<int64_t>();
        for (const auto& arg : {point.X, point.Y, point.Z}) {
            int64_t rounded = static_cast<int64_t>(llround(arg.Value / (ACCURACY * 2)));
            seed ^= hashFunction(rounded) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

} // namespace std