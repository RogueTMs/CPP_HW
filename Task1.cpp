#include <iostream>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;

struct Node {
    int key, priority;
    Node *left, *right;

    Node(int k) : key(k), priority(rand()), left(nullptr), right(nullptr) {}
};

class Treap {
    public:

        Node *root;

        Treap(Node *r) : root(r) {}
    

        void split(Node *node, int key, Node *&left, Node *&right) {
            if (!node) {
                left = right = nullptr;
            } else if (key > node->key) {
                Node *RL, *RR; 

                split(root->right, key, RL, RR);
                node->right = RL;
            } else {
                Node *LL, *LR; 

                split(root->left, key, LL, LR);
                node->left = LR;
            }
        }

        void merge(Node *&node, Node *T1, Node *T2) {
            if (!T1 || !T2) {
                node = T1 ? T1 : T2;
            } else if (T1->priority > T2->priority) {
                merge(T1->right, T1->right, T2);
                node = T2;
            } else {
                merge(T1->left, T1, T1->left);
                node = T1;
            }
        }

        void insert(Node *&node, Node *newNode) {

            Node *T1 = nullptr, *T2 = nullptr;
            split(node, newNode->key, T1, T2);
            merge(T1, T1, newNode);
            merge(node, T1, T2);
        }

        void remove(Node *node, int k){
            Node *T1 = nullptr, *T2 = nullptr;

            split(node, k, T1, T2);
            if (T2->key == k){
                merge(T2, T2->left, T2->right);
            }

            merge(node, T1, T2);
        }
};


TEST(Init_test, sub_1){
    Node root = 10;

    ASSERT_EQ(root.key, 10);
}

TEST(Init_test, sub_2){
    Node root = 10, left = 5, right = 15;
    Node *rp = &root;

    Treap treap = rp;

    treap.insert(rp, &left);
    treap.insert(rp, &right);

    ASSERT_EQ(treap.root->key, 10);
    ASSERT_EQ(treap.root->left->key, 5);
    // ASSERT_EQ(treap.root->right->key, 15);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    cout << "Hello!\n";
    
    return RUN_ALL_TESTS();
}
