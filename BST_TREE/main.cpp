#include <vector>
#include <iostream>
#include <queue>
using namespace std;

template<class T>
class BST_Node {
public:
    T value;
    BST_Node* left;
    BST_Node* right;

    BST_Node() {
        left = NULL;
        right = NULL;
    }
    BST_Node(const T& type, BST_Node* l = NULL, BST_Node* r = NULL) {
        value = type;
        left = l;
        right = r;
    }
};

template<class T>
class BST {
protected:
    BST_Node<T>* root;
public:
    BST() {
        root = NULL;
    }
    BST(const BST_Node<T>& r) {
        root = &r;
    }
    void clear() {
        root = NULL;
    }
    bool isEmpty() {
        return root == NULL;
    }

    // Complexity = path length to the node + 1
    T* search(T& el) {
        BST_Node<T>* p = root;
        while (p != NULL) {
            if (el == p->value) {
                return &p->value;
            }
            else if (el < p->value) {
                p = p->left;
            }
            else {
                p = p->right;
            }
        }
        return 0;
    }

    void Add(T item) {
        BST_Node<T>* now = root, * prev = NULL;
        while (now != NULL) {
            prev = now;
            if (now->value > item) {
                now = now->left;
            }
            else {
                now = now->right;
            }
        }
        if (root == NULL) {
            root = new BST_Node<T>(item);
        }
        else if (prev->value > item) {
            prev->left = new BST_Node<T>(item);
        }
        else {
            prev->right = new BST_Node<T>(item);
        }
    }

    void Ascending_Order(BST_Node<T>* node) {
        if (node != nullptr) {
            Ascending_Order(node->left);
            cout << node->value << ' ';
            Ascending_Order(node->right);
        }
    }
    void Ascending() {
        Ascending_Order(root);
        cout << endl;
    }

    void Descending_Order(BST_Node<T>* node) {
        if (node != nullptr) {
            Descending_Order(node->right);
            cout << node->value << ' ';
            Descending_Order(node->left);
        }
    }
    void Descending() {
        Descending_Order(root);
        cout << endl;
    }

    void Remove_item(T& r) {
        BST_Node<T>* now = root;
        BST_Node<T>* parent = NULL;

        while (now != NULL && now->value != r) {
            parent = now;
            if (r < now->value) {
                now = now->left;
            }
            else {
                now = now->right;
            }
        }

        if (now == NULL) {
            cout << "Item not found\n";
            return;
        }

        if (now->left == NULL && now->right == NULL) {
            if (parent == NULL) {
                root = NULL;
            }
            else if (parent->left == now) {
                parent->left = NULL;
            }
            else {
                parent->right = NULL;
            }
            delete now;
            return;
        }

        if (now->left != NULL && now->right == NULL) {
            if (parent == NULL) {
                root = now->left;
            }
            else if (parent->left == now) {
                parent->left = now->left;
            }
            else {
                parent->right = now->left;
            }
            delete now;
            return;
        }
        else if (now->right != NULL && now->left == NULL) {
            if (parent == NULL) {
                root = now->right;
            }
            else if (parent->left == now) {
                parent->left = now->right;
            }
            else {
                parent->right = now->right;
            }
            delete now;
            return;
        }

        BST_Node<T>* minitem = now->right;
        BST_Node<T>* miniParent = now;
        while (minitem->left != NULL) {
            miniParent = minitem;
            minitem = minitem->left;
        }

        now->value = minitem->value;

        if (miniParent->left == minitem) {
            miniParent->left = minitem->right;
        }
        else {
            miniParent->right = minitem->right;
        }
        delete minitem;
    }

    void Breadth_First() {
        if (root == NULL) {
            cout << "The tree is empty." << endl; // Debugging print
            return;
        }

        queue<BST_Node<T>*> queue;
        queue.push(root);

        while (!queue.empty()) {
            BST_Node<T>* p = queue.front();
            queue.pop();
            cout << p->value << ' ';

            if (p->left != NULL) {
                queue.push(p->left);
            }
            if (p->right != NULL) {
                queue.push(p->right);
            }
        }
        cout << endl;
    }

    void Preorder_Depth_First(BST_Node<T>* p){
        if(p!=NULL){
            cout<<p->value<<' ';
            Preorder_Depth_First(p->left);
            Preorder_Depth_First(p->right);
        }
    }
    void Postorder_Depth_First(BST_Node<T>* p){
        if(p!=NULL){
            Postorder_Depth_First(p->left);
            Postorder_Depth_First(p->right);
            cout<<p->value<<' ';
        }
    }
    void Depth_First(){
        cout<<"Inorder: Ascending order\n";
        Ascending_Order(root);
        cout<<endl;

        cout<<"Preorder: parent then one child \n";
        Preorder_Depth_First(root);
        cout<<endl;

        cout<<"Postorder: childern the parant last root\n";
        Postorder_Depth_First(root);
        cout<<endl;
    }
};

int main() {
    BST<int> tree;
    tree.Add(13);
    tree.Add(10);
    tree.Add(25);
    tree.Add(2);
    tree.Add(12);
    tree.Add(31);
    tree.Add(20);
    tree.Add(29);

    cout << "Breadth-First Traversal: " << endl;
    tree.Breadth_First();

    cout << "Depth-First Traversal: " << endl;
    tree.Depth_First();


    return 0;
}
