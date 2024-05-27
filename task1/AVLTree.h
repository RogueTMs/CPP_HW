#include <cstdlib>
#include <iostream>
#include <vector>

template <typename U> struct AVLNode {
    AVLNode *left;
    AVLNode *right;
    AVLNode *parent;

    U value;
    int height;

    AVLNode(U _value, AVLNode *parent_node = nullptr) : value(_value) {
        height = 1;
        left = nullptr;
        right = nullptr;
        parent = parent_node;
    }
};

template <typename T> class AVLTree {
  public:
    AVLNode<T> *root;
    AVLTree() { root = NULL; }
    AVLTree(const std::vector<T> &values);

    ~AVLTree() { clear(); };
    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&other);
    AVLTree &operator=(AVLTree other);

    void insert(T value) { root = insertImpl(root, value); }
    void remove(T value) { root = removeImpl(root, value); }

    AVLNode<T> *getMax(AVLNode<T> *node);
    AVLNode<T> *getMin(AVLNode<T> *node);

    AVLNode<T> *find(T value);

    class Iterator {
        AVLNode<T> *_cur;

      public:
        Iterator(AVLNode<T> *node) : _cur(node) {}

        Iterator &operator++();
        Iterator operator++(int);
        AVLNode<T> *operator->();
        AVLNode<T> &operator*();

        bool operator==(const Iterator &other) const {
            return _cur == other._cur;
        }

        bool operator!=(const Iterator &other) const {
            return !(*this == other);
        }
    };

    Iterator begin() { return Iterator(getMin(root)); }
    Iterator end() { return Iterator(nullptr); }

  private:
    int getHeight(AVLNode<T> *node);
    int getBalance(AVLNode<T> *node);
    AVLNode<T> *insertImpl(AVLNode<T> *node, T value,
                           AVLNode<T> *parent_node = nullptr);
    AVLNode<T> *removeImpl(AVLNode<T> *node, T value);
    AVLNode<T> *findImpl(AVLNode<T> *node, T value);

    AVLNode<T> *left_rotation(AVLNode<T> *node);
    AVLNode<T> *right_rotation(AVLNode<T> *node);
    AVLNode<T> *balanceTree(AVLNode<T> *node);

    // void swapData(AVLTree<T> &other, AVLNode<T> *root = nullptr);
    void clear();
};
