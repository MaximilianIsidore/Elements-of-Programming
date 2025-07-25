#include <iostream>
#include <memory>

enum Color { RED, BLACK };

template<typename T>
struct Node {
    T data;
    Color color;
    std::shared_ptr<Node<T>> left;
    std::shared_ptr<Node<T>> right;
    std::shared_ptr<Node<T>> parent;
    
    Node(T value, Color c = RED) 
        : data(value), color(c), left(nullptr), right(nullptr), parent(nullptr) {}
};

template<typename T>
class RedBlackTree {
private:
    std::shared_ptr<Node<T>> root;
    std::shared_ptr<Node<T>> NIL; // Sentinel node
    
    // Helper functions
    void leftRotate(std::shared_ptr<Node<T>> x);
    void rightRotate(std::shared_ptr<Node<T>> x);
    void insertFixup(std::shared_ptr<Node<T>> z);
    void deleteFixup(std::shared_ptr<Node<T>> x);
    void transplant(std::shared_ptr<Node<T>> u, std::shared_ptr<Node<T>> v);
    std::shared_ptr<Node<T>> minimum(std::shared_ptr<Node<T>> node);
    std::shared_ptr<Node<T>> maximum(std::shared_ptr<Node<T>> node);
    std::shared_ptr<Node<T>> successor(std::shared_ptr<Node<T>> node);
    void inorderHelper(std::shared_ptr<Node<T>> node);
    
public:
    RedBlackTree();
    ~RedBlackTree() = default;
    
    void insert(T data);
    void remove(T data);
    std::shared_ptr<Node<T>> search(T data);
    void inorderTraversal();
    std::shared_ptr<Node<T>> getRoot() { return root; }
};

// Constructor
template<typename T>
RedBlackTree<T>::RedBlackTree() {
    NIL = std::make_shared<Node<T>>(T{}, BLACK);
    root = NIL;
}

// Left Rotation (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::leftRotate(std::shared_ptr<Node<T>> x) {
    auto y = x->right;          // Set y
    x->right = y->left;         // Turn y's left subtree into x's right subtree
    
    if (y->left != NIL) {
        y->left->parent = x;
    }
    
    y->parent = x->parent;      // Link x's parent to y
    
    if (x->parent == NIL) {
        root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    
    y->left = x;               // Put x on y's left
    x->parent = y;
}

// Right Rotation (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::rightRotate(std::shared_ptr<Node<T>> x) {
    auto y = x->left;          // Set y
    x->left = y->right;        // Turn y's right subtree into x's left subtree
    
    if (y->right != NIL) {
        y->right->parent = x;
    }
    
    y->parent = x->parent;     // Link x's parent to y
    
    if (x->parent == NIL) {
        root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    
    y->right = x;              // Put x on y's right
    x->parent = y;
}

// RB-INSERT (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::insert(T data) {
    auto z = std::make_shared<Node<T>>(data);
    auto y = NIL;
    auto x = root;
    
    // Standard BST insertion
    while (x != NIL) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    
    z->parent = y;
    
    if (y == NIL) {
        root = z;              // Tree was empty
    } else if (z->data < y->data) {
        y->left = z;
    } else {
        y->right = z;
    }
    
    z->left = NIL;
    z->right = NIL;
    z->color = RED;            // New node is colored red
    
    insertFixup(z);            // Fix red-black properties
}

// RB-INSERT-FIXUP (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::insertFixup(std::shared_ptr<Node<T>> z) {
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            auto y = z->parent->parent->right;  // Uncle
            
            if (y->color == RED) {              // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {    // Case 2
                    z = z->parent;
                    leftRotate(z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {  // Same as above with "right" and "left" exchanged
            auto y = z->parent->parent->left;   // Uncle
            
            if (y->color == RED) {              // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {     // Case 2
                    z = z->parent;
                    rightRotate(z);
                }
                // Case 3
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK;  // Root is always black
}

// Tree Search
template<typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::search(T data) {
    auto current = root;
    while (current != NIL) {
        if (data == current->data) {
            return current;
        } else if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return NIL;
}

// Find minimum node
template<typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::minimum(std::shared_ptr<Node<T>> node) {
    while (node->left != NIL) {
        node = node->left;
    }
    return node;
}

// Find maximum node
template<typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::maximum(std::shared_ptr<Node<T>> node) {
    while (node->right != NIL) {
        node = node->right;
    }
    return node;
}

// Find successor
template<typename T>
std::shared_ptr<Node<T>> RedBlackTree<T>::successor(std::shared_ptr<Node<T>> x) {
    if (x->right != NIL) {
        return minimum(x->right);
    }
    auto y = x->parent;
    while (y != NIL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// RB-TRANSPLANT (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::transplant(std::shared_ptr<Node<T>> u, std::shared_ptr<Node<T>> v) {
    if (u->parent == NIL) {
        root = v;
    } else if (u == u->parent->left) {
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

// RB-DELETE (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::remove(T data) {
    auto z = search(data);
    if (z == NIL) {
        std::cout << "Node not found!" << std::endl;
        return;
    }
    
    auto y = z;
    auto y_original_color = y->color;
    std::shared_ptr<Node<T>> x;
    
    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;
        
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    
    if (y_original_color == BLACK) {
        deleteFixup(x);
    }
}

// RB-DELETE-FIXUP (CLRS Algorithm)
template<typename T>
void RedBlackTree<T>::deleteFixup(std::shared_ptr<Node<T>> x) {
    while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            auto w = x->parent->right;
            
            if (w->color == RED) {              // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            
            if (w->left->color == BLACK && w->right->color == BLACK) {  // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) { // Case 3
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(w);
                    w = x->parent->right;
                }
                // Case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                leftRotate(x->parent);
                x = root;
            }
        } else {  // Same as above with "right" and "left" exchanged
            auto w = x->parent->left;
            
            if (w->color == RED) {              // Case 1
                w->color = BLACK;
                x->parent->color = RED;
                rightRotate(x->parent);
                w = x->parent->left;
            }
            
            if (w->right->color == BLACK && w->left->color == BLACK) {  // Case 2
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {  // Case 3
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(w);
                    w = x->parent->left;
                }
                // Case 4
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;
}

// Inorder traversal helper
template<typename T>
void RedBlackTree<T>::inorderHelper(std::shared_ptr<Node<T>> node) {
    if (node != NIL) {
        inorderHelper(node->left);
        std::cout << node->data << "(" << (node->color == RED ? "RED" : "BLACK") << ") ";
        inorderHelper(node->right);
    }
}

// Inorder traversal
template<typename T>
void RedBlackTree<T>::inorderTraversal() {
    inorderHelper(root);
    std::cout << std::endl;
}

// Example usage
int main() {
    RedBlackTree<int> rbt;
    
    // Insert elements
    std::cout << "Inserting elements: 10, 20, 30, 15, 5, 25, 18" << std::endl;
    rbt.insert(10);
    rbt.insert(20);
    rbt.insert(30);
    rbt.insert(15);
    rbt.insert(5);
    rbt.insert(25);
    rbt.insert(18);
    
    std::cout << "Inorder traversal: ";
    rbt.inorderTraversal();
    
    // Search for elements
    std::cout << "\nSearching for 15: " << (rbt.search(15)->data != 0 ? "Found" : "Not found") << std::endl;
    std::cout << "Searching for 100: " << (rbt.search(100) != rbt.getRoot() ? "Found" : "Not found") << std::endl;
    
    // Delete elements
    std::cout << "\nDeleting 20..." << std::endl;
    rbt.remove(20);
    std::cout << "Inorder traversal after deletion: ";
    rbt.inorderTraversal();
    
    return 0;
}
