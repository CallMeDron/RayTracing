#include "vector.h"

namespace NRayTracingLib {

TVector::TVector(TSafeDouble x, TSafeDouble y, TSafeDouble z) : X(x), Y(y), Z(z) {}
TVector::TVector(const TPoint& point) : X(point.X), Y(point.Y), Z(point.Z) {}
TVector::TVector(const TPoint& start, const TPoint& end) : TVector{end - start} {}

bool TVector::operator==(const TVector& other) const { return (X == other.X) && (Y == other.Y) && (Z == other.Z); }
bool TVector::operator!=(const TVector& other) const { return !(*this == other); }

TVector TVector::operator-() const { return TVector{-X, -Y, -Z}; }

TVector TVector::operator+(const TVector& other) const { return TVector{X + other.X, Y + other.Y, Z + other.Z}; }
TVector TVector::operator-(const TVector& other) const { return TVector{X - other.X, Y - other.Y, Z - other.Z}; }
TVector TVector::operator*(TSafeDouble n) const { return TVector{X * n, Y * n, Z * n}; }
TVector TVector::operator/(TSafeDouble n) const { return TVector{X / n, Y / n, Z / n}; }

TVector& TVector::operator+=(const TVector& other) {
    *this = *this + other;
    return *this;
}
TVector& TVector::operator-=(const TVector& other) {
    *this = *this - other;
    return *this;
}
TVector& TVector::operator*=(TSafeDouble n) {
    *this = *this * n;
    return *this;
}
TVector& TVector::operator/=(TSafeDouble n) {
    *this = *this / n;
    return *this;
}

TSafeDouble TVector::operator*(const TVector& other) const { return X * other.X + Y * other.Y + Z * other.Z; }
TVector TVector::operator^(const TVector& other) const {
    return TVector{Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X};
}

TSafeDouble TVector::length() const { return ((X.pow(2)) + (Y.pow(2)) + (Z.pow(2))).pow(0.5); }
bool TVector::isZero() const { return X == TSafeDouble{0.0} && Y == TSafeDouble{0.0} && Z == TSafeDouble{0.0}; }

void TVector::normalize() { *this /= length(); }
TVector TVector::getNormalized() const {
    TVector normalized{*this};
    normalized.normalize();
    return normalized;
}

TSafeDouble TVector::cos(const TVector& other) const { return (*this * other) / length() / other.length(); }
bool TVector::isParallel(const TVector& other) const { return cos(other).abs() == TSafeDouble{1.0}; }
bool TVector::isPerpendicular(const TVector& other) const { return cos(other) == TSafeDouble{0.0}; }

TVector TVector::projectTo(const TVector& other) const { return other * ((*this * other) / (other * other)); }

std::ostream& operator<<(std::ostream& os, const TVector& vector) {
    return os << "vector = {" << vector.X << ", " << vector.Y << ", " << vector.Z << "}\n";
}
void TVector::print() const { std::cout << *this; }

} // namespace NRayTracingLib