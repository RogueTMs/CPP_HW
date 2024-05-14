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



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!" << std::endl;

    return RUN_ALL_TESTS();
}
