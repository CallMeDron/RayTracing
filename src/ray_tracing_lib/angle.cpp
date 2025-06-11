#include "angle.h"

#include <cmath>
#include <numbers>

namespace NRayTracingLib {

TAngle::TAngle(TSafeDouble angle, bool fromDegrees) {
    if (fromDegrees) {
        Degrees_ = fmod(angle.Value, 360.0);
        if (Degrees_ < 0.0) {
            Degrees_ += 360.0;
        }
        Radians_ = Degrees_ / (180.0 / std::numbers::pi);
    } else {
        Radians_ = fmod(angle.Value, 2 * std::numbers::pi);
        if (Radians_ < 0.0) {
            Radians_ += 2 * std::numbers::pi;
        }
        Degrees_ = Radians_ * (180.0 / std::numbers::pi);
    }
}

TSafeDouble TAngle::getDegrees() const { return Degrees_; }
TSafeDouble TAngle::getRadians() const { return Radians_; }

TSafeDouble TAngle::cos() const { return std::cos(Radians_.Value); }
TSafeDouble TAngle::sin() const { return std::sin(Radians_.Value); }

} // namespace NRayTracingLib
