#ifndef TREESE_H
#define TREESE_H

#include <string>
#include <cstddef>
#include <stdexcept>
#include <iostream>

class Treese {
private:
    struct Node {
        bool is_leaf;
        size_t length;
        size_t height;
        Node* left;
        Node* right;
        std::string data;

        Node(const std::string& str)
            : is_leaf(true), length(str.length()), height(1),
              left(nullptr), right(nullptr), data(str) {}

        Node(Node* l, Node* r)
            : is_leaf(false), left(l), right(r), data("") {
            length = (l ? l->length : 0) + (r ? r->length : 0);
            height = 1 + std::max(l ? l->height : 0, r ? r->height : 0);
        }

        ~Node() {
            if (!is_leaf) {
                delete left;
                delete right;
            }
        }
    };

    Node* root;

    static Node* copyTree(Node* node);
    void printHelper(Node* node) const;

    static Node* balance(Node* node);
    static size_t getHeight(Node* node);
    static int getBalance(Node* node);
    static Node* rotateRight(Node* y);
    static Node* rotateLeft(Node* x);
    static void updateHeight(Node* node);
    static void updateLength(Node* node);

public:
    Treese();
    Treese(const std::string& initial);
    Treese(const Treese& other);
    Treese& operator=(const Treese& other);
    ~Treese();

    size_t length() const;
    char at(size_t index) const;
    void print() const;
    Treese concat(const Treese& other) const;
};

#endif // TREESE_H
