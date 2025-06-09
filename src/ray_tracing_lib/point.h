#pragma once

#include "safe_double.h"
#include "vector.h"

#include <functional>
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

namespace std {

template <>
struct hash<NRayTracingLib::TPoint> {
    size_t operator()(const NRayTracingLib::TPoint& point) const {
        size_t seed = 0;
        auto hashFunction = std::hash<double>();
        for (const auto& arg : {point.X, point.Y, point.Z}) {
            seed ^= hashFunction(arg.Value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

} // namespace std