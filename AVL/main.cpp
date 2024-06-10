#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class AVLNode {
public:
    T data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template<typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    int height(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalance(AVLNode<T>* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    AVLNode<T>* rotateRight(AVLNode<T>* y) {
        AVLNode<T>* x = y->left;
        AVLNode<T>* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    AVLNode<T>* rotateLeft(AVLNode<T>* y) {
        AVLNode<T>* x = y->right;
        AVLNode<T>* T2 = x->left;

        x->left = y;
        y->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    AVLNode<T>* insertNode(AVLNode<T>* node, T key) {
        if (node == nullptr) return new AVLNode<T>(key);
        if (key < node->data) node->left = insertNode(node->left, key);
        else if (key > node->data) node->right = insertNode(node->right, key);
        else return node; // Duplicate keys are not allowed
        // Update height of this node
        node->height = 1 + max(height(node->left), height(node->right));
        // Get balance factor of this node to check if it became unbalanced
        int balance = getBalance(node);
        // If node becomes unbalanced, there are 4 cases:
        template<typename T>
        AVLNode<T>* insertNode(AVLNode<T>* node, T key) {
            if (node == nullptr)
                return new AVLNode<T>(key);

            if (key < node->data)
                node->left = insertNode(node->left, key);
            else if (key > node->data)
                node->right = insertNode(node->right, key);
            else
                return node; // Duplicate keys are not allowed

            node->height = 1 + max(height(node->left), height(node->right));

            int balance = getBalance(node);

            if (balance > 1) {
                // Left Left Case
                if (key < node->left->data) {
                    return rotateRight(node);
                }
                // Left Right Case
                if (key > node->left->data) {
                    node->left = rotateLeft(node->left);
                    return rotateRight(node);
                }
            } else if (balance < -1) {
                // Right Right Case
                if (key > node->right->data) {
                    return rotateLeft(node);
                }
                // Right Left Case
                if (key < node->right->data) {
                    node->right = rotateRight(node->right);
                    return rotateLeft(node);
                }
            }

            return node;
        }

        return node;
    }

    AVLNode<T>* minValueNode(AVLNode<T>* node) {
        AVLNode<T>* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    AVLNode<T>* deleteNode(AVLNode<T>* root, T key) {
        if (root == nullptr)
            return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                AVLNode<T>* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp; // Copy the contents of the non-empty child
                delete temp;
            } else {
                AVLNode<T>* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr)
            return root;

        // Update height of current node
        root->height = 1 + max(height(root->left), height(root->right));

        // Get balance factor of this node to check if it became unbalanced
        int balance = getBalance(root);

        // If node becomes unbalanced, there are 4 cases:


        // Left Left Case
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right Case
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right Case
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left Case
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorderTraversal(AVLNode<T>* root) {
        if (root == nullptr)
            return;
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(T key) {
        root = insertNode(root, key);
    }

    void remove(T key) {
        root = deleteNode(root, key);
    }

    void inorder() {
        inorderTraversal(root);
        cout << endl;
    }
};

int main() {
    AVLTree<int> avl;
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);

    cout << "Inorder traversal of AVL tree after insertion: ";
    avl.inorder();

    avl.remove(20);

    cout << "Inorder traversal of AVL tree after removing 20: ";
    avl.inorder();

    return 0;
}
