#include "ray_tracing_lib\all.h"

using namespace NRayTracingLib;

struct TCamera {
    TPoint Position = TPoint{0, 0, 0};
    TVector Direction = TVector{1, 0, 0};
    std::pair<TAngle, TAngle> ViewAngles{120.0, 90.0};
    std::pair<uint16_t, uint16_t> Resolution{600, 450};
};

int main() { std::cout << TPolygon({TPoint{0, 1, 0}, TPoint{1, 0, 0}, TPoint{1, 2, 2}, TPoint{2, 1, 2}}); }