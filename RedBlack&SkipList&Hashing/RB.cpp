
#include <iostream>
using namespace std;

enum Color { RED, BLACK };

struct RBNode {
    int data;
    Color color;
    RBNode *left, *right, *parent;

    RBNode(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    RBNode *root;
    RBNode *nile = new RBNode(0);

    void rotateLeft(RBNode *&node) {
        RBNode *temp = node->right;
        node->right = temp->left;

        if (temp->left != nullptr)
            temp->left->parent = node;

        temp->parent = node->parent;

        if (node->parent == nullptr)
            root = temp;
        else if (node == node->parent->left)
            node->parent->left = temp;
        else
            node->parent->right = temp;

        temp->left = node;
        node->parent = temp;
    }

    void rotateRight(RBNode *&node) {
        RBNode *temp = node->left;
        node->left = temp->right;

        if (temp->right != nullptr)
            temp->right->parent = node;

        temp->parent = node->parent;

        if (node->parent == nullptr)
            root = temp;
        else if (node == node->parent->right)
            node->parent->right = temp;
        else
            node->parent->left = temp;

        temp->right = node;
        node->parent = temp;
    }

    void fixInsertion(RBNode *&node) {
        RBNode *parent = nullptr;
        RBNode *grandparent = nullptr;

        while (node != root && node->color == RED && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;

            if (parent == grandparent->left) {
                RBNode *uncle = grandparent->right;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                RBNode *uncle = grandparent->left;

                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        root->color = BLACK;
    }

    void fixDeletion(RBNode *&node) {
        while (node != root && (node == nullptr || node->color == BLACK)) {
            if (node == node->parent->left) {
                RBNode *sibling = node->parent->right;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->right == nullptr || sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->right != nullptr)
                        sibling->right->color = BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                RBNode *sibling = node->parent->left;

                if (sibling->color == RED) {
                    sibling->color = BLACK;
                    node->parent->color = RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }

                if ((sibling->left == nullptr || sibling->left->color == BLACK) &&
                    (sibling->right == nullptr || sibling->right->color == BLACK)) {
                    sibling->color = RED;
                    node = node->parent;
                } else {
                    if (sibling->left == nullptr || sibling->left->color == BLACK) {
                        sibling->right->color = BLACK;
                        sibling->color = RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = BLACK;
                    if (sibling->left != nullptr)
                        sibling->left->color = BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }
        if (node != nullptr)
            node->color = BLACK;
    }

    void transplant(RBNode *u, RBNode *v) {
        if (u->parent == nullptr)
            root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;

        if (v != nullptr)
            v->parent = u->parent;
    }

    RBNode* minimum(RBNode *node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

public:
    RedBlackTree() : root(nullptr) {}

    void insert(int data) {
        RBNode *node = new RBNode(data);
        RBNode *parent = nullptr;
        RBNode *current = root;

        while (current != nullptr) {
            parent = current;
            if (node->data < current->data)
                current = current->left;
            else
                current = current->right;
        }

        node->parent = parent;

        if (parent == nullptr)
            root = node;
        else if (node->data < parent->data)
            parent->left = node;
        else
            parent->right = node;

        fixInsertion(node);
    }

    void deleteNode(int data) {
        RBNode *node = root;
        RBNode *z = nullptr;
        RBNode *x, *y;

        while (node != nullptr) {
            if (node->data == data) {
                z = node;
                break;
            }

            if (data < node->data)
                node = node->left;
            else
                node = node->right;
        }

        if (z == nullptr)
            return;

        y = z;
        Color yOriginalColor = y->color;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;

            if (y->parent == z && x!= nullptr)
                x->parent = y;
            else if(y->parent == z && x== nullptr){
                x = nile;
            }
            else{
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == BLACK)
            fixDeletion(x);
    }

    void inorder() {
        inorderHelper(root);
        cout << endl;
    }

    void inorderHelper(RBNode *node) {
        if (node == nullptr)
            return;

        inorderHelper(node->left);
        cout << "("<<node->data << ", "<<node->color<<") " ;
        inorderHelper(node->right);
    }
};


int main() {
    RedBlackTree tree;

    tree.insert(60);
    tree.insert(40);
    tree.insert(70);
    tree.insert(20);

    tree.insert(50);

    tree.insert(65);

    tree.insert(80);
    tree.insert(15);
    tree.insert(25);

    cout << "Inorder traversal after insertion: ";
    tree.inorder();

    tree.deleteNode(50);
    cout << "Inorder traversal after deletion of 20: ";
    tree.inorder();

//
//    tree.deleteNode(10);
//    cout << "Inorder traversal after deletion of 10: ";
//    tree.inorder();

}
