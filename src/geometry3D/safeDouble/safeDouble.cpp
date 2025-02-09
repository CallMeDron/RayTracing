#include "safeDouble.h"

#include <iomanip>
#include <stdexcept>

namespace NGeometry3D {

constexpr double ACCURACY = 1e-15;

TSafeDouble::TSafeDouble(double v) : Value(v) {}

bool TSafeDouble::operator>(const TSafeDouble& other) const { return (*this - other).Value > ACCURACY; }
bool TSafeDouble::operator<(const TSafeDouble& other) const { return (*this - other).Value < -ACCURACY; }

bool TSafeDouble::operator==(const TSafeDouble& other) const { return !(*this > other) && !(*this < other); }
bool TSafeDouble::operator!=(const TSafeDouble& other) const { return !(*this == other); }

bool TSafeDouble::operator>=(const TSafeDouble& other) const { return (*this > other || *this == other); }
bool TSafeDouble::operator<=(const TSafeDouble& other) const { return (*this < other || *this == other); }

TSafeDouble TSafeDouble::abs() const {
    if (*this > TSafeDouble{0.0}) {
        return TSafeDouble{Value};
    } else if (*this < TSafeDouble{0.0}) {
        return TSafeDouble{-Value};
    } else {
        return TSafeDouble{0.0};
    }
}

TSafeDouble TSafeDouble::operator-() const { return TSafeDouble{-Value}; }

TSafeDouble TSafeDouble::operator+(const TSafeDouble& other) const { return TSafeDouble{Value + other.Value}; }
TSafeDouble TSafeDouble::operator-(const TSafeDouble& other) const { return TSafeDouble{Value - other.Value}; }
TSafeDouble TSafeDouble::operator*(const TSafeDouble& other) const { return TSafeDouble{Value * other.Value}; }
TSafeDouble TSafeDouble::operator/(const TSafeDouble& other) const {
    if (other != TSafeDouble{0.0}) {
        return TSafeDouble{Value / other.Value};
    } else {
        throw std::runtime_error("Error: division by 0");
    }
}
TSafeDouble TSafeDouble::operator^(const TSafeDouble& other) const { return TSafeDouble{std::pow(Value, other.Value)}; }

TSafeDouble& TSafeDouble::operator+=(const TSafeDouble& other) {
    *this = *this + other;
    return *this;
}
TSafeDouble& TSafeDouble::operator-=(const TSafeDouble& other) {
    *this = *this - other;
    return *this;
}
TSafeDouble& TSafeDouble::operator*=(const TSafeDouble& other) {
    *this = *this * other;
    return *this;
}
TSafeDouble& TSafeDouble::operator/=(const TSafeDouble& other) {
    *this = *this / other;
    return *this;
}
TSafeDouble& TSafeDouble::operator^=(const TSafeDouble& other) {
    *this = *this ^ other;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const TSafeDouble& sdouble) {
    std::cout << std::scientific;
    std::cout << std::setprecision(1);
    return os << sdouble.Value;
}

void TSafeDouble::print() const { std::cout << *this; }

} // namespace NGeometry3D