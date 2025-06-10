#pragma once

#include <iostream>

namespace NRayTracingLib {

constexpr double ACCURACY = 1e-9;
constexpr unsigned COUT_PRECISION = 10;

class TSafeDouble {
  public:
    double Value;

    TSafeDouble();
    TSafeDouble(int v);
    TSafeDouble(size_t v);
    TSafeDouble(double v);

    bool operator>(const TSafeDouble& other) const noexcept;
    bool operator<(const TSafeDouble& other) const noexcept;

    bool operator==(const TSafeDouble& other) const noexcept;
    bool operator!=(const TSafeDouble& other) const noexcept;

    bool operator>=(const TSafeDouble& other) const noexcept;
    bool operator<=(const TSafeDouble& other) const noexcept;

    TSafeDouble operator-() const noexcept;

    TSafeDouble abs() const noexcept;

    TSafeDouble operator+(const TSafeDouble& other) const noexcept;
    TSafeDouble operator-(const TSafeDouble& other) const noexcept;
    TSafeDouble operator*(const TSafeDouble& other) const noexcept;
    TSafeDouble operator/(const TSafeDouble& other) const;

    TSafeDouble& operator+=(const TSafeDouble& other) noexcept;
    TSafeDouble& operator-=(const TSafeDouble& other) noexcept;
    TSafeDouble& operator*=(const TSafeDouble& other) noexcept;
    TSafeDouble& operator/=(const TSafeDouble& other);

    TSafeDouble pow(const TSafeDouble& exponent) const;

    friend std::ostream& operator<<(std::ostream& os, const TSafeDouble& sdouble);
    void print() const;
};

} // namespace NRayTracingLib