#include "static_checks.hpp"

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


TEST(Static_checks, allocPositive) {
    char arg1 = 'C';
    float arg2 = 14.f;
    Triple arg3(1, 2, 3);

    const size_t memory_sum = sizeof(arg1) + sizeof(arg2) + sizeof(arg3);
    char mem[memory_sum];

    allocate<memory_sum>(mem, arg1, arg2, arg3);

    char *arg1_ = (char *)(mem);
    float *arg2_ = (float *)(mem + sizeof(arg1));
    Triple *arg3_ = (Triple *)(mem + sizeof(arg1) + sizeof(arg2));

    EXPECT_EQ(arg1, *arg1_);
    EXPECT_EQ(arg2, *arg2_);
    EXPECT_EQ(arg3, *arg3_);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
