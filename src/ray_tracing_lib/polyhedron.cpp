#include "polyhedron.h"

namespace NRayTracingLib {

TPolyhedron::TPolyhedron(const std::unordered_set<TPolygon>& polygons) : Faces_(polygons) {
    std::unordered_map<TEdge, uint8_t> edgesCount;

    for (const auto& face : Faces_) {
        for (size_t i = 0; i < face.getPoints().size(); i++) {
            const size_t nextIdx = (i + 1) % face.getPoints().size();
            const TEdge edge{face.getPoints()[i], face.getPoints()[nextIdx]};
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

TPolyhedron createRegularTetrahedron(const TPoint& center, TSafeDouble edgeLength) {
    if (edgeLength <= 0.0) {
        throw std::runtime_error("Error: trying to create regular tetrahedron with edge length <= 0");
    }

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

    return TPolyhedron{{f1, f2, f3, f4}};
}
TPolyhedron createRegularHexahedron(const TPoint& center, TSafeDouble edgeLength) {
    if (edgeLength <= 0.0) {
        throw std::runtime_error("Error: trying to create regular hexahedron with edge length <= 0");
    }

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

    return TPolyhedron{{f1, f2, f3, f4, f5, f6}};
}
TPolyhedron createRegularOctahedron(const TPoint& center, TSafeDouble edgeLength) {
    if (edgeLength <= 0.0) {
        throw std::runtime_error("Error: trying to create regular octahedron with edge length <= 0");
    }

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

    return TPolyhedron{{f1, f2, f3, f4, f5, f6, f7, f8}};
}
TPolyhedron createRegularDodecahedron(const TPoint& center, TSafeDouble edgeLength) {
    if (edgeLength <= 0.0) {
        throw std::runtime_error("Error: trying to create regular dodecahedron with edge length <= 0");
    }

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

    return TPolyhedron{{f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12}};
}
TPolyhedron createRegularIcosahedron(const TPoint& center, TSafeDouble edgeLength) {
    if (edgeLength <= 0.0) {
        throw std::runtime_error("Error: trying to create regular icosahedron with edge length <= 0");
    }

    const double phi = (1.0 + std::sqrt(5.0)) / 2.0;
    const double scale = edgeLength.Value / 2.0;

    const TPoint p0 = center + TVector{0.0, 1.0, phi} * scale;
    const TPoint p1 = center + TVector{0.0, 1.0, -phi} * scale;
    const TPoint p2 = center + TVector{0.0, -1.0, phi} * scale;
    const TPoint p3 = center + TVector{0.0, -1.0, -phi} * scale;
    const TPoint p4 = center + TVector{1.0, phi, 0.0} * scale;
    const TPoint p5 = center + TVector{-1.0, phi, 0.0} * scale;
    const TPoint p6 = center + TVector{1.0, -phi, 0.0} * scale;
    const TPoint p7 = center + TVector{-1.0, -phi, 0.0} * scale;
    const TPoint p8 = center + TVector{phi, 0.0, 1.0} * scale;
    const TPoint p9 = center + TVector{phi, 0.0, -1.0} * scale;
    const TPoint p10 = center + TVector{-phi, 0.0, 1.0} * scale;
    const TPoint p11 = center + TVector{-phi, 0.0, -1.0} * scale;

    const TPolygon f0{{p0, p2, p8}};
    const TPolygon f1{{p7, p10, p11}};
    const TPolygon f2{{p0, p2, p10}};
    const TPolygon f3{{p0, p4, p5}};
    const TPolygon f4{{p0, p4, p8}};
    const TPolygon f5{{p0, p5, p10}};
    const TPolygon f6{{p1, p3, p9}};
    const TPolygon f7{{p1, p3, p11}};
    const TPolygon f8{{p1, p4, p5}};
    const TPolygon f9{{p1, p4, p9}};
    const TPolygon f10{{p1, p5, p11}};
    const TPolygon f11{{p2, p6, p7}};
    const TPolygon f12{{p2, p6, p8}};
    const TPolygon f13{{p2, p7, p10}};
    const TPolygon f14{{p3, p6, p7}};
    const TPolygon f15{{p3, p6, p9}};
    const TPolygon f16{{p3, p7, p11}};
    const TPolygon f17{{p4, p8, p9}};
    const TPolygon f18{{p5, p10, p11}};
    const TPolygon f19{{p6, p8, p9}};

    return TPolyhedron{{f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, f10, f11, f12, f13, f14, f15, f16, f17, f18, f19}};
}

} // namespace NRayTracingLib