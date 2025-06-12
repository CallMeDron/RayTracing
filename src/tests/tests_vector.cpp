#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TVector tests ===

TEST(TVector, Constructor_FromPointAndCoordinates_WorksCorrectly) {
    TPoint p{1.0, 2.0, 3.0};
    TVector fromPoint{p};
    TVector fromCoords{1.0, 2.0, 3.0};
    EXPECT_EQ(fromPoint, fromCoords);

    TPoint a{1.0, 2.0, 3.0};
    TPoint b{2.0, 3.0, 4.0};
    TVector diff{1.0, 1.0, 1.0};
    EXPECT_EQ(TVector(a, b), diff);
}

TEST(TVector, AdditionAndSubtraction_WorksCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{4.0, 3.0, 2.0};
    TVector sum{5.0, 5.0, 5.0};
    TVector diff{-3.0, -1.0, 1.0};
    EXPECT_EQ(a + b, sum);
    EXPECT_EQ(a - b, diff);
}

TEST(TVector, MultiplicationAndDivision_ByScalar_WorksCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 6.0, 9.0};
    EXPECT_EQ(a * 3.0, b);
    EXPECT_EQ(b / 3.0, a);
    EXPECT_THROW(b / TINY, std::runtime_error);
}

TEST(TVector, ScalarProduct_ComputesCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 6.0, 9.0};
    EXPECT_EQ(a * b, 42.0);
}

TEST(TVector, VectorProduct_ComputesCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 2.0, 1.0};
    TVector expected{-4.0, 8.0, -4.0};
    EXPECT_EQ(a ^ b, expected);
}

TEST(TVector, Length_ComputesCorrectly) {
    TVector v{0.0, 3.0, 4.0};
    EXPECT_EQ(v.length(), 5.0);
}

TEST(TVector, Normalization_WorksCorrectly) {
    TVector v{0.0, 3.0, 4.0};
    v.normalize();
    TVector expected{0.0, 0.6, 0.8};
    EXPECT_EQ(v, expected);

    TVector v2{0.0, 3.0, 4.0};
    EXPECT_EQ(v2.getNormalized(), expected);

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(zeroVec.getNormalized(), std::runtime_error);
}

TEST(TVector, CosineOfAngle_ComputesCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{3.0, 2.0, 1.0};
    EXPECT_DOUBLE_EQ(a.cos(b).Value, 5.0 / 7.0);
    EXPECT_DOUBLE_EQ(b.cos(a).Value, 5.0 / 7.0);
}

TEST(TVector, IsParallel_ReturnsCorrectly) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{5.0, 10.0, 15.0};
    EXPECT_TRUE(a.isParallel(a));
    EXPECT_TRUE(a.isParallel(-a));
    EXPECT_TRUE(a.isParallel(b));
    EXPECT_TRUE(b.isParallel(a));

    TVector zeroVec{0.0, 0.0, 0.0};
    EXPECT_THROW(zeroVec.isParallel(zeroVec), std::runtime_error);

    TVector c{6.0, 10.0, 15.0};
    EXPECT_FALSE(a.isParallel(c));
    EXPECT_FALSE(c.isParallel(a));

    TVector d{5.0 + TINY, 10.0 + TINY, 15.0 + TINY};
    EXPECT_TRUE(d.isParallel(b));
}

TEST(TVector, IsPerpendicular_ReturnsCorrectly) {
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    TVector z{0.0, 0.0, 1.0};
    EXPECT_TRUE(x.isPerpendicular(y));
    EXPECT_TRUE(x.isPerpendicular(z));
    EXPECT_TRUE(y.isPerpendicular(x));
    EXPECT_TRUE(y.isPerpendicular(z));
    EXPECT_TRUE(z.isPerpendicular(x));
    EXPECT_TRUE(z.isPerpendicular(y));

    TVector w{6.0, 10.0, 15.0};
    EXPECT_FALSE(x.isPerpendicular(w));
    EXPECT_FALSE(w.isPerpendicular(x));

    TVector v{0.0 + TINY, 1.0 + TINY, 0.0 + TINY};
    EXPECT_TRUE(v.isPerpendicular(x));
}

TEST(TVector, Projection_ReturnsCorrectProjection) {
    TVector x{1.0, 0.0, 0.0};
    TVector y{0.0, 1.0, 0.0};
    EXPECT_EQ(x.projectTo(x), x);
    EXPECT_TRUE(x.projectTo(y).isZero());

    TVector v{1.0, 2.0, 3.0};
    TVector w{-3.0, 2.0, 7.0};
    TVector expected{-33.0 / 31.0, 22.0 / 31.0, 77.0 / 31.0};
    EXPECT_EQ(v.projectTo(w), expected);
}

TEST(TVector, DivisionByVerySmallScalar_ShouldThrow) {
    TVector a{1.0, 2.0, 3.0};
    EXPECT_THROW(a / TINY, std::runtime_error);
}

TEST(TVector, DotProductWithZeroVector_ShouldBeZero) {
    TVector zeroVec{0.0, 0.0, 0.0};
    TVector v{1.0, 2.0, 3.0};
    EXPECT_EQ(zeroVec * v, 0);
    EXPECT_EQ(v * zeroVec, 0);
}

TEST(TVector, CrossProductWithZeroVector_ShouldBeZero) {
    TVector zeroVec{0.0, 0.0, 0.0};
    TVector v{1.0, 2.0, 3.0};
    EXPECT_EQ(zeroVec ^ v, (TVector{0.0, 0.0, 0.0}));
    EXPECT_EQ(v ^ zeroVec, (TVector{0.0, 0.0, 0.0}));
}

TEST(TVector, IsPerpendicularWithZeroVector_ShouldThrow) {
    TVector zeroVec{0.0, 0.0, 0.0};
    TVector a{1.0, 2.0, 3.0};
    EXPECT_THROW(zeroVec.isPerpendicular(a), std::runtime_error);
}

TEST(TVector, ProjectionOntoZeroVector_ShouldBeZero) {
    TVector zeroVec{0.0, 0.0, 0.0};
    TVector v{1.0, 2.0, 3.0};
    EXPECT_TRUE(zeroVec.projectTo(v).isZero());
    EXPECT_TRUE(v.projectTo(zeroVec).isZero());
}