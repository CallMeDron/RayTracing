#include "camera.h"

namespace NRayTracingLib {

TCamera::TCamera()
    : Position_{0.0, 0.0, 0.0}, Direction_{1.0, 0.0, 0.0}, ViewAngles_{120.0, 90.0}, Resolution_{600, 450} {};

TCamera::TCamera(const TPoint& position, const TVector& direction, const std::pair<TAngle, TAngle>& viewAngles,
                 const std::pair<uint16_t, uint16_t>& resolution)
    : Position_{position}, Direction_{direction}, ViewAngles_{viewAngles}, Resolution_{resolution} {};

} // namespace NRayTracingLib
