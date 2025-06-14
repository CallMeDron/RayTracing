#include "../ray_tracing_lib/all.h"

#include <gtest/gtest.h>

using namespace NRayTracingLib;

static constexpr double TINY = ACCURACY / 2.0;
static constexpr double NOT_TINY = ACCURACY * 2.0;

//=== TSafeDouble tests ===

TEST(TSafeDouble, Constructor_Default_SetsZero) {
    TSafeDouble a;
    EXPECT_EQ(a.Value, 0.0);
}

TEST(TSafeDouble, Constructor_FromInt_SetsCorrectValue) {
    int v = 42;
    TSafeDouble a(v);
    EXPECT_EQ(a.Value, static_cast<double>(v));
}

TEST(TSafeDouble, Constructor_FromSize_t_SetsCorrectValue) {
    size_t v = 42;
    TSafeDouble a(v);
    EXPECT_EQ(a.Value, static_cast<double>(v));
}

TEST(TSafeDouble, Constructor_FromDouble_SetsCorrectValue) {
    double v = 3.1415;
    TSafeDouble a(v);
    EXPECT_EQ(a.Value, v);
}

TEST(TSafeDouble, EqualityOperator_WithValuesWithinTolerance_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    EXPECT_TRUE(a == b);
}

TEST(TSafeDouble, EqualityOperator_WithValuesOutsideTolerance_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + NOT_TINY);
    EXPECT_FALSE(a == b);
}

TEST(TSafeDouble, InequalityOperator_WithValuesOutsideTolerance_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + NOT_TINY);
    EXPECT_TRUE(a != b);
}

TEST(TSafeDouble, InequalityOperator_WithValuesWithinTolerance_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    EXPECT_FALSE(a != b);
}

TEST(TSafeDouble, GreaterThanOperator_CorrectComparison) {
    TSafeDouble a(2.0);
    TSafeDouble b(1.0);
    EXPECT_TRUE(a > b);
    EXPECT_FALSE(b > a);

    TSafeDouble c(2.0 + TINY);
    EXPECT_FALSE(a > c);
}

TEST(TSafeDouble, LessThanOperator_CorrectComparison) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);

    TSafeDouble c(1.0 - TINY);
    EXPECT_FALSE(a < c);
}

TEST(TSafeDouble, GreaterEqualOperator_Behavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    TSafeDouble c(0.9);
    EXPECT_TRUE(a >= b);
    EXPECT_TRUE(a >= c);
    EXPECT_FALSE(c >= a);
}

TEST(TSafeDouble, LessEqualOperator_Behavior) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 - TINY);
    TSafeDouble c(1.1);
    EXPECT_TRUE(a <= b);
    EXPECT_TRUE(a <= c);
    EXPECT_FALSE(c <= a);
}

TEST(TSafeDouble, UnaryMinus_NegatesValue) {
    TSafeDouble a(5.0);
    TSafeDouble b = -a;
    EXPECT_EQ(b.Value, -5.0);
    TSafeDouble c = -b;
    EXPECT_EQ(c.Value, 5.0);
}

TEST(TSafeDouble, Abs_ReturnsAbsoluteValue_ForNegative) {
    TSafeDouble a(-3.5);
    TSafeDouble result = a.abs();
    EXPECT_EQ(result.Value, 3.5);
}

TEST(TSafeDouble, Abs_ReturnsZero_ForZero) {
    TSafeDouble a(0.0);
    TSafeDouble result = a.abs();
    EXPECT_EQ(result.Value, 0.0);
}

TEST(TSafeDouble, Abs_ReturnsSameValue_ForPositive) {
    TSafeDouble a(4.2);
    TSafeDouble result = a.abs();
    EXPECT_EQ(result.Value, 4.2);
}

TEST(TSafeDouble, Addition_AddsValues) {
    TSafeDouble a(1.5);
    TSafeDouble b(2.5);
    TSafeDouble c = a + b;
    EXPECT_EQ(c.Value, 4.0);
}

TEST(TSafeDouble, Subtraction_SubtractsValues) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    TSafeDouble c = a - b;
    EXPECT_EQ(c.Value, 2.0);
}

TEST(TSafeDouble, Multiplication_MultipliesValues) {
    TSafeDouble a(2.0);
    TSafeDouble b(4.0);
    TSafeDouble c = a * b;
    EXPECT_EQ(c.Value, 8.0);
}

TEST(TSafeDouble, Division_DividesValues) {
    TSafeDouble a(10.0);
    TSafeDouble b(2.0);
    TSafeDouble c = a / b;
    EXPECT_EQ(c.Value, 5.0);
}

TEST(TSafeDouble, Division_ByZero_Throws) {
    TSafeDouble a(1.0);
    TSafeDouble zero(0.0);
    EXPECT_THROW(a / zero, std::runtime_error);
}

TEST(TSafeDouble, PlusEquals_AddsAndAssigns) {
    TSafeDouble a(1.0);
    TSafeDouble b(2.0);
    a += b;
    EXPECT_EQ(a.Value, 3.0);
}

TEST(TSafeDouble, MinusEquals_SubtractsAndAssigns) {
    TSafeDouble a(5.0);
    TSafeDouble b(3.0);
    a -= b;
    EXPECT_EQ(a.Value, 2.0);
}

TEST(TSafeDouble, MultiplyEquals_MultipliesAndAssigns) {
    TSafeDouble a(3.0);
    TSafeDouble b(4.0);
    a *= b;
    EXPECT_EQ(a.Value, 12.0);
}

TEST(TSafeDouble, DivideEquals_DividesAndAssigns) {
    TSafeDouble a(8.0);
    TSafeDouble b(2.0);
    a /= b;
    EXPECT_EQ(a.Value, 4.0);
}

TEST(TSafeDouble, Pow_RaisesToPower_CorrectResult) {
    TSafeDouble a(2.0);
    TSafeDouble exponent(3.0);
    TSafeDouble result = a.pow(exponent);
    EXPECT_EQ(result.Value, 8.0);
}

TEST(TSafeDouble, EqualityOperator_WithValuesOnBoundary_ReturnsTrue) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + TINY);
    EXPECT_TRUE(a == b);
}

TEST(TSafeDouble, EqualityOperator_WithValuesJustOutsideBoundary_ReturnsFalse) {
    TSafeDouble a(1.0);
    TSafeDouble b(1.0 + NOT_TINY);
    EXPECT_FALSE(a == b);
}

TEST(TSafeDouble, OperatorGreater_HandlesEdgeCases) {
    TSafeDouble a(1.0);
    TSafeDouble b(1 - TINY);
    EXPECT_FALSE(a > b);

    TSafeDouble c(1.0 + NOT_TINY);
    EXPECT_FALSE(a > c);
}

TEST(TSafeDouble, OperatorLess_HandlesEdgeCases) {
    TSafeDouble a(1.0);
    TSafeDouble b(1 + NOT_TINY);
    EXPECT_TRUE(a < b);

    TSafeDouble c(1.0 - NOT_TINY);
    EXPECT_FALSE(a < c);
}

TEST(TSafeDouble, CompoundExpressions_CorrectResults) {
    TSafeDouble a(2.0);
    TSafeDouble b(3.0);
    TSafeDouble c = (a + b) * a - b / a;
    EXPECT_EQ(c.Value, (2.0 + 3.0) * 2.0 - 3.0 / 2.0);
}

TEST(TSafeDouble, Pow_NegativeExponent_ReturnsCorrectResult) {
    TSafeDouble base(4.0);
    TSafeDouble exp(-2.0);
    TSafeDouble result = base.pow(exp);
    EXPECT_EQ(result.Value, 0.0625);
}

TEST(TSafeDouble, Division_ByVerySmallNumber) {
    TSafeDouble a(1.0);
    TSafeDouble tiny(1e-12);
    EXPECT_THROW(a / tiny, std::runtime_error);
}

TEST(TSafeDouble, Abs_MultipleCases) {
    TSafeDouble neg(-123.456);
    TSafeDouble pos(789.1011);
    TSafeDouble zero(0.0);
    EXPECT_EQ(neg.abs().Value, 123.456);
    EXPECT_EQ(pos.abs().Value, 789.1011);
    EXPECT_EQ(zero.abs().Value, 0.0);
}

TEST(TSafeDouble, ComplexComparison_BoundaryCases) {
    TSafeDouble a(1 + TINY);
    TSafeDouble b(1 + 2 * TINY);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_FALSE(a > b);
    EXPECT_FALSE(a < b);
}

TEST(TSafeDouble, OperatorPlusEquals_MultipleSteps) {
    TSafeDouble a(1.0);
    a += TSafeDouble(2.0);
    EXPECT_EQ(a.Value, 3.0);
    a += TSafeDouble(4.0);
    EXPECT_EQ(a.Value, 7.0);
}

TEST(TSafeDouble, OperatorMinusEquals_MultipleSteps) {
    TSafeDouble a(10.0);
    a -= TSafeDouble(3.0);
    EXPECT_EQ(a.Value, 7.0);
    a -= TSafeDouble(2.0);
    EXPECT_EQ(a.Value, 5.0);
}

TEST(TSafeDouble, MultiplicationAndDivisionWithNegatives) {
    TSafeDouble a(-2.0);
    TSafeDouble b(4.0);
    TSafeDouble c = a * b;
    EXPECT_EQ(c.Value, -8.0);
    TSafeDouble d = c / b;
    EXPECT_EQ(d.Value, -2.0);
}

TEST(TSafeDouble, DivisionLeadingToLargeNumber) {
    TSafeDouble a(1.0);
    TSafeDouble tiny(1.0 / NOT_TINY);
    TSafeDouble result = a / tiny;
    EXPECT_EQ(result.Value, NOT_TINY);
}

TEST(TSafeDouble, DivisionByZeroThrows) {
    TSafeDouble a(1.0);
    TSafeDouble zero(0.0);
    EXPECT_THROW(a / zero, std::runtime_error);
}

TEST(TSafeDouble, LargeNumbersHandling) {
    TSafeDouble a(1e308);
    TSafeDouble b(1e308);
    EXPECT_TRUE(a == b);
    TSafeDouble c = a + b;
    EXPECT_TRUE(std::isinf(c.Value) || c.Value > 0);
}

TEST(TSafeDouble, VerySmallNumbersHandling) {
    TSafeDouble a(1e-308);
    TSafeDouble b(1e-308);
    EXPECT_TRUE(a == b);
    TSafeDouble c = a + b;
    EXPECT_EQ(c.Value, 2e-308);
}