#include "AVLTree.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

TEST(InsertTest, 1) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    ASSERT_EQ(tree.root->value, 2);
}

TEST(RemoveTest, 1) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    tree.remove(2);
    tree.remove(1);

    ASSERT_EQ(tree.root->value, 3);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
