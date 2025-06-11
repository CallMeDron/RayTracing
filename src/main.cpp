#include "ray_tracing_lib/all.h"

using namespace NRayTracingLib;

int main() {
    TCamera camera;
    std::cout << TPolygon({TPoint{0, 1, 0}, TPoint{1, 0, 0}, TPoint{1, 2, 2}, TPoint{2, 1, 2}});
}