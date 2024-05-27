#include "scopedPointer.cpp"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(DeepCopy, copyConstructor) {

    ScopedPointerDeep<Triple> sp1{new Triple{1, 2, 3}};
    ScopedPointerDeep<Triple> sp2(sp1);
    EXPECT_TRUE(sp1.get() != std::nullopt);
    EXPECT_EQ(sp1->first, sp2->first);
    EXPECT_EQ(sp1->second, sp2->second);
    EXPECT_EQ(sp1->third, sp2->third);
}


TEST(DeepCopy, moveConstructor) {

    ScopedPointerDeep<Triple> sp{new Triple{1, 2, 3}};
    ScopedPointerDeep<Triple> sp2 {std::move(sp)};
    EXPECT_TRUE(sp.get() == std::nullopt);
    EXPECT_EQ(1, sp2->first);
    EXPECT_EQ(2, sp2->second);
    EXPECT_EQ(3, sp2->third);
}

TEST(DeepCopy, copyOperator) {

    ScopedPointerDeep<Triple> sp1{new Triple{1, 2, 3}};
    ScopedPointerDeep<Triple> sp2{new Triple{3, 2, 1}};
    sp2 = sp1;
    EXPECT_TRUE(sp1.get() != std::nullopt);
    EXPECT_EQ(sp1->first, sp2->first);
    EXPECT_EQ(sp1->second, sp2->second);
    EXPECT_EQ(sp1->third, sp2->third);
}

TEST(DeepCopy, moveOperator) {

    ScopedPointerDeep<Triple> sp1{new Triple{1, 2, 3}};
    ScopedPointerDeep<Triple> sp2{new Triple{0, 0, 0}};
    sp2 = std::move(sp1);
    EXPECT_TRUE(sp1.get() == std::nullopt);
    EXPECT_EQ(1, sp2->first);
    EXPECT_EQ(2, sp2->second);
    EXPECT_EQ(3, sp2->third);
}

TEST(Prohibited, moveConstructor) {

    ScopedPointerShallow<Triple> sp1{new Triple{1, 2, 3}};
    ScopedPointerShallow<Triple> sp2 {std::move(sp1)};
    EXPECT_TRUE(sp1.get() == std::nullopt);
    EXPECT_EQ(1, sp2->first);
    EXPECT_EQ(2, sp2->second);
    EXPECT_EQ(3, sp2->third);
}

TEST(Prohibited, moveOperator) {

    ScopedPointerShallow<Triple> sp1{new Triple{1, 2, 3}};
    ScopedPointerShallow<Triple> sp2{new Triple{0, 0, 0}};
    sp2 = std::move(sp1);
    EXPECT_TRUE(sp1.get() == std::nullopt);
    EXPECT_EQ(1, sp2->first);
    EXPECT_EQ(2, sp2->second);
    EXPECT_EQ(3, sp2->third);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
