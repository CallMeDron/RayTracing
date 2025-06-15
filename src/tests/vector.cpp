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

TEST(TVector, ComplexAdditionAndSubtraction) {
    TVector a{1.0, -2.0, 3.0};
    TVector b{-4.0, 5.0, -6.0};
    TVector sum{-3.0, 3.0, -3.0};
    TVector diff{5.0, -7.0, 9.0};
    EXPECT_EQ(a + b, sum);
    EXPECT_EQ(a - b, diff);
}

TEST(TVector, ScalarMultiplicationAndDivisionWithNegative) {
    TVector a{1.0, -2.0, 3.0};
    TSafeDouble n{-2.0};
    TVector scaled{-2.0, 4.0, -6.0};
    EXPECT_EQ(a * n, scaled);
    EXPECT_EQ(scaled / n, a);
}

TEST(TVector, LengthOfZeroVectorIsZero) {
    TVector zeroVec;
    EXPECT_EQ(zeroVec.length().Value, 0.0);
}

TEST(TVector, NormalizationOfNonZeroVector) {
    TVector v{3.0, 4.0, 0.0};
    v.normalize();
    EXPECT_EQ(v.length().Value, 1.0);
    EXPECT_EQ(v, (TVector{0.6, 0.8, 0.0}));
}

TEST(TVector, GetNormalizedReturnsNormalizedVector) {
    TVector v{0.0, 0.0, 5.0};
    auto n = v.getNormalized();
    EXPECT_EQ(n, (TVector{0.0, 0.0, 1.0}));
}

TEST(TVector, GetNormalizedOnZeroVectorThrows) {
    TVector zeroVec;
    EXPECT_THROW(zeroVec.getNormalized(), std::runtime_error);
}

TEST(TVector, CosineOfParallelVectorsIsOne) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{2.0, 4.0, 6.0};
    EXPECT_EQ(a.cos(b).Value, 1.0);
}

TEST(TVector, CosineOfPerpendicularVectorsIsZero) {
    TVector a{1.0, 0.0, 0.0};
    TVector b{0.0, 1.0, 0.0};
    EXPECT_EQ(a.cos(b).Value, 0.0);
}

TEST(TVector, IsParallelDetectsParallelVectors) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{4.0, 8.0, 12.0};
    EXPECT_TRUE(a.isParallel(b));
    EXPECT_TRUE(b.isParallel(a));
    TVector c{1.0, 2.0, 3.01};
    EXPECT_FALSE(a.isParallel(c));
}

TEST(TVector, IsPerpendicularDetectsPerpendicularVectors) {
    TVector a{1.0, 0.0, 0.0};
    TVector b{0.0, 1.0, 0.0};
    EXPECT_TRUE(a.isPerpendicular(b));
    TVector c{1.0, 1.0, 0.0};
    EXPECT_FALSE(a.isPerpendicular(c));
}

TEST(TVector, ProjectionOfVectorOntoAnother) {
    TVector v{3.0, 4.0, 0.0};
    TVector u{1.0, 0.0, 0.0};
    auto proj = v.projectTo(u);
    EXPECT_EQ(proj, (TVector{3.0, 0.0, 0.0}));
    TVector zeroVec;
    EXPECT_EQ(zeroVec.projectTo(v), zeroVec);
    EXPECT_EQ(v.projectTo(zeroVec), zeroVec);
}

TEST(TVector, CrossProductWithOrthogonalVectors) {
    TVector a{1.0, 0.0, 0.0};
    TVector b{0.0, 1.0, 0.0};
    EXPECT_EQ(a ^ b, (TVector{0.0, 0.0, 1.0}));
    EXPECT_EQ(b ^ a, (TVector{0.0, 0.0, -1.0}));
}

TEST(TVector, CrossProductWithParallelVectorsIsZero) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{2.0, 4.0, 6.0};
    EXPECT_EQ(a ^ b, (TVector{0.0, 0.0, 0.0}));
}

TEST(TVector, IsZeroReturnsTrueForZeroVector) {
    TVector zeroVec;
    EXPECT_TRUE(zeroVec.isZero());
    TVector nonZero{1.0, 0.0, 0.0};
    EXPECT_FALSE(nonZero.isZero());
}

TEST(TVector, NormalizeZeroVectorThrows) {
    TVector zeroVec;
    EXPECT_THROW(zeroVec.normalize(), std::runtime_error);
}

TEST(TVector, LengthOfVectorWithNegativeCoordinates) {
    TVector v{-3.0, -4.0, 0.0};
    EXPECT_EQ(v.length().Value, 5.0);
}

TEST(TVector, SinOfAngleBetweenOrthogonalVectorsZero) {
    TVector a{1.0, 0.0, 0.0};
    TVector b{0.0, 1.0, 0.0};
    EXPECT_EQ(a.sin(b).Value, 1.0);
}

TEST(TVector, SinOfAngleBetweenParallelVectorsZero) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{2.0, 4.0, 6.0};
    EXPECT_EQ(a.sin(b).Value, 0.0);
}

TEST(TVector, GetNormalizedOfParallelVectorsEqualsOriginalNormalized) {
    TVector a{1.0, 2.0, 3.0};
    auto na1 = a.getNormalized();
    auto na2 = a.getNormalized();
    EXPECT_EQ(na1, na2);
}

TEST(TVector, MultipleOperationsChain) {
    TVector a{1.0, 2.0, 3.0};
    TVector b{4.0, 5.0, 6.0};
    auto c = ((a + b) * 2.0) - (b / 2.0);
    EXPECT_EQ(c, (TVector{(1 + 4) * 2 - 4 / 2.0, (2 + 5) * 2 - 5 / 2.0, (3 + 6) * 2 - 6 / 2.0}));
}

TEST(TVector, ProjectOntoSelfReturnsSameVector) {
    TVector a{1.0, 2.0, 3.0};
    EXPECT_EQ(a.projectTo(a), a);
}

TEST(TVector, ProjectOntoZeroVectorReturnsZero) {
    TVector zeroVec;
    TVector v{1.0, 2.0, 3.0};
    EXPECT_EQ(zeroVec.projectTo(v), zeroVec);
}

TEST(TVector, NormalizeAlreadyNormalizedVectorRemainsSame) {
    TVector a{0.6, 0.8, 0.0};
    auto norm = a.getNormalized();
    EXPECT_EQ(norm, a);
}

TEST(TVector, LengthOfVectorWithNegativeAndPositiveCoordinates) {
    TVector v{-3.0, 4.0, 12.0};
    EXPECT_EQ(v.length().Value, 13.0);
}

TEST(TVector, ScalarProductOfOrthogonalVectorsIsZero) {
    TVector a{1.0, 0.0, 0.0};
    TVector b{0.0, 1.0, 0.0};
    EXPECT_EQ(a * b, 0.0);
}

TEST(TVector, MultiplyByScalarAndDivideByScalarInverse) {
    TVector a{1.0, -2.0, 3.0};
    TSafeDouble scalar{4.0};
    auto scaled = a * scalar;
    auto divided = scaled / scalar;
    EXPECT_EQ(divided, a);
}

TEST(TVector, ProjectedVectors) {
    TVector vector{-1, -1, -1};
    TPlane plane{TPoint{1, 1, 1}, vector, TVector{0, 0, 1}};

    auto result = vector.projectedVectors(plane, TAngle{30});

    EXPECT_EQ(result.first + result.second, vector * 2);
    EXPECT_EQ(result.first.cos(vector), sqrt(3.0) / 2.0);
    EXPECT_EQ(result.second.cos(vector), sqrt(3.0) / 2.0);
    EXPECT_TRUE(plane.isParallel(result.first));
    EXPECT_TRUE(plane.isParallel(result.second));
    EXPECT_EQ(result.first.projectTo(vector), vector);
    EXPECT_EQ(result.second.projectTo(vector), vector);
}

TEST(TVector, ProjectedVectors2) {
    TVector vector{1, 2, 3};
    TPlane plane{TPoint{0, 0, 0}, vector, TVector{1, -1, 0}};

    auto result = vector.projectedVectors(plane, TAngle{60});

    EXPECT_EQ(result.first + result.second, vector * 2);
    EXPECT_EQ(result.first.cos(vector), 0.5);
    EXPECT_EQ(result.second.cos(vector), 0.5);
    EXPECT_TRUE(plane.isParallel(result.first));
    EXPECT_TRUE(plane.isParallel(result.second));
    EXPECT_EQ(result.first.projectTo(vector), vector);
    EXPECT_EQ(result.second.projectTo(vector), vector);
}