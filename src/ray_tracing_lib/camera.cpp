#include "camera.h"

namespace NRayTracingLib {

TRay& TCamera::getRay(size_t i, size_t j) { return Rays_[i * Resolution_.first + j]; }

TVector TCamera::getHalfUpVector() const {
    const TPlane verticalPlane{Position_, Direction_, TVector{0.0, 0.0, 1.0}};
    const std::pair<TVector, TVector> verticalBorders =
        Direction_.projectedVectors(verticalPlane, ViewAngles_.second / 2.0);
    const TVector upLimitVector =
        verticalBorders.first.Z > verticalBorders.second.Z ? verticalBorders.first : verticalBorders.second;
    return upLimitVector - Direction_;
}
TVector TCamera::getHalfLeftVector() const {
    const TVector directionXY = Direction_ - TVector{0.0, 0.0, Direction_.Z};
    const TVector directionToLeftXY = TVector{0.0, 0.0, 1.0} ^ directionXY;
    const TPlane horizontalPlane{Position_, Direction_, directionToLeftXY};
    const std::pair<TVector, TVector> horizontalBorders =
        Direction_.projectedVectors(horizontalPlane, ViewAngles_.first / 2.0);
    const TVector leftLimitVector =
        horizontalBorders.first.cos(directionToLeftXY) > horizontalBorders.second.cos(directionToLeftXY)
            ? horizontalBorders.first
            : horizontalBorders.second;
    return leftLimitVector - Direction_;
}

void TCamera::initRays() {
    Direction_.normalize();

    Rays_.resize(Resolution_.first * Resolution_.second);

    const TVector halfUp = getHalfUpVector();
    const TVector halfLeft = getHalfLeftVector();

    for (size_t i = 0; i < Resolution_.second; i++) {
        double upCoeff = 1.0 - 2.0 * (static_cast<double>(i) / (Resolution_.second - 1));
        for (size_t j = 0; j < Resolution_.first; j++) {
            double leftCoeff = 1.0 - 2.0 * (static_cast<double>(j) / (Resolution_.first - 1));
            getRay(i, j) = TRay{Position_, Direction_ + halfUp * upCoeff + halfLeft * leftCoeff};
        }
    }
}

TCamera::TCamera(const TPoint& position, const TVector& direction, const std::pair<TAngle, TAngle>& viewAngles,
                 const std::pair<uint16_t, uint16_t>& resolution)
    : Position_{position}, Direction_{direction}, ViewAngles_{viewAngles}, Resolution_{resolution} {
    initRays();
};

} // namespace NRayTracingLib
