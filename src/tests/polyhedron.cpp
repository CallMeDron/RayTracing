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
    auto intersection = poly.intersection(line);
    ASSERT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection->X, 0.5);
    EXPECT_EQ(intersection->Y, 0.5);
    EXPECT_EQ(intersection->Z, 0);
}

TEST(TPolyhedron, NoIntersection) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(2, 2, 2), TPoint(3, 3, 3));
    EXPECT_EQ(poly.intersection(line).value(), TPoint(1, 1, 1));
}

TEST(TPolyhedron, TangentLine) {
    TPolyhedron poly(FACES);
    TLine line(TPoint(0.5, 0.5, -1), TPoint(0.5, 0.5, 0));
    auto intersection = poly.intersection(line);
    EXPECT_TRUE(intersection.has_value());
    EXPECT_EQ(intersection->Z, 0);
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