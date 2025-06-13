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
    EXPECT_DOUBLE_EQ(ray.cos(rayY).Value, 5.0 / 7.0);
    EXPECT_DOUBLE_EQ(rayY.cos(ray).Value, 5.0 / 7.0);
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

    EXPECT_DOUBLE_EQ(ray.distToPoint(TPoint{1.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(ray.distToPoint(TPoint{0.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(ray.distToPoint(TPoint{10000.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(ray.distToPoint(TPoint{10000.0, 5.0, 0.0}).Value, 5.0);
    EXPECT_DOUBLE_EQ(ray.distToPoint(TPoint{10000.0, 3.0, 4.0}).Value, 5.0);
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
    EXPECT_FALSE(ray.containsPoint(TPoint{-TINY, 0.0, 0.0}));
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

    TPoint p2{1.0, 0.0, 0.0};
    TVector v2{0.0, 1.0, 1.0};
    TRay ray2{p2, v2};

    EXPECT_EQ(ray1.intersection(TPlane{p1, v1}).value(), TPoint(1.0, 1.0, 1.0));

    TPoint p3{0.0, 0.0, 0.0};
    TVector v3{1.0, 1.0, 1.0};
    TRay ray3{p3, v3};

    TPoint p4{1.0, 0.0, 0.0};
    TVector v4{1.0, 1.0, 1.0};
    TRay ray4{p4, v4};

    EXPECT_EQ(ray3.intersection(TPlane{p4, v4}), std::nullopt);
}
