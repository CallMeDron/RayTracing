#include "safe_double.h"

#include <cmath>
#include <iomanip>
#include <stdexcept>

namespace NRayTracingLib {

TSafeDouble::TSafeDouble() : Value(0.0) {}
TSafeDouble::TSafeDouble(int v) : Value(static_cast<double>(v)) {}
TSafeDouble::TSafeDouble(size_t v) : Value(static_cast<double>(v)) {}
TSafeDouble::TSafeDouble(double v) : Value(v) {}

bool TSafeDouble::operator>(const TSafeDouble& other) const noexcept { return (Value - other.Value) > ACCURACY; }
bool TSafeDouble::operator<(const TSafeDouble& other) const noexcept { return (Value - other.Value) < -ACCURACY; }

bool TSafeDouble::operator==(const TSafeDouble& other) const noexcept { return !(*this > other) && !(*this < other); }
bool TSafeDouble::operator!=(const TSafeDouble& other) const noexcept { return !(*this == other); }

bool TSafeDouble::operator>=(const TSafeDouble& other) const noexcept { return (*this > other) || (*this == other); }
bool TSafeDouble::operator<=(const TSafeDouble& other) const noexcept { return (*this < other) || (*this == other); }

TSafeDouble TSafeDouble::operator-() const noexcept { return -Value; }

TSafeDouble TSafeDouble::abs() const noexcept {
    if (*this > 0.0) {
        return *this;
    } else if (*this < 0.0) {
        return -(*this);
    } else {
        return 0.0;
    }
}

TSafeDouble TSafeDouble::operator+(const TSafeDouble& other) const noexcept { return Value + other.Value; }
TSafeDouble TSafeDouble::operator-(const TSafeDouble& other) const noexcept { return Value - other.Value; }
TSafeDouble TSafeDouble::operator*(const TSafeDouble& other) const noexcept { return Value * other.Value; }
TSafeDouble TSafeDouble::operator/(const TSafeDouble& other) const {
    if (other != 0.0) {
        return Value / other.Value;
    } else {
        throw std::runtime_error("Error: division by 0");
    }
}

TSafeDouble& TSafeDouble::operator+=(const TSafeDouble& other) noexcept {
    *this = *this + other;
    return *this;
}
TSafeDouble& TSafeDouble::operator-=(const TSafeDouble& other) noexcept {
    *this = *this - other;
    return *this;
}
TSafeDouble& TSafeDouble::operator*=(const TSafeDouble& other) noexcept {
    *this = *this * other;
    return *this;
}
TSafeDouble& TSafeDouble::operator/=(const TSafeDouble& other) {
    *this = *this / other;
    return *this;
}

TSafeDouble TSafeDouble::pow(const TSafeDouble& exponent) const { return std::pow(Value, exponent.Value); }

std::ostream& operator<<(std::ostream& os, const TSafeDouble& sdouble) {
    os << std::setprecision(COUT_PRECISION);
    return os << sdouble.Value;
}
void TSafeDouble::print() const { std::cout << *this; }

} // namespace NRayTracingLib