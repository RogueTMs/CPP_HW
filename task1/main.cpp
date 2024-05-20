#include "AVLTree.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>

template <typename T> bool compareTrees(AVLNode<T> *root1, AVLNode<T> *root2) {
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }

    if (root1 == nullptr || root2 == nullptr) {
        return false;
    }

    if (root1->value != root2->value) {
        return false;
    }

    if (!compareTrees(root1->left, root2->left)) {
        return false;
    }

    if (!compareTrees(root1->right, root2->right)) {
        return false;
    }

    return true;
}

TEST(AVLTreeTest, Insert) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    ASSERT_EQ(tree.root->value, 2);
    ASSERT_EQ(tree.root->left->value, 1);
    ASSERT_EQ(tree.root->right->value, 3);
}

TEST(AVLTreeTest, InsertString) {
    AVLTree<std::string> tree;

    tree.insert("aa");
    tree.insert("bb");
    tree.insert("cc");

    ASSERT_EQ(tree.root->value, "bb");
    ASSERT_EQ(tree.root->left->value, "aa");
    ASSERT_EQ(tree.root->right->value, "cc");
}

TEST(AVLTreeTest, Remove) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    tree.remove(2);
    tree.remove(1);

    ASSERT_EQ(tree.root->value, 3);
    ASSERT_EQ(tree.root->left, nullptr);
    ASSERT_EQ(tree.root->right, nullptr);
}

TEST(AVLTreeTest, GetMax) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    ASSERT_EQ(tree.getMax(tree.root)->value, 3);
}

TEST(AVLTreeTest, GetMin) {
    AVLTree<int> tree;

    tree.insert(3);
    tree.insert(2);
    tree.insert(1);

    ASSERT_EQ(tree.getMin(tree.root)->value, 1);
}

TEST(AVLTreeTest, BalanceTree) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.insert(5);

    ASSERT_EQ(tree.root->height, 3);
    ASSERT_EQ(tree.root->left->height, 1);
    ASSERT_EQ(tree.root->right->height, 2);
}

TEST(AVLTreeTest, Find) {
    AVLTree<int> tree;

    tree.insert(1);
    tree.insert(2);
    tree.insert(3);

    ASSERT_EQ(tree.find(2)->value, 2);
    ASSERT_EQ(tree.find(1)->value, 1);
    ASSERT_EQ(tree.find(3)->value, 3);
}

TEST(AVLTreeTest, CopyConstructor) {
    AVLTree<int> originalTree;
    originalTree.insert(1);
    originalTree.insert(2);
    originalTree.insert(3);

    AVLTree<int> copiedTree(originalTree);

    ASSERT_TRUE(compareTrees(originalTree.root, copiedTree.root));
}

TEST(AVLTreeTest, CopyAssignment) {
    AVLTree<int> originalTree;
    originalTree.insert(1);
    originalTree.insert(2);
    originalTree.insert(3);

    AVLTree<int> copiedTree;
    copiedTree.insert(4);
    copiedTree = originalTree;

    ASSERT_TRUE(compareTrees(originalTree.root, copiedTree.root));
}

TEST(AVLTreeTest, MoveConstructor) {
    AVLTree<int> tree1;
    tree1.insert(1);
    tree1.insert(2);
    tree1.insert(3);

    AVLTree<int> tree2(std::move(tree1));

    ASSERT_EQ(tree2.root->value, 2);
    ASSERT_EQ(tree2.root->left->value, 1);
    ASSERT_EQ(tree2.root->right->value, 3);
    ASSERT_EQ(tree1.root, nullptr);
}

TEST(AVLTreeTest, iterator) {

  std::vector<int> values = {9, 8, 7, 6, 5, 4, 3, 2, 1};
  AVLTree<int> determ_tree = AVLTree<int>(values);

  std::vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::vector<int> actual;

  for (auto node: determ_tree) {
    actual.push_back(node.value);
  }
  ASSERT_THAT(actual, expected);

}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    std::cout << "Hello!\n";

    return RUN_ALL_TESTS();
}
