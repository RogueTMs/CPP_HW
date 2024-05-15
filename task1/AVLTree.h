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
    class Iterator {
        AVLNode<T> *curr_;
        std::vector<AVLNode<T> *> stack;

      public:
        Iterator(AVLNode<T> *ptr) {
            push_node_trace(ptr);
            curr_ = has_next() ? next() : nullptr;
        }
        Iterator(const Iterator &other);
        Iterator &operator=(const Iterator &other);
        ~Iterator() {}

        // Iterator's operators
        AVLNode<T> &operator*();
        AVLNode<T> *operator->();
        Iterator &operator++();
        Iterator operator++(int);
        friend bool operator==(const Iterator &first, const Iterator &second) {
            return first.curr_ == second.curr_;
        }
        friend bool operator!=(const typename AVLTree<T>::Iterator &first,
                               const AVLTree<T>::Iterator &second) {
            return !(first == second);
        }

      private:
        void push_node_trace(AVLNode<T> *node);
        bool has_next();
        AVLNode<T> *next();
    };

    AVLNode<T> *root;

    AVLTree() { root = NULL; }
    AVLTree(const std::vector<T>& values);

    ~AVLTree() { clear(); };
    AVLTree(const AVLTree &other);
    AVLTree(AVLTree &&other);
    AVLTree &operator=(AVLTree other);

    void insert(T value) { root = insertImpl(root, value); }
    void remove(T value) { root = removeImpl(root, value); }

    AVLNode<T> *getMax(AVLNode<T> *node);
    AVLNode<T> *getMin(AVLNode<T> *node);

    AVLNode<T> *find(T value);
    Iterator begin() { return Iterator(root); }
    Iterator end() { return Iterator(nullptr); }

  private:
    int getHeight(AVLNode<T> *node);
    int getBalance(AVLNode<T> *node);
    AVLNode<T> *insertImpl(AVLNode<T> *node, T value);
    AVLNode<T> *removeImpl(AVLNode<T> *node, T value);
    AVLNode<T> *findImpl(AVLNode<T> *node, T value);

    AVLNode<T> *left_rotation(AVLNode<T> *node);
    AVLNode<T> *right_rotation(AVLNode<T> *node);
    AVLNode<T> *balanceTree(AVLNode<T> *node);

    void swapData(AVLTree<T> &other, AVLNode<T> *root = nullptr);
    void clear();
};
