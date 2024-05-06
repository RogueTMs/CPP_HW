#include <cstdlib>
#include <iostream>
#include <vector>

template <typename U> struct AVLNode {
    AVLNode *left;
    AVLNode *right;

    U value;
    int height;

    AVLNode(U _value) : value(_value) {
        height = 1;
        left = NULL;
        right = NULL;
    }
};

template <typename T> class AVLTree {
  public:
    AVLNode<T> *root;

    AVLTree() { root = NULL; }

    ~AVLTree() { clear(); };
    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&other);
    AVLTree &operator=(AVLTree other);


    void insert(T value) { root = insertImpl(root, value); }
    void remove(T value) { root = removeImpl(root, value); }

    AVLNode<T> *getMax(AVLNode<T> *node);
    AVLNode<T> *getMin(AVLNode<T> *node);

    AVLNode<T> *find(T value);

  private:
    int getHeight(AVLNode<T> *node);
    int getBalance(AVLNode<T> *node);
    AVLNode<T> *insertImpl(AVLNode<T> *node, T value);
    AVLNode<T> *removeImpl(AVLNode<T> *node, T value);
    AVLNode<T> *findImpl(AVLNode<T> *node, T value);

    AVLNode<T> *left_rotation(AVLNode<T> *node);
    AVLNode<T> *right_rotation(AVLNode<T> *node);
    AVLNode<T> *balanceTree(AVLNode<T> *node);

    void swapData(AVLTree<T> &other, AVLNode<T> *root=nullptr);
    void clear();
};
