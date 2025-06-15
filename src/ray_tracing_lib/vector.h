#pragma once

#include "angle.h"
#include "common.h"
#include "point.h"

namespace NRayTracingLib {

class TPoint;
class TPlane;

class TVector {
  public:
    TSafeDouble X, Y, Z;

    TVector();
    explicit TVector(TSafeDouble x, TSafeDouble y, TSafeDouble z);
    explicit TVector(const TPoint& point);
    explicit TVector(const TPoint& start, const TPoint& end);

    bool operator==(const TVector& other) const;
    bool operator!=(const TVector& other) const;

    TVector operator-() const;

    TVector operator+(const TVector& other) const;
    TVector operator-(const TVector& other) const;
    TVector operator*(TSafeDouble n) const;
    TVector operator/(TSafeDouble n) const;

    TVector& operator+=(const TVector& other);
    TVector& operator-=(const TVector& other);
    TVector& operator*=(TSafeDouble n);
    TVector& operator/=(TSafeDouble n);

    TSafeDouble operator*(const TVector& other) const;
    TVector operator^(const TVector& other) const;

    TSafeDouble length() const;
    bool isZero() const;

    void normalize();
    TVector getNormalized() const;

    TSafeDouble cos(const TVector& other) const;
    TSafeDouble sin(const TVector& other) const;
    bool isParallel(const TVector& other) const;
    bool isPerpendicular(const TVector& other) const;

    TVector projectTo(const TVector& other) const;
    std::pair<TVector, TVector> projectedVectors(const TPlane& plane, const TAngle& angle) const;

    friend std::ostream& operator<<(std::ostream& os, const TVector& vector);
};

} // namespace NRayTracingLib