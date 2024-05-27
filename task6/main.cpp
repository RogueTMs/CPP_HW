#include "squareMatrix.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(SquareMatrix, operatorSqBck) {

    SquareMatrix m1({1, 2, 3});
    EXPECT_EQ(m1[0][0], 1);
    EXPECT_EQ(m1[1][1], 2);
    EXPECT_EQ(m1[2][2], 3);
}

TEST(SquareMatrix, diagConstructor) {

    SquareMatrix m1({1.f, 3.f, -2.f});
    EXPECT_EQ((double)m1, 2.f);
}

TEST(SquareMatrix, copyConstructor) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2 = m1;
    EXPECT_EQ((double)m1, (double)m2);
}

TEST(SquareMatrix, moveConstructor) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2 = std::move(m1);
    EXPECT_EQ((double)m1, 0);
    EXPECT_EQ((double)m2, 3);
}

TEST(SquareMatrix, matrixOperators) {

    SquareMatrix m1({1, 1, 1});
    SquareMatrix m2({2, 2, 2});
    EXPECT_EQ((double)(m1 - m2), -3);
    EXPECT_EQ((double)(m1 + m2), 9);
    EXPECT_EQ((double)(m1 * m2),6);
    EXPECT_FALSE(m1 == m2);
    EXPECT_TRUE(m1 != m2);

    m1 += m2;
    EXPECT_EQ((double)m1, 9);

    m1 *= m2;
    EXPECT_EQ((double)m1, 18);
}

TEST(SquareMatrix, matrixScalarOperators) {

    SquareMatrix m1({1, 2, 3});
    EXPECT_EQ((double)(m1 - 1), 3);
    EXPECT_EQ((double)(1 + m1), 9);
    EXPECT_EQ((double)(m1 * 2),12);

    m1 += 1;
    EXPECT_EQ((double)m1, 9);

    m1 *= 2;
    EXPECT_EQ((double)m1, 18);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!" << std::endl;

    return RUN_ALL_TESTS();
}
