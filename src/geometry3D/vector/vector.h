#pragma once

#include "../point/point.h"
#include "../safeDouble/safeDouble.h"

#include <iostream>

namespace NGeometry3D {

class TPoint;

class TVector {
public:
  TSafeDouble X, Y, Z;

  TVector(TSafeDouble x, TSafeDouble y, TSafeDouble z);
  explicit TVector(const TPoint& point);
  TVector(const TPoint& start, const TPoint& end);

  bool operator==(const TVector& other) const;
  bool operator!=(const TVector& other) const;

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
  bool isParallel(const TVector& other) const;
  bool isPerpendicular(const TVector& other) const;

  friend std::ostream& operator<<(std::ostream& os, const TVector& vector);
  void print() const;
};

} // namespace NGeometry3D