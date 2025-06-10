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
    explicit TPoint(const TVector& vector);

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
        auto hashFunction = std::hash<int64_t>();
        for (const auto& arg : {point.X, point.Y, point.Z}) {
            int64_t rounded = static_cast<int64_t>(std::llround(arg.Value / (NRayTracingLib::ACCURACY * 2)));
            seed ^= hashFunction(rounded) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

} // namespace std