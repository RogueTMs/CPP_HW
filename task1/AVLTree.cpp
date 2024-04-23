#include "AVLTree.h"
#include <algorithm>

template <typename T> AVLNode<T> *AVLTree<T>::find(T value) {
    AVLNode<T> *node = findImpl(root, value);
    return node;
}

template <typename T> int AVLTree<T>::getHeight(AVLNode<T> *node) {
    if (!node)
        return 0;
    return node->height;
}

template <typename T> int AVLTree<T>::getBalance(AVLNode<T> *node) {
    if (!node)
        return 0;
    return getHeight(node->right) - getHeight(node->left);
}

template <typename T> AVLNode<T> *AVLTree<T>::getMax(AVLNode<T> *node) {
    if (!node) {
        std::cout << "Empty tree\n";
        return nullptr;
    }

    AVLNode<T> *p = node;
    while (p->right)
        p = p->right;

    return p;
}

template <typename T> AVLNode<T> *AVLTree<T>::getMin(AVLNode<T> *node) {
    if (!node) {
        std::cout << "Empty tree\n";
        return nullptr;
    }

    AVLNode<T> *p = node;
    while (p->left)
        p = p->left;

    return p;
}

template <typename T>
AVLNode<T> *AVLTree<T>::insertImpl(AVLNode<T> *node, T value) {
    if (!node) {
        node = new AVLNode<T>(value);
        return node;
    }

    if (value < node->value)
        node->left = insertImpl(node->left, value);
    else if (value > node->value)
        node->right = insertImpl(node->right, value);
    else {
        std::cout << "Equal keys are not allowed in BST\n";
        return nullptr;
    }
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    return balanceTree(node);
}

template <typename T>
AVLNode<T> *AVLTree<T>::findImpl(AVLNode<T> *node, T value) {
    if (!node) {
        std::cout << "No such node\n";
        return node;
    }

    if (node->value == value)
        return node;

    if (node->value > value)
        return findImpl(node->left, value);
    else
        return findImpl(node->right, value);
}

template <typename T>
AVLNode<T> *AVLTree<T>::removeImpl(AVLNode<T> *node, T value) {
    if (!node) {
        std::cout << "Empty tree\n";
        return nullptr;
    }

    if (value < node->value) {
        node->left = removeImpl(node->left, value);
    } else if (value > node->value)
        node->right = removeImpl(node->right, value);
    else {
        if (!node->right && !node->left) {
            delete node;
            node = nullptr;
        } else if (!node->right) {
            AVLNode<T> *left = node->left;
            delete node;
            node = left;
        } else if (!node->left) {
            AVLNode<T> *right = node->right;
            delete node;
            node = right;
        } else {
            AVLNode<T> *smallest_right = node->right;
            while (smallest_right->left)
                smallest_right = smallest_right->left;
            node->value = smallest_right->value;

            node->right = removeImpl(node->right, node->value);
        }
    }
    if (node)
        node->height =
            1 + std::max(getHeight(node->left), getHeight(node->right));

    return balanceTree(node);
}

template <typename T> AVLNode<T> *AVLTree<T>::right_rotation(AVLNode<T> *node) {
    AVLNode<T> *newNode = node->left;
    node->left = newNode->right;
    newNode->right = node;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    newNode->height =
        1 + std::max(getHeight(newNode->left), getHeight(newNode->right));
    return newNode;
}

template <typename T> AVLNode<T> *AVLTree<T>::left_rotation(AVLNode<T> *node) {
    AVLNode<T> *newNode = node->right;
    node->right = newNode->left;
    newNode->left = node;
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    newNode->height =
        1 + std::max(getHeight(newNode->left), getHeight(newNode->right));
    return newNode;
}

template <typename T> AVLNode<T> *AVLTree<T>::balanceTree(AVLNode<T> *node) {
    int balance = getBalance(node);
    if (balance > 1) {
        if (getBalance(node->right) > -1) {
            return left_rotation(node);
        } else {
            node->right = right_rotation(node->right);
            return left_rotation(node);
        }
    } else if (balance < -1) {
        if (getBalance(node->left) > -1) {
            return right_rotation(node);
        } else {
            node->left = left_rotation(node->left);
            return right_rotation(node);
        }
    } else
        return node;
}

template <class T> void AVLTree<T>::clear() {
    std::vector<AVLNode<T> *> stack;

    if (root != nullptr)
        stack.push_back(root);

    while (!stack.empty()) {
        AVLNode<T> *node = stack.back();
        stack.pop_back();

        if (node->left != nullptr)
            stack.push_back(node->left);

        if (node->right != nullptr)
            stack.push_back(node->right);

        delete node;
    }

    root = nullptr;
}

template class AVLTree<int>;
template class AVLTree<float>;
template class AVLTree<std::string>;