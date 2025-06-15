#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TPolyhedron Tests ===

static const TPoint p000(0, 0, 0);
static const TPoint p100(1, 0, 0);
static const TPoint p110(1, 1, 0);
static const TPoint p010(0, 1, 0);
static const TPoint p001(0, 0, 1);
static const TPoint p101(1, 0, 1);
static const TPoint p111(1, 1, 1);
static const TPoint p011(0, 1, 1);
static const TPoint p120(1, 2, 0);
static const TPoint p020(0, 2, 0);
static const TPoint p021(0, 2, 1);
static const TPoint p121(1, 2, 1);

static const std::unordered_set FACES{TPolygon{{p000, p100, p110, p010}}, TPolygon{{p001, p101, p111, p011}},
                                      TPolygon{{p000, p100, p101, p001}}, TPolygon{{p010, p110, p111, p011}},
                                      TPolygon{{p000, p010, p011, p001}}, TPolygon{{p100, p110, p111, p101}}};

TEST(TPolyhedron, CreationAndFaceCount) {
    TPolyhedron poly(FACES);
    EXPECT_EQ(poly.getFaces().size(), FACES.size());
}

TEST(TPolyhedron, IntersectionThroughCenter) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(0.5, 0.5, -1), TPoint(0.5, 0.5, 2));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    ASSERT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.X, 0.5);
    EXPECT_EQ(intersection.value().first.Y, 0.5);
    EXPECT_EQ(intersection.value().first.Z, 0);
}

TEST(TPolyhedron, NoIntersection) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(2, 2, 2), TPoint(3, 3, 3));
    EXPECT_EQ(poly.intersection(line).value().first, TPoint(1, 1, 1));
}

TEST(TPolyhedron, TangentLine) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(0.5, 0.5, -1), TPoint(0.5, 0.5, 0));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.Z, 0);
}

TEST(TPolyhedron, NotClosedPolyhedronThrows) {
    std::unordered_set<TPolygon> invalid_faces = {TPolygon{{p000, p100, p110, p010}}};
    EXPECT_THROW(TPolyhedron polyhedron(invalid_faces), std::runtime_error);
}

TEST(TPolyhedron, IntersectionAtVertex) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(0, 0, -1), TPoint(0, 0, 1));
    EXPECT_THROW(poly.intersection(line), std::runtime_error);
}

TEST(TPolyhedron, ParallelLineNoIntersection) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(2, 1.5, 1.5), TPoint(3, 1.5, 1.5));
    EXPECT_FALSE(poly.intersection(line).has_value());
}

TEST(TPolyhedron, LineAlongFace) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(0, 0.5, 0), TPoint(1, 0.5, 0));
    EXPECT_THROW(poly.intersection(line), std::runtime_error);
}

TEST(TPolyhedron, IntersectionThroughComplexObliquePyramid) {
    std::unordered_set<TPolygon> faces = {TPolygon{{p000, p100, p110, p010}}, TPolygon{{p000, p100, p101, p001}},
                                          TPolygon{{p100, p110, p111, p101}}, TPolygon{{p010, p110, p111, p011}},
                                          TPolygon{{p000, p010, p011, p001}}, TPolygon{{p001, p101, p111, p011}}};
    TPolyhedron poly(faces);
    TLine line(TPoint(0.5, 0.5, -1), TPoint(0.5, 0.5, 2));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.X, 0.5);
    EXPECT_EQ(intersection.value().first.Y, 0.5);
    EXPECT_EQ(intersection.value().first.Z, 0);
}

TEST(TPolyhedron, IntersectionWithDiagonalTiltedBox) {
    std::unordered_set<TPolygon> faces = {TPolygon{{p000, p100, p110, p010}}, TPolygon{{p001, p101, p111, p011}},
                                          TPolygon{{p000, p100, p101, p001}}, TPolygon{{p010, p110, p111, p011}},
                                          TPolygon{{p000, p010, p011, p001}}, TPolygon{{p100, p110, p111, p101}}};
    TPolyhedron poly(faces);
    TLine line(TPoint(0.2, 0.3, -1), TPoint(0.8, 0.7, 3));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.X, 0.35);
    EXPECT_EQ(intersection.value().first.Y, 0.4);
    EXPECT_EQ(intersection.value().first.Z, 0);
}

TEST(TPolyhedron, IntersectionWithTiltedParallelepiped) {
    std::unordered_set<TPolygon> faces = {TPolygon{{p000, p100, p120, p020}}, TPolygon{{p001, p101, p121, p021}},
                                          TPolygon{{p000, p100, p101, p001}}, TPolygon{{p020, p120, p121, p021}},
                                          TPolygon{{p000, p020, p021, p001}}, TPolygon{{p100, p120, p121, p101}}};
    TPolyhedron poly(faces);
    TLine line(TPoint(0.3, 0.4, -1), TPoint(0.7, 0.6, 2));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.X, 0.4333333333);
    EXPECT_EQ(intersection.value().first.Y, 0.4666666667);
    EXPECT_EQ(intersection.value().first.Z, 0);
}

TEST(TPolyhedron, NoIntersectionWithObliqueTiltedShape) {
    std::unordered_set<TPolygon> faces = {TPolygon{{p000, p100, p110, p010}}, TPolygon{{p001, p101, p111, p011}},
                                          TPolygon{{p000, p100, p101, p001}}, TPolygon{{p010, p110, p111, p011}},
                                          TPolygon{{p000, p010, p011, p001}}, TPolygon{{p100, p110, p111, p101}}};
    TPolyhedron poly(faces);
    TLine line(TPoint(2, 2, -1), TPoint(3, 3, 1));
    EXPECT_FALSE(poly.intersection(line).has_value());
}

TEST(TPolyhedron, IntersectionAlongDiagonalEdge) {
    std::unordered_set<TPolygon> faces = {TPolygon{{p000, p100, p110, p010}}, TPolygon{{p001, p101, p111, p011}},
                                          TPolygon{{p000, p100, p101, p001}}, TPolygon{{p010, p110, p111, p011}},
                                          TPolygon{{p000, p010, p011, p001}}, TPolygon{{p100, p110, p111, p101}}};
    TPolyhedron poly(faces);
    TLine line(TPoint(0, 0, -1), TPoint(1, 1, 1));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.X, 0.5);
    EXPECT_EQ(intersection.value().first.Y, 0.5);
    EXPECT_EQ(intersection.value().first.Z, 0.0);
}

TEST(TPolyhedron, IntersectionFromInsidePoint) {
    std::unordered_set<TPolygon> faces = {TPolygon{{p000, p100, p110, p010}}, TPolygon{{p001, p101, p111, p011}},
                                          TPolygon{{p000, p100, p101, p001}}, TPolygon{{p010, p110, p111, p011}},
                                          TPolygon{{p000, p010, p011, p001}}, TPolygon{{p100, p110, p111, p101}}};
    TPolyhedron poly(faces);
    TLine line(TPoint(0.5, 0.5, 0.5), TPoint(0.5, 0.5, 2));
    std::optional<std::pair<TPoint, TPointContainment>> intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection.value().first.X, 0.5);
    EXPECT_EQ(intersection.value().first.Y, 0.5);
    EXPECT_EQ(intersection.value().first.Z, 0);
}

TEST(TPolyhedron, CreateRegularTetrahedron) {
    const TPolyhedron tetrahedron = createRegularTetrahedron(TPoint{1, 2, 3}, 1.0);

    EXPECT_EQ(tetrahedron.getFaces().size(), 4u);

    for (const auto& face : tetrahedron.getFaces()) {
        EXPECT_EQ(face.getPoints().size(), 3u);
        EXPECT_TRUE(face.getAnglesIsEqual());
        EXPECT_TRUE(face.getEdgesIsEqual());
        EXPECT_EQ(face.getPoints()[0].distToPoint(face.getPoints()[1]), 1.0);
    }
}

TEST(TPolyhedron, CreateRegularHexahedron) {
    const TPolyhedron hexahedron = createRegularHexahedron(TPoint{100, 200, 300}, 2.0);

    EXPECT_EQ(hexahedron.getFaces().size(), 6u);

    for (const auto& face : hexahedron.getFaces()) {
        EXPECT_EQ(face.getPoints().size(), 4u);
        EXPECT_TRUE(face.getAnglesIsEqual());
        EXPECT_TRUE(face.getEdgesIsEqual());
        EXPECT_EQ(face.getPoints()[0].distToPoint(face.getPoints()[1]), 2.0);
    }
}

TEST(TPolyhedron, CreateRegularOctahedron) {
    const TPolyhedron octahedron = createRegularOctahedron(TPoint(), 4.0);

    EXPECT_EQ(octahedron.getFaces().size(), 8u);

    for (const auto& face : octahedron.getFaces()) {
        EXPECT_EQ(face.getPoints().size(), 3u);
        EXPECT_TRUE(face.getAnglesIsEqual());
        EXPECT_TRUE(face.getEdgesIsEqual());
        EXPECT_EQ(face.getPoints()[0].distToPoint(face.getPoints()[1]), 4.0);
    }
}

TEST(TPolyhedron, CreateRegularDodecahedron) {
    const TPolyhedron dodecahedron = createRegularDodecahedron(TPoint{-1, 2, -3.2}, 8.0);

    EXPECT_EQ(dodecahedron.getFaces().size(), 12u);

    for (const auto& face : dodecahedron.getFaces()) {
        EXPECT_EQ(face.getPoints().size(), 5u);
        EXPECT_TRUE(face.getAnglesIsEqual());
        EXPECT_TRUE(face.getEdgesIsEqual());
        EXPECT_EQ(face.getPoints()[0].distToPoint(face.getPoints()[1]), 8.0);
    }
}

TEST(TPolyhedron, CreateRegularIcosahedron) {
    const TPolyhedron icosahedron = createRegularIcosahedron(TPoint(), 16.0);

    EXPECT_EQ(icosahedron.getFaces().size(), 20u);

    for (const auto& face : icosahedron.getFaces()) {
        EXPECT_EQ(face.getPoints().size(), 3u);
        EXPECT_TRUE(face.getAnglesIsEqual());
        EXPECT_TRUE(face.getEdgesIsEqual());
        EXPECT_EQ(face.getPoints()[0].distToPoint(face.getPoints()[1]), 16.0);
    }
}
