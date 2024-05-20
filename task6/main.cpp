#include "squareMatrix.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SquareMatrix, diagConstructor) {

    SquareMatrix m1({1.f, 3.f, -2.f});
    ASSERT_TRUE((double)m1 == 2.f);
}

TEST(SquareMatrix, copyConstructor) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2 = m1;
    ASSERT_TRUE((double)m1 == (double)m2);
}

TEST(SquareMatrix, moveConstructor) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2 = std::move(m1);
    ASSERT_TRUE((double)m1 == 0);
    ASSERT_TRUE((double)m2 == 3);
}

TEST(SquareMatrix, operatorSqBck) {

    SquareMatrix m1({1, 2, 3});
    ASSERT_TRUE(m1[0][0] == 1);
    ASSERT_TRUE(m1[1][1] == 2);
    ASSERT_TRUE(m1[2][2] == 3);
}

TEST(SquareMatrix, matrixOperators) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2({2, 2, 2});
    ASSERT_TRUE((double)(m1 - m2) == -3);
    ASSERT_TRUE((double)(m1 + m2) == 9);
    ASSERT_TRUE((double)(m1 * m2) == 6);
    ASSERT_FALSE(m1 == m2);
    ASSERT_TRUE(m1 != m2);

    m1 += m2;
    ASSERT_TRUE((double)m1 == 9);

    m1 *= m2;
    ASSERT_TRUE((double)m1 == 18);
}

TEST(SquareMatrix, matrixScalarOperators) {

    SquareMatrix m1({1, 2, 3});
    ASSERT_TRUE((double)(m1 - 1) == 3);
    ASSERT_TRUE((double)(m1 + 1) == 9);
    ASSERT_TRUE((double)(m1 * 2) == 12);

    m1 += 1;
    ASSERT_TRUE((double)m1 == 9);

    m1 *= 2;
    ASSERT_TRUE((double)m1 == 18);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!" << std::endl;

    return RUN_ALL_TESTS();
}
