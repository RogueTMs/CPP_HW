#include "generic_func.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(GetIndexOfFirstMatch, EmptyList) {
    auto checker = [](int x) { return x == 42; };
    EXPECT_EQ(getIndexOfFirstMatch(checker), -1);
}

TEST(GetIndexOfFirstMatch, SingleMatch) {
    auto checker = [](int x) { return x == 42; };
    EXPECT_EQ(getIndexOfFirstMatch(checker, 42, 1, 2, 3), 0);
}

TEST(GetIndexOfFirstMatch, MultipleMatches) {
    auto checker = [](int x) { return x % 2 == 0; };
    EXPECT_EQ(getIndexOfFirstMatch(checker, 1, 4, 6, 8), 1);
}

TEST(GetIndexOfFirstMatch, NoMatch) {
    auto checker = [](int x) { return x == 42; };
    EXPECT_EQ(getIndexOfFirstMatch(checker, 1, 3, 5, 7), -1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
