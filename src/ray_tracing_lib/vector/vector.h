#pragma once

#include "../point/point.h"
#include "../safe_double/safe_double.h"

#include <iostream>

namespace NRayTracingLib {

class TPoint;

class TVector {
  public:
    TSafeDouble X, Y, Z;

    TVector(TSafeDouble x, TSafeDouble y, TSafeDouble z);
    explicit TVector(const TPoint& point);
    TVector(const TPoint& start, const TPoint& end);

    bool operator==(const TVector& other) const noexcept;
    bool operator!=(const TVector& other) const noexcept;

    TVector operator-() const noexcept;

    TVector operator+(const TVector& other) const noexcept;
    TVector operator-(const TVector& other) const noexcept;
    TVector operator*(TSafeDouble n) const noexcept;
    TVector operator/(TSafeDouble n) const;

    TVector& operator+=(const TVector& other) noexcept;
    TVector& operator-=(const TVector& other) noexcept;
    TVector& operator*=(TSafeDouble n) noexcept;
    TVector& operator/=(TSafeDouble n);

    TSafeDouble operator*(const TVector& other) const noexcept;
    TVector operator^(const TVector& other) const noexcept;

    TSafeDouble length() const noexcept;
    bool isZero() const noexcept;

    void normalize();
    TVector getNormalized() const;

    TSafeDouble cos(const TVector& other) const;
    bool isParallel(const TVector& other) const;
    bool isPerpendicular(const TVector& other) const;

    TVector projectTo(const TVector& other) const;

    friend std::ostream& operator<<(std::ostream& os, const TVector& vector);
    void print() const;
};

} // namespace NRayTracingLib