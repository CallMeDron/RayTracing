#include "ray_tracing_lib/all.h"

using namespace NRayTracingLib;

int main() {
    try {
        TCamera camera;

        const TPolyhedron tetrahedron = CreateRegularTetrahedron(TPoint(), 10.0);
        print(tetrahedron);

        const TPolyhedron hexahedron = CreateRegularHexahedron(TPoint(), 10.0);
        print(hexahedron);

        const TPolyhedron octahedron = CreateRegularOctahedron(TPoint(), 10.0);
        print(octahedron);

        const TPolyhedron dodecahedron = CreateRegularDodecahedron(TPoint(), 10.0);
        print(dodecahedron);

        const TPolyhedron icosahedron = CreateRegularIcosahedron(TPoint(), 10.0);
        print(icosahedron);

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}