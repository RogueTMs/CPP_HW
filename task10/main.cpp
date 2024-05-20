#include "MixIn.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

template <typename T, size_t LIMIT> struct Restricted : MixIn<LIMIT> {
    T value;
    Restricted(T val) : value(val) {}
};

TEST(ExpressionsInheritance, valTest) {
    const size_t limit = 4;
    typedef Restricted<char, limit> restricted_t;
    try {
        restricted_t a('1');
        restricted_t b('a');
        restricted_t c('1');
        restricted_t d('a');
        restricted_t f('1');

    } catch (const MixInException &e) {
        std::cout << e.what() << std::endl;
    }
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
