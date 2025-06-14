#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TPolygon Tests ===

TEST(TPolygon, InitializationFailsWithLessThanThreePoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, ValidTriangle) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 3u);
}

TEST(TPolygon, ValidRectangle) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(1, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 4u);
}

TEST(TPolygon, CheckPlanarityFail) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(0, 0, 1)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, SortByPolarAngleWorksCorrectly) {
    std::unordered_set<TPoint> points = {TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(-1, 0, 0), TPoint(0, -1, 0)};
    TPolygon p(points);

    std::vector<std::vector<TPoint>> expectedVariants;
    expectedVariants.push_back({TPoint(-1, 0, 0), TPoint(0, 1, 0), TPoint(1, 0, 0), TPoint(0, -1, 0)});
    expectedVariants.push_back({TPoint(0, -1, 0), TPoint(-1, 0, 0), TPoint(0, 1, 0), TPoint(1, 0, 0)});
    expectedVariants.push_back({TPoint(1, 0, 0), TPoint(0, -1, 0), TPoint(-1, 0, 0), TPoint(0, 1, 0)});
    expectedVariants.push_back({TPoint(0, 1, 0), TPoint(1, 0, 0), TPoint(0, -1, 0), TPoint(-1, 0, 0)});
    expectedVariants.push_back({TPoint(-1, 0, 0), TPoint(0, -1, 0), TPoint(1, 0, 0), TPoint(0, 1, 0)});
    expectedVariants.push_back({TPoint(0, -1, 0), TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(-1, 0, 0)});
    expectedVariants.push_back({TPoint(1, 0, 0), TPoint(0, 1, 0), TPoint(-1, 0, 0), TPoint(0, -1, 0)});
    expectedVariants.push_back({TPoint(0, 1, 0), TPoint(-1, 0, 0), TPoint(0, -1, 0), TPoint(1, 0, 0)});

    bool condition = false;
    for (const auto& expected : expectedVariants) {
        condition |= (p.getPoints() == expected);
    }

    EXPECT_TRUE(condition);
}

TEST(TPolygon, RemoveExtraPointsRemovesCollinearPoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0), TPoint(0, 1, 0)};
    TPolygon p(points);
    EXPECT_EQ(p.getPoints().size(), 3u);
    for (const auto& point : p.getPoints()) {
        EXPECT_NE(point, TPoint(1, 1, 0));
    }
}

TEST(TPolygon, NonConvexPolygonThrows) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(2, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0),
                                         TPoint(0, 2, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, PointsOnLineThrows) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 1, 0), TPoint(2, 2, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

TEST(TPolygon, FullCreationProcess) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(1, 1, 0), TPoint(0, 1, 0),
                                         TPoint(0.5, 0.5, 0)};
    EXPECT_THROW(TPolygon p(points), std::runtime_error);
}

void ExpectOptionalPointsEqual(const std::optional<TPoint>& expected, const std::optional<TPoint>& actual) {
    if (!expected.has_value() && !actual.has_value()) {
        SUCCEED();
    } else if (expected.has_value() && actual.has_value()) {
        EXPECT_EQ(expected.value(), actual.value());
    } else {
        FAIL() << "One of the optionals is null, the other is not.";
    }
}

TPolygon CreateSquare() {
    std::unordered_set<TPoint> pts = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(1, 1, 0), TPoint(0, 1, 0)};
    TPolygon square = TPolygon(pts);
    EXPECT_TRUE(square.getPoints().size() == 4u);
    EXPECT_TRUE(square.getEdgesIsEqual());
    EXPECT_TRUE(square.getAnglesIsEqual());
    return square;
}

TEST(TPolygon, ContainsPointInside) {
    TPolygon square = CreateSquare();
    TPoint insidePoint(0.5, 0.5, 0);
    EXPECT_TRUE(square.containsPoint(insidePoint));
}

TEST(TPolygon, ContainsPointOnEdge) {
    TPolygon square = CreateSquare();
    TPoint onEdge(1, 0.5, 0);
    EXPECT_TRUE(square.containsPoint(onEdge));
}

TEST(TPolygon, ContainsPointOnVertex) {
    TPolygon square = CreateSquare();
    TPoint vertex(0, 0, 0);
    EXPECT_TRUE(square.containsPoint(vertex));
}

TEST(TPolygon, ContainsPointOutside) {
    TPolygon square = CreateSquare();
    TPoint outsidePoint(2, 2, 0);
    EXPECT_FALSE(square.containsPoint(outsidePoint));
}

TEST(TPolygon, ContainsPointOnPlaneButOutsidePolygon) {
    TPolygon square = CreateSquare();
    TPoint outsideOnPlane(1.5, 0.5, 0);
    EXPECT_FALSE(square.containsPoint(outsideOnPlane));
}

TEST(TPolygon, IntersectionInsidePolygon) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(0.5, 0.5, -1), TPoint(0.5, 0.5, 1));
    auto result = square.intersection(line);
    ExpectOptionalPointsEqual(TPoint(0.5, 0.5, 0), result);
}

TEST(TPolygon, IntersectionOutsidePolygon) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(2, 2, -1), TPoint(2, 2, 1));
    auto result = square.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(TPolygon, IntersectionLineMissesPlane) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(0, 0, 1), TPoint(1, 1, 1));
    auto result = square.intersection(line);
    EXPECT_FALSE(result.has_value());
}

TEST(TPolygon, IntersectionLineTangentToPolygonEdge) {
    TPolygon square = CreateSquare();
    TLine line(TPoint(0, 0.5, 0), TPoint(1, 0.5, 0));
    EXPECT_THROW(square.intersection(line), std::runtime_error);
}

TEST(TPolygon, ValidRectangleXYPlane) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(4, 0, 0), TPoint(4, 3, 0), TPoint(0, 3, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_TRUE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, ValidRectangle3DOrientation) {
    std::unordered_set<TPoint> points = {TPoint(1, 1, 1), TPoint(5, 1, 1), TPoint(5, 4, 1), TPoint(1, 4, 1)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_TRUE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, InvalidNotFourPoints) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(1, 0, 0), TPoint(1, 1, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 3u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_FALSE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, NotAllAnglesRight) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(4, 0, 0), TPoint(4, 3, 0), TPoint(2, 2, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_FALSE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, NonPerpendicularAngles) {
    std::unordered_set<TPoint> points = {TPoint(0, 0, 0), TPoint(4, 0, 0), TPoint(4, 3, 0), TPoint(0, 3.5, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_FALSE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, ObliqueRectangleIn3D) {
    auto points = std::unordered_set<TPoint>{TPoint(0, 0, 0), TPoint(4, 0, 3), TPoint(4, 3, 3), TPoint(0, 3, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_TRUE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, SlightNumericalDeviation) {
    auto points = std::unordered_set<TPoint>{TPoint(0, 0, 0), TPoint(4, 0, 0), TPoint(4, 3, 0), TPoint(0, 3 + TINY, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_TRUE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, ObliqueRectangleWithDiagonalSides) {
    auto points = std::unordered_set<TPoint>{TPoint(0, 0, 0), TPoint(4, 1, 0), TPoint(4, 4, 0), TPoint(0, 3, 0)};
    TPolygon polygon(points);
    EXPECT_TRUE(polygon.getPoints().size() == 4u);
    EXPECT_FALSE(polygon.getEdgesIsEqual());
    EXPECT_FALSE(polygon.getAnglesIsEqual());
}

TEST(TPolygon, EqualSameOrder) {
    TPolygon poly1{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    TPolygon poly2{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    EXPECT_TRUE(poly1 == poly2);
}

TEST(TPolygon, EqualDifferentOrder) {
    TPolygon poly1{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    TPolygon poly2{{TPoint{0, 0, 1}, TPoint{0, 0, 0}, TPoint{0, 1, 0}}};
    EXPECT_TRUE(poly1 == poly2);
}

TEST(TPolygon, DifferentNumberOfPoints) {
    TPolygon poly1{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{1, 1, 0}}};
    TPolygon poly2{{TPoint{-1, 0, 0}, TPoint{1, 0, 0}, TPoint{0, 1, 0}, TPoint{0, -1, 0}}};
    EXPECT_FALSE(poly1 == poly2);
}

TEST(TPolygon, DifferentPoints) {
    TPolygon poly1{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    TPolygon poly2{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{3, 3, 3}}};
    EXPECT_FALSE(poly1 == poly2);
}

TEST(TPolygon, SlightDifference) {
    TPolygon poly1{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    TPolygon poly2{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{2, 2, 2.0001}}};
    EXPECT_FALSE(poly1 == poly2);
}

TEST(TPolygon, SamePointsDifferentOrderWithDuplicates) {
    TPolygon poly1{{TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    TPolygon poly2{{TPoint{0, 1, 0}, TPoint{0, 0, 0}, TPoint{0, 1, 0}, TPoint{0, 0, 1}}};
    EXPECT_TRUE(poly1 == poly2);
}

TEST(TPolygon, EqualPolygonsHaveSameHash) {
    std::unordered_set<TPoint> points1 = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 0.0, 0.0}, TPoint{1.0, 1.0, 0.0},
                                          TPoint{0.0, 1.0, 0.0}};

    std::unordered_set<TPoint> points2 = {TPoint{1.0, 1.0, 0.0}, TPoint{0.0, 1.0, 0.0}, TPoint{0.0, 0.0, 0.0},
                                          TPoint{1.0, 0.0, 0.0}};

    TPolygon polygon1 = TPolygon(points1);
    TPolygon polygon2 = TPolygon(points2);

    EXPECT_EQ(polygon1, polygon2);

    std::hash<TPolygon> hash_fn;
    size_t hash1 = hash_fn(polygon1);
    size_t hash2 = hash_fn(polygon2);

    EXPECT_EQ(hash1, hash2);
}

TEST(TPolygon, DifferentPolygonsHaveDifferentHash) {
    std::unordered_set<TPoint> points1 = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 0.0, 0.0}, TPoint{1.0, 1.0, 0.0},
                                          TPoint{0.0, 1.0, 0.0}};

    std::unordered_set<TPoint> points2 = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 0.0, 0.0}, TPoint{2.0, 2.0, 0.0},
                                          TPoint{0.0, 1.0, 0.0}};

    TPolygon polygon1 = TPolygon(points1);
    TPolygon polygon2 = TPolygon(points2);

    EXPECT_NE(polygon1, polygon2);

    std::hash<TPolygon> hash_fn;
    size_t hash1 = hash_fn(polygon1);
    size_t hash2 = hash_fn(polygon2);

    EXPECT_NE(hash1, hash2);
}

TEST(TPolygon, HashConsistency) {
    std::unordered_set<TPoint> points = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 2.0, 3.0}, TPoint{4.0, 5.0, 6.0}};

    TPolygon polygon = TPolygon(points);
    std::hash<TPolygon> hash_fn;

    size_t h1 = hash_fn(polygon);
    size_t h2 = hash_fn(polygon);

    EXPECT_EQ(h1, h2);
}

TEST(TPolygon, HashInUnorderedSetWorksCorrectly) {
    std::unordered_set<TPolygon> polygonSet;

    std::unordered_set<TPoint> points1 = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 0.0, 0.0}, TPoint{1.0, 1.0, 0.0}};

    std::unordered_set<TPoint> points2 = {TPoint{1.0, 1.0, 0.0}, TPoint{0.0, 1.0, 0.0}, TPoint{0.0, 0.0, 0.0}};

    TPolygon poly1 = TPolygon(points1);
    TPolygon poly2 = TPolygon(points2);

    auto result1 = polygonSet.insert(poly1);
    EXPECT_TRUE(result1.second);

    EXPECT_FALSE(polygonSet.contains(poly2));

    std::unordered_set<TPoint> points3 = {TPoint{2.0, 0.0, 0.0}, TPoint{0.0, 3.0, 0.0}, TPoint{0.0, 0.0, 1.0}};
    TPolygon poly3 = TPolygon(points3);
    auto result2 = polygonSet.insert(poly3);
    EXPECT_TRUE(result2.second);
    EXPECT_NE(polygonSet.find(poly3), polygonSet.end());
}

TEST(TPolygon, PolygonsWithDifferentPointsAreNotEqual) {
    std::unordered_set<TPoint> points1 = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 0.0, 0.0}, TPoint{1.0, 1.0, 0.0}};

    std::unordered_set<TPoint> points2 = {TPoint{0.0, 0.0, 0.0}, TPoint{1.0, 0.0, 0.0}, TPoint{2.0, 1.0, 0.0}};

    TPolygon poly1 = TPolygon(points1);
    TPolygon poly2 = TPolygon(points2);

    EXPECT_NE(poly1, poly2);
    EXPECT_NE(std::hash<TPolygon>()(poly1), std::hash<TPolygon>()(poly2));
}
