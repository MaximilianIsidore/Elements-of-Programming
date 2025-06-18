#include <iostream>
#include <algorithm>

using namespace std;

template <typename Type>
class node {
public:
    Type data;
    node* left{nullptr};
    node* right{nullptr};
    size_t height{1};

    node(Type data) : data(data) {}
};

template <typename Type>
class AVL_Tree {
private:
    node<Type>* root{nullptr};

    node<Type>* insert(Type data, node<Type>* _root) {
        if (_root == nullptr) {
            return new node<Type>(data);
        }

        if (data < _root->data)
            _root->left = insert(data, _root->left);
        else if (data > _root->data)
            _root->right = insert(data, _root->right);
        else
            return _root;  // Duplicate, do nothing

        _root->height = 1 + max(get_height(_root->left), get_height(_root->right));

        int balance = get_balanceFactor(_root);

        // Left Left Case
        if (balance > 1 && data < _root->left->data)
            return rightRotate(_root);

        // Right Right Case
        if (balance < -1 && data > _root->right->data)
            return leftRotate(_root);

        // Left Right Case
        if (balance > 1 && data > _root->left->data) {
            _root->left = leftRotate(_root->left);
            return rightRotate(_root);
        }

        // Right Left Case
        if (balance < -1 && data < _root->right->data) {
            _root->right = rightRotate(_root->right);
            return leftRotate(_root);
        }

        return _root;
    }

    size_t get_height(node<Type>* _root) {
        return _root ? _root->height : 0;
    }

    int get_balanceFactor(node<Type>* _root) {
        return _root ? get_height(_root->left) - get_height(_root->right) : 0;
    }

    node<Type>* leftRotate(node<Type>* z) {
        node<Type>* y = z->right;
        node<Type>* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = 1 + max(get_height(z->left), get_height(z->right));
        y->height = 1 + max(get_height(y->left), get_height(y->right));

        return y;
    }

    node<Type>* rightRotate(node<Type>* y) {
        node<Type>* x = y->left;
        node<Type>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(get_height(y->left), get_height(y->right));
        x->height = 1 + max(get_height(x->left), get_height(x->right));

        return x;
    }

    void inorder(node<Type>* _root) {
        if (!_root) return;
        inorder(_root->left);
        cout << _root->data << " " <<"height: " << _root->height<<"\n";
        inorder(_root->right);
    }

    node<Type>* deleteNode(node<Type>* _root, Type data) {
        if (!_root) return nullptr;

        // Step 1: Regular BST delete
        if (data < _root->data)
            _root->left = deleteNode(_root->left, data);
        else if (data > _root->data)
            _root->right = deleteNode(_root->right, data);
        else {
            // Node with one or no child
            if (!_root->left || !_root->right) {
                node<Type>* temp = _root->left ? _root->left : _root->right;
                delete _root;
                return temp;
            }

            // Node with two children: get inorder successor
            node<Type>* temp = getMinValueNode(_root->right);
            _root->data = temp->data;
            _root->right = deleteNode(_root->right, temp->data);
        }

        // Step 2: Update height
        _root->height = 1 + max(get_height(_root->left), get_height(_root->right));

        // Step 3: Balance
        int balance = get_balanceFactor(_root);

        // Left Left
        if (balance > 1 && get_balanceFactor(_root->left) >= 0)
            return rightRotate(_root);

        // Left Right
        if (balance > 1 && get_balanceFactor(_root->left) < 0) {
            _root->left = leftRotate(_root->left);
            return rightRotate(_root);
        }

        // Right Right
        if (balance < -1 && get_balanceFactor(_root->right) <= 0)
            return leftRotate(_root);

        // Right Left
        if (balance < -1 && get_balanceFactor(_root->right) > 0) {
            _root->right = rightRotate(_root->right);
            return leftRotate(_root);
        }

        return _root;
    }

    node<Type>* getMinValueNode(node<Type>* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    node<Type>* search(node<Type>* _root, Type data) {
        if (_root == nullptr || _root->data == data)
            return _root;

        if (data < _root->data)
            return search(_root->left, data);
        else
            return search(_root->right, data);
    }

    

    

public:
    void insert(Type data) {
        root = insert(data, root);
    }

    void remove(Type data) {
        root = deleteNode(root, data);
    }

    bool contains(Type data) {
        return search(root, data) != nullptr;
    }


    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVL_Tree<int> tree;
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    tree.insert(25);
    tree.insert(40);
    tree.insert(50);

    tree.display();  // Output: 10 20 25 30 40 50

    tree.remove(30);
    tree.display();  // Output should be balanced after deletion

    cout << (tree.contains(25) ? "Found" : "Not Found") << endl;
    cout << (tree.contains(30) ? "Found" : "Not Found") << endl;

    return 0;
}
