#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TRay tests ===

TEST(TRay, CosineOfAngle_ComputesCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 2.0, 1.0};
    TRay ray{origin, x};
    TRay rayY{origin, y};
    EXPECT_EQ(ray.cos(rayY).Value, 5.0 / 7.0);
    EXPECT_EQ(rayY.cos(ray).Value, 5.0 / 7.0);
}

TEST(TRay, IsParallel_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{5.0, 10.0, 15.0};
    TRay rayX{origin, x};
    TRay rayY{origin, y};
    EXPECT_TRUE(rayX.isParallel(rayX));
    EXPECT_TRUE(rayX.isParallel(rayY));
    EXPECT_TRUE(rayY.isParallel(rayX));

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(TRay(origin, zeroVec), std::runtime_error);

    TVector w{6.0, 10.0, 15.0};
    TRay rayW{origin, w};
    EXPECT_FALSE(rayX.isParallel(rayW));
    EXPECT_FALSE(rayW.isParallel(rayX));

    TVector v{5.0 + TINY, 10.0 + TINY, 15.0 + TINY};
    TRay rayV{origin, v};
    EXPECT_TRUE(rayV.isParallel(rayY));
}

TEST(TRay, IsPerpendicular_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    TVector z{0.0, 0.0, 1.0};
    TRay rayX{origin, x};
    TRay rayY{origin, y};
    TRay rayZ{origin, z};
    EXPECT_TRUE(rayX.isPerpendicular(rayY));
    EXPECT_TRUE(rayX.isPerpendicular(rayZ));
    EXPECT_TRUE(rayY.isPerpendicular(rayX));
    EXPECT_TRUE(rayY.isPerpendicular(rayZ));
    EXPECT_TRUE(rayZ.isPerpendicular(rayX));
    EXPECT_TRUE(rayZ.isPerpendicular(rayY));

    TVector w{6.0, 10.0, 15.0};
    TRay rayW{origin, w};
    EXPECT_FALSE(rayX.isPerpendicular(rayW));
    EXPECT_FALSE(rayW.isPerpendicular(rayX));

    TVector v{0.0 + TINY, 1.0 + TINY, 0.0 + TINY};
    TRay rayV{origin, v};
    EXPECT_TRUE(rayV.isPerpendicular(rayX));
}

TEST(TRay, DistToPoint_ComputesCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TRay ray{origin, dir};

    EXPECT_EQ(ray.distToPoint(TPoint{1.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_EQ(ray.distToPoint(TPoint{0.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_EQ(ray.distToPoint(TPoint{10000.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_EQ(ray.distToPoint(TPoint{10000.0, 5.0, 0.0}).Value, 5.0);
    EXPECT_EQ(ray.distToPoint(TPoint{10000.0, 3.0, 4.0}).Value, 5.0);
}

TEST(TRay, ContainsPoint_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TRay ray{origin, dir};

    EXPECT_TRUE(ray.containsPoint(origin));
    EXPECT_TRUE(ray.containsPoint(TPoint{1.0, 0.0, 0.0}));
    EXPECT_FALSE(ray.containsPoint(TPoint{-1.0, 0.0, 0.0}));
    EXPECT_FALSE(ray.containsPoint(TPoint{0.0, 1.0, 0.0}));
    EXPECT_TRUE(ray.containsPoint(TPoint{TINY, 0.0, 0.0}));
    EXPECT_TRUE(ray.containsPoint(TPoint{-TINY, 0.0, 0.0}));
    EXPECT_FALSE(ray.containsPoint(TPoint{-NOT_TINY, 0.0, 0.0}));
}

TEST(TRay, EqualityOperators_WorkCorrectly) {
    TPoint p{0, 0, 0};
    TVector v{1, 0, 0};
    TRay ray1{p, v};
    TRay ray2{p + TVector{TINY, 0, 0}, v};

    EXPECT_TRUE(ray1 == ray2);
    EXPECT_FALSE(ray1 != ray2);
}

TEST(TRay, Intersection_ReturnsCorrectPointOrNullopt) {
    TPoint p1{0.0, 0.0, 0.0};
    TVector v1{1.0, 1.0, 1.0};
    TRay ray1{p1, v1};

    TPoint p2{1.0, 1.0, 1.0};
    TVector v2{1.0, 1.0, 1.0};

    EXPECT_EQ(ray1.intersection(TPlane{p2, v2}).value(), TPoint(1.0, 1.0, 1.0));

    TPoint p3{0.0, 0.0, 0.0};
    TVector v3{1.0, 1.0, 1.0};
    TRay ray3{p3, v3};

    TPoint p4{1.0, 0.0, 0.0};
    TVector v4{1.0, 1.0, 1.0};
    TRay ray4{p4, v4};

    EXPECT_EQ(ray3.intersection(TPlane{p4, v4}), TPoint(1.0 / 3.0, 1.0 / 3.0, 1.0 / 3.0));
}

TEST(TRay, CosineOfAngle_WithOppositeVectors) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector v1{1.0, 0.0, 0.0};
    TVector v2{-1.0, 0.0, 0.0};
    TRay ray1{origin, v1};
    TRay ray2{origin, v2};
    EXPECT_EQ(ray1.cos(ray2).Value, -1.0);
}

TEST(TRay, IsParallel_WithNearlyParallelVectors) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector v1{1.0, 1.0, 0.0};
    TVector v2{1.0 + TINY, 1.0 + TINY, 0.0};
    TRay ray1{origin, v1};
    TRay ray2{origin, v2};
    EXPECT_TRUE(ray1.isParallel(ray2));
}

TEST(TRay, IsPerpendicular_WithAlmostPerpendicularVectors) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector v1{1.0, 0.0, 0.0};
    TVector v2{TINY, 1.0, 0.0};
    TRay ray1{origin, v1};
    TRay ray2{origin, v2};
    EXPECT_TRUE(ray1.isPerpendicular(ray2));
}

TEST(TRay, DistToPoint_AlongDirection) {
    TPoint origin{1.0, 2.0, 3.0};
    TVector dir{0.0, 1.0, 0.0};
    TRay ray{origin, dir};
    EXPECT_EQ(ray.distToPoint(TPoint{1.0, 5.0, 3.0}).Value, 0.0);
}

TEST(TRay, DistToPoint_BehindOrigin) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TRay ray{origin, dir};
    EXPECT_EQ(ray.distToPoint(TPoint{-5.0, 0.0, 0.0}).Value, 5.0);
}

TEST(TRay, ContainsPoint_BeforeOrigin) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TRay ray{origin, dir};
    EXPECT_FALSE(ray.containsPoint(TPoint{-1.0, 0.0, 0.0}));
}

TEST(TRay, ContainsPoint_AfterOrigin) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TRay ray{origin, dir};
    EXPECT_TRUE(ray.containsPoint(TPoint{10.0, 0.0, 0.0}));
}

TEST(TRay, EqualityOperator_SameObject) {
    TPoint p{0, 0, 0};
    TVector v{1, 0, 0};
    TRay ray{p, v};
    EXPECT_TRUE(ray == ray);
}

TEST(TRay, EqualityOperator_DifferentObjects) {
    TPoint p1{0, 0, 0};
    TVector v1{1, 0, 0};
    TPoint p2{0, 0, 0};
    TVector v2{1, 0, 0};
    TRay ray1{p1, v1};
    TRay ray2{p2, v2};
    EXPECT_TRUE(ray1 == ray2);
}

TEST(TRay, InequalityOperator) {
    TPoint p1{0, 0, 0};
    TVector v1{1, 0, 0};
    TPoint p2{1, 0, 0};
    TVector v2{0, 1, 0};
    TRay ray1{p1, v1};
    TRay ray2{p2, v2};
    EXPECT_TRUE(ray1 != ray2);
}

TEST(TRay, Intersection_ParallelAndOutside) {
    TPoint p1{0.0, 0.0, 0.0};
    TVector v1{1.0, 0.0, 0.0};
    TRay ray{p1, v1};
    TPlane plane{TPoint{0, 1, 0}, TVector{0, 1, 0}};
    EXPECT_EQ(ray.intersection(plane), std::nullopt);
}

TEST(TRay, Intersection_PerpendicularAndOnPlane) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{0.0, 0.0, 1.0};
    TRay ray{p, v};
    TPlane plane{TPoint{0, 0, 1}, TVector{0, 0, 1}};
    EXPECT_EQ(ray.intersection(plane).value(), (TPoint{0, 0, 1}));
}

TEST(TRay, Intersection_WrongSide) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{0.0, 0.0, 1.0};
    TRay ray{p, v};
    TPlane plane{TPoint{0, 0, 1}, TVector{0, 0, 1}};
    auto result = ray.intersection(plane);
    EXPECT_EQ(result.value(), (TPoint{0, 0, 1}));
}

TEST(TRay, ContainsPoint_ExactlyAtOrigin) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{1.0, 0.0, 0.0};
    TRay ray{p, v};
    EXPECT_TRUE(ray.containsPoint(p));
}

TEST(TRay, ContainsPoint_AlongDirection) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{1.0, 0.0, 0.0};
    TRay ray{p, v};
    EXPECT_TRUE(ray.containsPoint(TPoint{5.0, 0.0, 0.0}));
}

TEST(TRay, ContainsPoint_BeforeOrigin2) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{1.0, 0.0, 0.0};
    TRay ray{p, v};
    EXPECT_FALSE(ray.containsPoint(TPoint{-1.0, 0.0, 0.0}));
}

TEST(TRay, DistToPoint_ExactlyOnOrigin) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{1.0, 0.0, 0.0};
    TRay ray{p, v};
    EXPECT_EQ(ray.distToPoint(p).Value, 0.0);
}

TEST(TRay, DistToPoint_VeryFarPoint) {
    TPoint p{0.0, 0.0, 0.0};
    TVector v{1.0, 0.0, 0.0};
    TRay ray{p, v};
    EXPECT_EQ(ray.distToPoint(TPoint{1e6, 1e6, 1e6}).Value, std::sqrt(1e6 * 1e6 + 1e6 * 1e6));
}
