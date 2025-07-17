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
        
        std::string data;
        
        Node* left;
        Node* right;
        
        Node(const std::string& str) : is_leaf(true), length(str.length()), 
                                       height(1), data(str), left(nullptr), right(nullptr) {}
        
        Node(Node* l, Node* r) : is_leaf(false), left(l), right(r), data("") {
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
    
    Node* copyTree(Node* node);
    void printHelper(Node* node) const;
    Node* balance(Node* node);
    size_t getHeight(Node* node);
    int getBalance(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeft(Node* node);
    void updateHeight(Node* node);

public:
    Treese();
    Treese(const std::string& initial);
    Treese(const Treese& other);
    Treese& operator=(const Treese& other);
    ~Treese();
    size_t length() const;
    char at(size_t index) const;
    void print() const;
    
#endif // TREESE_H
    Treese concat(const Treese& other) const;
};
