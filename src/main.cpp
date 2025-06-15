#include "ray_tracing_lib/all.h"

#include <chrono>

using namespace NRayTracingLib;

int main() {
    try {
        auto start = std::chrono::steady_clock::now();

        TCamera camera{
            TPoint{10.0, 10.0, 10.0},
            TVector{-10.0, -10.0, -10.0},
            {TAngle{10.0}, TAngle{10.0}},
            {700, 700},
        };

        const TPolyhedron figure = createRegularDodecahedron(TPoint{0.0, 0.0, 0.0}, 1.0);
        camera.makePicture(figure);

        const char* filename = "D:/Coding/C++/RayTracing/src/output.png";
        camera.savePicture(filename);

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        print(duration.count());

    } catch (const std::exception& e) {
        print(e.what());
    }
}