#include "MixIn.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

template <typename T, size_t LIMIT> struct ExampleClass : MixIn<LIMIT> {
    T value;
    ExampleClass(T val) : value(val) {}
};

TEST(ExpressionsInheritance, valTest) {
    const size_t limit = 4;
    typedef ExampleClass<int, limit> example;
    example a(0);
    example b(1);
    example c(2);
    example d(3);
    try {
        example e(4);
    } catch (const std::runtime_error &e) {
        EXPECT_EQ(e.what(), "Too many instances!");
    } catch(...){
        FAIL() << "Doesnt fail when trying to get instance out of limit";
    }
}
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
