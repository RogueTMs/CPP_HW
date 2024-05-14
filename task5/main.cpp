#include "scopedPointer.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(DeepCopy, copyConstructor) {

    ScopedPointerDeep<Triple> sp{new Triple{1, 2, 3}};
    ScopedPointerDeep<Triple> sp2 = sp;
    ASSERT_TRUE(sp.get() != std::nullopt);
}


TEST(DeepCopy, moveConstructor) {

    ScopedPointerDeep sp{new Triple{1, 2, 3}};
    ScopedPointerDeep sp2 {std::move(sp)};
    ASSERT_TRUE(sp.get() == std::nullopt);
}

TEST(DeepCopy, copyOperator) {

    ScopedPointerDeep sp1{new Triple{1, 2, 3}};
    ScopedPointerDeep sp2{new Triple{1, 2, 3}};
    sp2 = sp1;
    ASSERT_TRUE(sp1.get() != std::nullopt);
}

TEST(DeepCopy, moveOperator) {

    ScopedPointerDeep sp1{new Triple{1, 2, 3}};
    ScopedPointerDeep sp2{new Triple{1, 2, 3}};
    sp2 = std::move(sp1);
    ASSERT_TRUE(sp1.get() == std::nullopt);
}


TEST(Prohibited, copyConstructor) {

    ScopedPointerShallow sp{new Triple{1, 2, 3}};
    ScopedPointerShallow sp2  = std::move(sp);
    ASSERT_TRUE(sp.get() == std::nullopt);
}


TEST(Prohibited, moveConstructor) {

    ScopedPointerShallow sp{new Triple{1, 2, 3}};
    ScopedPointerShallow sp2 {std::move(sp)};
    ASSERT_TRUE(sp.get() == std::nullopt);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
