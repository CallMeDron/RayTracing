#pragma once

#include <iostream>

namespace NRayTracingLib {

// affects the maximum range of coordinate values
// ACCURACY = 1e-9 allows use abs to 9.22×10^9
// ACCURACY = 1e-16 allows use abs to 922
static constexpr double ACCURACY = 1e-9;
static constexpr unsigned COUT_PRECISION = 10;

class TSafeDouble {
  public:
    double Value;

    TSafeDouble();
    TSafeDouble(int v);
    TSafeDouble(size_t v);
    TSafeDouble(double v);

    bool operator>(const TSafeDouble& other) const;
    bool operator<(const TSafeDouble& other) const;

    bool operator==(const TSafeDouble& other) const;
    bool operator!=(const TSafeDouble& other) const;

    bool operator>=(const TSafeDouble& other) const;
    bool operator<=(const TSafeDouble& other) const;

    TSafeDouble operator-() const;

    TSafeDouble abs() const;

    TSafeDouble operator+(const TSafeDouble& other) const;
    TSafeDouble operator-(const TSafeDouble& other) const;
    TSafeDouble operator*(const TSafeDouble& other) const;
    TSafeDouble operator/(const TSafeDouble& other) const;

    TSafeDouble& operator+=(const TSafeDouble& other);
    TSafeDouble& operator-=(const TSafeDouble& other);
    TSafeDouble& operator*=(const TSafeDouble& other);
    TSafeDouble& operator/=(const TSafeDouble& other);

    TSafeDouble pow(const TSafeDouble& exponent) const;

    friend std::ostream& operator<<(std::ostream& os, const TSafeDouble& sdouble);
    void print() const;
};

} // namespace NRayTracingLib