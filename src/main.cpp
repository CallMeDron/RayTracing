#include "ray_tracing_lib/all.h"

#include <chrono>

using namespace NRayTracingLib;

int main() {
    try {
        auto start = std::chrono::steady_clock::now();

        const TCamera camera{
            TPoint{10.0, 10.0, 10.0},
            TVector{-10.0, -10.0, -10.0},
            {TAngle{120.0}, TAngle{90.0}},
            {360, 270},
        };

        auto end = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        print(duration.count());

        camera.makePicture(createRegularDodecahedron(TPoint{0.0, 0.0, 0.0}, 1.0));

        end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        print(duration.count());

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}