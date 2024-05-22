#include "CompilePrimes.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(Count, valTest) {
    EXPECT_EQ(prime<5>::value, 11);
    EXPECT_EQ(prime<100>::value, 541);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
