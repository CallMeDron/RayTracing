#include "..\ray_tracing_lib\all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

const double TINY = ACCURACY / 2.0;
const double NOT_TINY = ACCURACY * 2.0;

//=== TLine tests ===

TEST(TLine, CosineOfAngle_ComputesCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{3.0, 2.0, 1.0};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    EXPECT_DOUBLE_EQ(lineX.cos(lineY).Value, 5.0 / 7.0);
    EXPECT_DOUBLE_EQ(lineY.cos(lineX).Value, 5.0 / 7.0);
}

TEST(TLine, IsParallel_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 2.0, 3.0};
    TVector y{5.0, 10.0, 15.0};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    EXPECT_TRUE(lineX.isParallel(lineX));
    EXPECT_TRUE(lineX.isParallel(lineY));
    EXPECT_TRUE(lineY.isParallel(lineX));

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(TLine(origin, zeroVec), std::runtime_error);

    TVector w{6.0, 10.0, 15.0};
    TLine lineW{origin, w};
    EXPECT_FALSE(lineX.isParallel(lineW));
    EXPECT_FALSE(lineW.isParallel(lineX));

    TVector v{5.0 + TINY, 10.0 + TINY, 15.0 + TINY};
    TLine lineV{origin, v};
    EXPECT_TRUE(lineV.isParallel(lineY));
}

TEST(TLine, IsPerpendicular_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    TVector z{0.0, 0.0, 1.0};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    TLine lineZ{origin, z};
    EXPECT_TRUE(lineX.isPerpendicular(lineY));
    EXPECT_TRUE(lineX.isPerpendicular(lineZ));
    EXPECT_TRUE(lineY.isPerpendicular(lineX));
    EXPECT_TRUE(lineY.isPerpendicular(lineZ));
    EXPECT_TRUE(lineZ.isPerpendicular(lineX));
    EXPECT_TRUE(lineZ.isPerpendicular(lineY));

    TVector w{6.0, 10.0, 15.0};
    TLine lineW{origin, w};
    EXPECT_FALSE(lineX.isPerpendicular(lineW));
    EXPECT_FALSE(lineW.isPerpendicular(lineX));

    TVector v{0.0 + TINY, 1.0 + TINY, 0.0 + TINY};
    TLine lineV{origin, v};
    EXPECT_TRUE(lineV.isPerpendicular(lineX));
}

TEST(TLine, DistToPoint_ComputesCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TLine line{origin, dir};

    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{1.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{0.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{10000.0, 0.0, 0.0}).Value, 0.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{10000.0, 5.0, 0.0}).Value, 5.0);
    EXPECT_DOUBLE_EQ(line.distToPoint(TPoint{10000.0, 3.0, 4.0}).Value, 5.0);
}

TEST(TLine, ContainsPoint_ReturnsCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector dir{1.0, 0.0, 0.0};
    TLine line{origin, dir};

    EXPECT_TRUE(line.containsPoint(origin));
    EXPECT_TRUE(line.containsPoint(TPoint{1.0, 0.0, 0.0}));
    EXPECT_FALSE(line.containsPoint(TPoint{1.0 + NOT_TINY, -NOT_TINY, -NOT_TINY}));
    EXPECT_TRUE(line.containsPoint(TPoint{1.0 + TINY, -TINY, -TINY}));
}

TEST(TLine, EqualityOperators_WorkCorrectly) {
    TPoint origin{0.0, 0.0, 0.0};
    TVector x{1.0, 0.0, 0.0};
    TVector y{1.0 + 0.01, -0.01, -0.01};
    TVector z{1.0 + TINY, -TINY, -TINY};
    TLine lineX{origin, x};
    TLine lineY{origin, y};
    TLine lineZ{origin, z};

    EXPECT_EQ(lineX, lineZ);
    EXPECT_EQ(lineZ, lineX);
    EXPECT_NE(lineX, lineY);
    EXPECT_NE(lineY, lineX);
    EXPECT_NE(lineY, lineZ);
    EXPECT_NE(lineZ, lineY);
}

TEST(TLine, Intersection_ReturnsCorrectPointOrThrows) {
    TPoint p1{0.0, 0.0, 0.0};
    TVector v1{1.0, 1.0, 1.0};
    TLine l1{p1, v1};

    TPoint p2{1.0, 0.0, 0.0};
    TVector v2{0.0, 1.0, 1.0};
    TLine l2{p2, v2};

    EXPECT_EQ(l1.intersection(l2), TPoint(1.0, 1.0, 1.0));

    TPoint p3{0.0, 0.0, 0.0};
    TVector v3{1.0, 1.0, 1.0};
    TLine l3{p3, v3};

    TPoint p4{1.0, 0.0, 0.0};
    TVector v4{1.0, 1.0, 1.0};
    TLine l4{p4, v4};

    EXPECT_EQ(l3.intersection(l4), std::nullopt);

    TPoint p5{0.0, 0.0, 0.0};
    TVector v5{1.0, 1.0, 1.0};
    TLine l5{p5, v5};

    TPoint p6{1.0, 1.0, 1.0};
    TVector v6{1.0, 1.0, 1.0};
    TLine l6{p6, v6};

    EXPECT_THROW(l5.intersection(l6), std::runtime_error);

    TPoint p7{1.0, 2.0, 3.0};
    TVector v7{-1.0, -2.0, -3.0};
    TLine l7{p7, v7};

    TPoint p8{13.0, -4.0, 5.0};
    TVector v8{-13.0, 4.0, -5.0};
    TLine l8{p8, v8};

    EXPECT_EQ(l7.intersection(l8), TPoint(0.0, 0.0, 0.0));
}

TEST(TLine, ParallelLines_NoIntersection) {
    TPoint p{0, 0, 0};
    TVector v{1, 0, 0};
    TLine line1{p, v};
    TLine line2{p + TVector{0, 1, 0}, v};

    EXPECT_EQ(line1.intersection(line2), std::nullopt);
}

TEST(TLine, CoplanarNonIntersectingLines) {
    TPoint p1{0, 0, 0};
    TPoint p2{0, 1, 0};
    TVector v1{1, 1, 0};
    TVector v2{1, 1, 0};
    TLine line1{p1, v1};
    TLine line2{p2, v2};

    EXPECT_EQ(line1.intersection(line2), std::nullopt);
}

TEST(TLine, DistToPoint_ClosePoints) {
    TPoint p{0, 0, 0};
    TVector v{1, 0, 0};
    TLine line{p, v};

    TPoint closePoint{0, TINY, 0};
    EXPECT_NEAR(line.distToPoint(closePoint).Value, TINY, ACCURACY);
}

TEST(TLine, Equality_CloseLines) {
    TPoint p{0, 0, 0};
    TVector v{1, 0, 0};
    TLine line1{p, v};
    TLine line2{p + TVector{TINY, 0, 0}, v};

    EXPECT_TRUE(line1 == line2);
}