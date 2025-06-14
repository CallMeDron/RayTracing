#include "ray_tracing_lib/all.h"

using namespace NRayTracingLib;

int main() {
    try {
        TCamera camera;

        const TPolyhedron dodecahedron = CreateRegularDodecahedron(TPoint(), 10.0);
        const TPolyhedron icosahedron = CreateRegularIcosahedron(TPoint(), 10.0);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}