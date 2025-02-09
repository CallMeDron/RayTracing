#pragma once

#include <iostream>

namespace NGeometry3D {

class TSafeDouble {
  public:
    double Value;

    TSafeDouble(double v);

    bool operator>(const TSafeDouble& other) const;
    bool operator<(const TSafeDouble& other) const;

    bool operator==(const TSafeDouble& other) const;
    bool operator!=(const TSafeDouble& other) const;

    bool operator>=(const TSafeDouble& other) const;
    bool operator<=(const TSafeDouble& other) const;

    TSafeDouble abs() const;

    TSafeDouble operator-() const;

    TSafeDouble operator+(const TSafeDouble& other) const;
    TSafeDouble operator-(const TSafeDouble& other) const;
    TSafeDouble operator*(const TSafeDouble& other) const;
    TSafeDouble operator/(const TSafeDouble& other) const;
    TSafeDouble operator^(const TSafeDouble& other) const;

    TSafeDouble& operator+=(const TSafeDouble& other);
    TSafeDouble& operator-=(const TSafeDouble& other);
    TSafeDouble& operator*=(const TSafeDouble& other);
    TSafeDouble& operator/=(const TSafeDouble& other);
    TSafeDouble& operator^=(const TSafeDouble& other);

    friend std::ostream& operator<<(std::ostream& os, const TSafeDouble& sdouble);
    void print() const;
};

} // namespace NGeometry3D