#include <gtest/gtest.h>
#include <solver.hpp>

TEST(SolverTest, BasicEquation) {
    EXPECT_DOUBLE_EQ(solve_equation(2.0, 4.0), -2.0);
}

TEST(SolverTest, ZeroACoefficient) {
    EXPECT_DOUBLE_EQ(solve_equation(0.0, 4.0), 0.0);
}

TEST(SolverTest, NegativeCoefficients) {
    EXPECT_DOUBLE_EQ(solve_equation(-2.0, -4.0), -2.0);
}

TEST(SolverTest, FractionalResult) {
    EXPECT_DOUBLE_EQ(solve_equation(4.0, 2.0), -0.5);
}
