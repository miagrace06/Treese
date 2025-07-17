#include "treese.h"
#include <algorithm>
#include <iostream>

Treese::Treese() : root(nullptr) {}

Treese::Treese(const std::string& initial) {
    if (initial.empty()) {
        root = nullptr;
    } else {
        root = new Node(initial);
    }
}

Treese::Treese(const Treese& other) : root(copyTree(other.root)) {}

Treese& Treese::operator=(const Treese& other) {
    if (this != &other) {
        delete root;
        root = copyTree(other.root);
    }
    return *this;
}

Treese::~Treese() {
    delete root;
}

size_t Treese::length() const {
    return root ? root->length : 0;
}

char Treese::at(size_t index) const {
    if (index >= length()) {
        throw std::out_of_range("Index out of range.");
    }
    
    Node* current = root;
    while (!current->is_leaf) {
        size_t left_length = current->left ? current->left->length : 0;
        if (index < left_length) {
            current = current->left;
        } else {
            index -= left_length;
            current = current->right;
        }
    }
    return current->data[index];
}

void Treese::print() const {
    printHelper(root);
    std::cout << std::endl;
}

Treese Treese::concat(const Treese& other) const {
    Treese result;
    
    if (!root && !other.root) {
        return result;
    } else if (!root) {
        result.root = copyTree(other.root);
    } else if (!other.root) {
        result.root = copyTree(root);
    } else {
        Node* left_copy = copyTree(root);
        Node* right_copy = copyTree(other.root);
        result.root = new Node(left_copy, right_copy);
        
        result.root = balance(result.root);
    }
    
    return result;
}

Treese::Node* Treese::copyTree(Node* node) {
    if (!node) return nullptr;
    
    if (node->is_leaf) {
        return new Node(node->data);
    } else {
        Node* left_copy = copyTree(node->left);
        Node* right_copy = copyTree(node->right);
        return new Node(left_copy, right_copy);
    }
}

void Treese::printHelper(Node* node) const {
    if (!node) return;
    
    if (node->is_leaf) {
        std::cout << node->data;
    } else {
        printHelper(node->left);
        printHelper(node->right);
    }
}

size_t Treese::getHeight(Node* node) {
    return node ? node->height : 0;
}

int Treese::getBalance(Node* node) {
    if (!node) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void Treese::updateHeight(Node* node) {
    if (node && !node->is_leaf) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

Treese::Node* Treese::rotateRight(Node* y) {
    if (!y || !y->left) return y;
    
    Node* x = y->left;
    Node* T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    updateHeight(y);
    updateHeight(x);
    
    y->length = (y->left ? y->left->length : 0) + (y->right ? y->right->length : 0);
    x->length = (x->left ? x->left->length : 0) + (x->right ? x->right->length : 0);
    
    return x;
}

Treese::Node* Treese::rotateLeft(Node* x) {
    if (!x || !x->right) return x;
    
    Node* y = x->right;
    Node* T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    updateHeight(x);
    updateHeight(y);
    
    x->length = (x->left ? x->left->length : 0) + (x->right ? x->right->length : 0);
    y->length = (y->left ? y->left->length : 0) + (y->right ? y->right->length : 0);
    
    return y;
}

Treese::Node* Treese::balance(Node* node) {
    if (!node || node->is_leaf) return node;
    
    updateHeight(node);
    
    int balance_factor = getBalance(node);
    
    if (balance_factor > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    
    if (balance_factor < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    
    if (balance_factor > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    if (balance_factor < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}
