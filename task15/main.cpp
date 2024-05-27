#include "container.hpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

struct Triple {
  protected:
    size_t first, second, third;

  public:
    Triple(size_t f, size_t s, size_t t) : first(f), second(s), third(t) {}

    bool operator==(const Triple &other) const {
        return first == other.first && second == other.second &&
               third == other.third;
    }
};


TEST(Container, simplePositive){
    Triple t{2, 3, 4};
    Container<int, char, Triple> c(12, 'c', t);

    EXPECT_EQ(12, c.getElement<int>(0));
    EXPECT_EQ('c', c.getElement<char>(1));
    EXPECT_EQ(t, c.getElement<Triple>(2));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
