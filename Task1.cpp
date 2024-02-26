#include <iostream>

#include "googletest/googlemock/include/gmock/gmock.h"
#include "googletest/googletest/include/gtest/gtest.h"

using namespace std;

struct Node {
    int key, priority;
    Node *left, *right;

    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

void split(Node *root, int key, Node *&left, Node *&right) {
    if (!root) {
        left = right = nullptr;
    } else if (key < root->key) {
        split(root->left, key, left, root->left);
        right = root;
    } else {
        split(root->right, key, root->right, right);
        left = root;
    }
}

void merge(Node *&root, Node *left, Node *right) {
    if (!left || !right) {
        root = left ? left : right;
    } else if (left->priority > right->priority) {
        merge(left->right, left->right, right);
        root = left;
    } else {
        merge(right->left, left, right->left);
        root = right;
    }
}

void insert(Node *&root, Node *newNode) {
    if (!root) {
        root = newNode;
    } else if (newNode->priority > root->priority) {
        split(root, newNode->key, newNode->left, newNode->right);
        root = newNode;
    } else {
        insert(newNode->key < root->key ? root->left : root->right, newNode);
    }
}

void erase(Node *&root, int key) {
    if (!root) return;
    if (root->key == key) {
        Node *temp = root;
        merge(root, root->left, root->right);
        delete temp;
    } else {
        erase(key < root->key ? root->left : root->right, key);
    }
}

void inorder(Node *root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

// Define tests for the Node struct
TEST(NodeTest, Constructor) {
  Node node(5);
  EXPECT_EQ(5, node.key);
  EXPECT_EQ(0, node.priority); // Assuming priority is initialized to 0
  EXPECT_EQ(nullptr, node.left);
  EXPECT_EQ(nullptr, node.right);
}

// Add more tests for other functions or behaviors of the Node struct

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}