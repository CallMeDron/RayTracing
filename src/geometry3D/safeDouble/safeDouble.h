#pragma once

#include <iostream>

namespace NGeometry3D {

class TSafeDouble {
public:
  double Value;

  TSafeDouble();
  TSafeDouble(double v);

  TSafeDouble operator+(const TSafeDouble& other) const;
  TSafeDouble operator-(const TSafeDouble& other) const;
  TSafeDouble operator-() const;

  bool operator>(const TSafeDouble& other) const;
  bool operator<(const TSafeDouble& other) const;

  TSafeDouble abs() const;

  bool operator==(const TSafeDouble& other) const;
  bool operator!=(const TSafeDouble& other) const;

  TSafeDouble operator*(const TSafeDouble& other) const;
  TSafeDouble operator/(const TSafeDouble& other) const;
  TSafeDouble operator^(const TSafeDouble& other) const;

  TSafeDouble& operator+=(const TSafeDouble& other);
  TSafeDouble& operator-=(const TSafeDouble& other);
  TSafeDouble& operator*=(const TSafeDouble& other);
  TSafeDouble& operator/=(const TSafeDouble& other);
  TSafeDouble& operator^=(const TSafeDouble& other);

  bool operator>=(const TSafeDouble& other) const;
  bool operator<=(const TSafeDouble& other) const;

  friend std::ostream& operator<<(std::ostream& os, const TSafeDouble& sdouble);
  void print();
};

} // namespace NGeometry3D