#include "angle.h"

namespace NRayTracingLib {

static constexpr double FULL_CIRCLE_DEGREES = 360.0;
static constexpr double FULL_CIRCLE_RADIANS = 2 * std::numbers::pi;
static constexpr double DEGREES_IN_RADIAN = FULL_CIRCLE_DEGREES / FULL_CIRCLE_RADIANS;

TAngle::TAngle(TSafeDouble angle, bool fromDegrees) {
    if (fromDegrees) {
        Degrees_ = fmod(angle.Value, FULL_CIRCLE_DEGREES);
        if (Degrees_ < 0.0) {
            Degrees_ += FULL_CIRCLE_DEGREES;
        }
        Radians_ = Degrees_ / DEGREES_IN_RADIAN;
    } else {
        Radians_ = fmod(angle.Value, FULL_CIRCLE_RADIANS);
        if (Radians_ < 0.0) {
            Radians_ += FULL_CIRCLE_RADIANS;
        }
        Degrees_ = Radians_ * DEGREES_IN_RADIAN;
    }
}

TSafeDouble TAngle::getDegrees() const { return Degrees_; }
TSafeDouble TAngle::getRadians() const { return Radians_; }

TSafeDouble TAngle::cos() const { return std::cos(Radians_.Value); }
TSafeDouble TAngle::sin() const { return std::sin(Radians_.Value); }
TSafeDouble TAngle::tg() const { return std::tan(Radians_.Value); }

} // namespace NRayTracingLib
