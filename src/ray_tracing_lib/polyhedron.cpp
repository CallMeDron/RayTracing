#include "polyhedron.h"

namespace NRayTracingLib {

TPolyhedron::TPolyhedron(const std::unordered_set<TPolygon>& polygons) : Faces_(polygons) {
    std::unordered_map<TEdge, uint8_t> edgesCount;

    for (const auto& face : Faces_) {
        for (size_t i = 0; i < face.getPoints().size(); i++) {
            size_t nextIdx = (i + 1) % face.getPoints().size();
            TEdge edge{face.getPoints()[i], face.getPoints()[nextIdx]};
            edgesCount[edge] += 1;
        }
    }

    for (const auto& [edge, count] : edgesCount) {
        if (count != 2) {
            throw std::runtime_error("Error: creating not closed polyhedron");
        }
    }
}

const std::unordered_set<TPolygon>& TPolyhedron::getFaces() const { return Faces_; }

std::optional<TPoint> TPolyhedron::intersection(const TLine& line) const {
    // closest to line.Point intersection point

    std::vector<std::pair<TPoint, double>> intersectionsWithDistances;

    for (const auto& face : Faces_) {
        std::optional<TPoint> intersection = face.intersection(line);
        if (intersection != std::nullopt) {
            intersectionsWithDistances.push_back(
                {intersection.value(), line.Point.distToPoint(intersection.value()).Value});
        }
    }

    sort(intersectionsWithDistances.begin(), intersectionsWithDistances.end(),
         [&line](const auto& lhs, const auto& rhs) { return lhs.second < rhs.second; });

    if (intersectionsWithDistances.empty()) {
        return std::nullopt;
    }
    return intersectionsWithDistances[0].first;
}

std::ostream& operator<<(std::ostream& os, const TPolyhedron& polyhedron) {
    os << "polyhedron:\n";
    for (const auto& face : polyhedron.getFaces()) {
        os << face;
    }
    return os;
}

TPolyhedron CreateRegularTetrahedron(const TPoint& center, TSafeDouble edgeLength) {
    const double sqrt_3 = std::sqrt(3.0);
    const double sqrt_6 = std::sqrt(6.0);
    const double r = edgeLength.Value / sqrt_3;
    const double h0 = edgeLength.Value * sqrt_6 / 12.0;
    const double h1 = edgeLength.Value * sqrt_6 / 4.0;

    const TPoint p1 = center + TVector{0.0, 0.0, h1};
    const TPoint p2 = center + TVector{r, 0.0, -h0};
    const TPoint p3 = center + TVector{-r / 2, r * sqrt_3 / 2, -h0};
    const TPoint p4 = center + TVector{-r / 2, -r * sqrt_3 / 2, -h0};

    const TPolygon f1{{p1, p2, p3}};
    const TPolygon f2{{p1, p2, p4}};
    const TPolygon f3{{p1, p3, p4}};
    const TPolygon f4{{p2, p3, p4}};

    for (const auto& face : {f1, f2, f3, f4}) {
        if ((face.getPoints().size() != 3) || !face.getAnglesIsEqual() || !face.getEdgesIsEqual() ||
            (face.getPoints()[0].distToPoint(face.getPoints()[1]) != edgeLength)) {
            throw std::runtime_error("Error: creating regular tetrahedron with broken face");
        }
    }

    const std::unordered_set<TPolygon> faces{f1, f2, f3, f4};
    if (faces.size() != 4) {
        throw std::runtime_error("Error: creating regular tetrahedron with != 4 faces");
    }

    return TPolyhedron{faces};
}
TPolyhedron CreateRegularHexahedron(const TPoint& center, TSafeDouble edgeLength) {
    const TSafeDouble multiplier = edgeLength / 2.0;

    const TPoint p1 = center + TVector{1.0, 1.0, 1.0} * multiplier;
    const TPoint p2 = center + TVector{1.0, 1.0, -1.0} * multiplier;
    const TPoint p3 = center + TVector{1.0, -1.0, 1.0} * multiplier;
    const TPoint p4 = center + TVector{1.0, -1.0, -1.0} * multiplier;
    const TPoint p5 = center + TVector{-1.0, 1.0, 1.0} * multiplier;
    const TPoint p6 = center + TVector{-1.0, 1.0, -1.0} * multiplier;
    const TPoint p7 = center + TVector{-1.0, -1.0, 1.0} * multiplier;
    const TPoint p8 = center + TVector{-1.0, -1.0, -1.0} * multiplier;

    const TPolygon f1{{p1, p2, p6, p5}};
    const TPolygon f2{{p3, p4, p8, p7}};
    const TPolygon f3{{p1, p3, p7, p5}};
    const TPolygon f4{{p2, p4, p8, p6}};
    const TPolygon f5{{p5, p7, p8, p6}};
    const TPolygon f6{{p1, p2, p4, p3}};

    for (const auto& face : {f1, f2, f3, f4, f5, f6}) {
        if ((face.getPoints().size() != 4) || !face.getAnglesIsEqual() || !face.getEdgesIsEqual() ||
            (face.getPoints()[0].distToPoint(face.getPoints()[1]) != edgeLength)) {
            throw std::runtime_error("Error: creating regular hexahedron with broken face");
        }
    }

    const std::unordered_set<TPolygon> faces{f1, f2, f3, f4, f5, f6};
    if (faces.size() != 6) {
        throw std::runtime_error("Error: creating regular hexahedron with != 6 faces");
    }

    return TPolyhedron{faces};
}
TPolyhedron CreateRegularOctahedron(const TPoint& center, TSafeDouble edgeLength) {
    const TSafeDouble multiplier = edgeLength / sqrt(2.0);

    const TPoint p1 = center + TVector{1.0, 0.0, 0.0} * multiplier;
    const TPoint p2 = center + TVector{-1.0, 0.0, 0.0} * multiplier;
    const TPoint p3 = center + TVector{0.0, 1.0, 0.0} * multiplier;
    const TPoint p4 = center + TVector{0.0, -1.0, 0.0} * multiplier;
    const TPoint p5 = center + TVector{0.0, 0.0, 1.0} * multiplier;
    const TPoint p6 = center + TVector{0.0, 0.0, -1.0} * multiplier;

    const TPolygon f1{{p1, p3, p5}};
    const TPolygon f2{{p3, p2, p5}};
    const TPolygon f3{{p2, p4, p5}};
    const TPolygon f4{{p4, p1, p5}};
    const TPolygon f5{{p1, p3, p6}};
    const TPolygon f6{{p3, p2, p6}};
    const TPolygon f7{{p2, p4, p6}};
    const TPolygon f8{{p4, p1, p6}};

    for (const auto& face : {f1, f2, f3, f4, f5, f6, f7, f8}) {
        if ((face.getPoints().size() != 3) || !face.getAnglesIsEqual() || !face.getEdgesIsEqual() ||
            (face.getPoints()[0].distToPoint(face.getPoints()[1]) != edgeLength)) {
            throw std::runtime_error("Error: creating regular octahedron with broken face");
        }
    }

    const std::unordered_set<TPolygon> faces{f1, f2, f3, f4, f5, f6, f7, f8};
    if (faces.size() != 8) {
        throw std::runtime_error("Error: creating regular octahedron with != 8 faces");
    }

    return TPolyhedron{faces};
}
TPolyhedron CreateRegularDodecahedron(const TPoint& center, TSafeDouble edgeLength) {
    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double inv_phi = 1.0 / phi;
    const double baseEdgeLength = sqrt(5) - 1;
    const double scale = edgeLength.Value / baseEdgeLength;

    const TPoint p0 = center + TVector{1.0, 1.0, 1.0} * scale;
    const TPoint p1 = center + TVector{1.0, 1.0, -1.0} * scale;
    const TPoint p2 = center + TVector{1.0, -1.0, 1.0} * scale;
    const TPoint p3 = center + TVector{1.0, -1.0, -1.0} * scale;
    const TPoint p4 = center + TVector{-1.0, 1.0, 1.0} * scale;
    const TPoint p5 = center + TVector{-1.0, 1.0, -1.0} * scale;
    const TPoint p6 = center + TVector{-1.0, -1.0, 1.0} * scale;
    const TPoint p7 = center + TVector{-1.0, -1.0, -1.0} * scale;
    const TPoint p8 = center + TVector{0.0, inv_phi, phi} * scale;
    const TPoint p9 = center + TVector{0.0, inv_phi, -phi} * scale;
    const TPoint p10 = center + TVector{0.0, -inv_phi, phi} * scale;
    const TPoint p11 = center + TVector{0.0, -inv_phi, -phi} * scale;
    const TPoint p12 = center + TVector{inv_phi, phi, 0.0} * scale;
    const TPoint p13 = center + TVector{inv_phi, -phi, 0.0} * scale;
    const TPoint p14 = center + TVector{-inv_phi, phi, 0.0} * scale;
    const TPoint p15 = center + TVector{-inv_phi, -phi, 0.0} * scale;
    const TPoint p16 = center + TVector{phi, 0.0, inv_phi} * scale;
    const TPoint p17 = center + TVector{phi, 0.0, -inv_phi} * scale;
    const TPoint p18 = center + TVector{-phi, 0.0, inv_phi} * scale;
    const TPoint p19 = center + TVector{-phi, 0.0, -inv_phi} * scale;

    const TPolygon f1{{p0, p1, p12, p16, p17}};
    const TPolygon f2{{p0, p2, p8, p10, p16}};
    const TPolygon f3{{p0, p4, p8, p12, p14}};
    const TPolygon f4{{p1, p3, p9, p11, p17}};
    const TPolygon f5{{p1, p5, p9, p12, p14}};
    const TPolygon f6{{p2, p3, p13, p16, p17}};
    const TPolygon f7{{p2, p6, p10, p13, p15}};
    const TPolygon f8{{p3, p7, p11, p13, p15}};
    const TPolygon f9{{p4, p5, p14, p18, p19}};
    const TPolygon f10{{p4, p6, p8, p10, p18}};
    const TPolygon f11{{p5, p7, p9, p11, p19}};
    const TPolygon f12{{p6, p7, p15, p18, p19}};

    for (const auto& face : {f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12}) {
        if ((face.getPoints().size() != 5) || !face.getAnglesIsEqual() || !face.getEdgesIsEqual() ||
            (face.getPoints()[0].distToPoint(face.getPoints()[1]) != edgeLength)) {
            throw std::runtime_error("Error: creating regular dodecahedron with broken face");
        }
    }

    const std::unordered_set<TPolygon> faces{f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12};
    if (faces.size() != 12) {
        throw std::runtime_error("Error: creating regular dodecahedron with != 12 faces");
    }

    return TPolyhedron{faces};
}
// TPolyhedron CreateRegularIcosahedron(const TPoint& center, TSafeDouble edgeLength) {}

} // namespace NRayTracingLib