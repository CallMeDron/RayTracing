#include "camera.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

namespace NRayTracingLib {

void TCamera::initHalfUpVector() {
    const TPlane verticalPlane{Position_, Direction_, TVector{0.0, 0.0, 1.0}};
    const std::pair<TVector, TVector> verticalBorders =
        Direction_.projectedVectors(verticalPlane, HeightViewAngle_ / 2.0);
    const TVector upLimitVector =
        verticalBorders.first.Z > verticalBorders.second.Z ? verticalBorders.first : verticalBorders.second;
    if (upLimitVector != Direction_) {
        HalfUpVector_ = upLimitVector - Direction_;
    } else {
        throw std::runtime_error("Error: zero half up vector in camera");
    }
}
void TCamera::initHalfLeftVector() {
    const TVector directionXY = Direction_ - TVector{0.0, 0.0, Direction_.Z};
    const TVector directionToLeftXY = TVector{0.0, 0.0, 1.0} ^ directionXY;
    const TPlane horizontalPlane{Position_, Direction_, directionToLeftXY};
    const std::pair<TVector, TVector> horizontalBorders =
        Direction_.projectedVectors(horizontalPlane, WidthViewAngle_ / 2.0);
    const TVector leftLimitVector =
        horizontalBorders.first.cos(directionToLeftXY) > horizontalBorders.second.cos(directionToLeftXY)
            ? horizontalBorders.first
            : horizontalBorders.second;
    if (leftLimitVector != Direction_) {
        HalfLeftVector_ = leftLimitVector - Direction_;
    } else {
        throw std::runtime_error("Error: zero half left vector in camera");
    }
}

TCamera::TCamera(const TPoint& position, const TVector& direction, const std::pair<TAngle, TAngle>& viewAngles,
                 const std::pair<uint16_t, uint16_t>& resolution)
    : Position_{position}, Direction_{direction}, WidthViewAngle_{viewAngles.first},
      HeightViewAngle_{viewAngles.second}, WidthResolution_{resolution.first}, HeightResolution_{resolution.second} {
    Direction_.normalize();

    ImageData_.resize(WidthResolution_ * HeightResolution_ * 3);

    initHalfUpVector();
    initHalfLeftVector();
};

uint8_t coordinateToByte(double coord) {
    const double minCoord = -1.5;
    const double maxCoord = 1.5;
    double normalized = (coord - minCoord) / (maxCoord - minCoord);
    return static_cast<uint8_t>(normalized * 255.0);
}

void TCamera::makePicture(const TFigure& figure) {
    const size_t iMax = HeightResolution_ - 1;
    const size_t jMax = WidthResolution_ - 1;

    for (size_t i = 0; i < HeightResolution_; i++) {
        const double upProgress = static_cast<double>(i) / iMax;
        print("Progress =", upProgress * 100, "%");
        const double upCoeff = 1.0 - 2.0 * upProgress;
        for (size_t j = 0; j < WidthResolution_; j++) {
            const double leftProgress = static_cast<double>(j) / jMax;
            const double leftCoeff = 1.0 - 2.0 * leftProgress;
            const TRay ray{Position_, Direction_ + HalfUpVector_ * upCoeff + HalfLeftVector_ * leftCoeff};
            const std::optional<std::pair<TPoint, TPointContainment>> intersection = figure.intersection(ray);
            const size_t idx = (i * WidthResolution_ + j) * 3;
            if (!intersection.has_value()) {
                continue;
            }
            if (intersection.value().second == TPointContainment::OnBoundary) {
                ImageData_[idx] = 255;
                ImageData_[idx + 1] = 255;
                ImageData_[idx + 2] = 128;
            } else if (intersection.value().second == TPointContainment::Inside) {
                const TPoint point = intersection.value().first;
                ImageData_[idx] = coordinateToByte(point.X.Value);     // static_cast<uint8_t>(upProgress * 256);
                ImageData_[idx + 1] = coordinateToByte(point.Y.Value); // static_cast<uint8_t>(leftProgress * 256);
                ImageData_[idx + 2] = coordinateToByte(point.Z.Value); // 128;
            }
        }
    }
}

void TCamera::savePicture(const char* filename) const {
    if (!stbi_write_png(filename, static_cast<int>(WidthResolution_), static_cast<int>(HeightResolution_), 3,
                        ImageData_.data(), static_cast<int>(WidthResolution_ * 3))) {
        throw std::runtime_error("Failed to write PNG file");
    }
}

} // namespace NRayTracingLib
