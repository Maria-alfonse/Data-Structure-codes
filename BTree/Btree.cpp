#include <iostream>
using namespace std;

template <typename T, int Order>
class BTree {
private:
    struct Node {
        T * keys = new T[Order-1];
        Node ** children = new Node*[Order];
        int keyCount = 0;
        int pos = -1; //track the highest index
        Node() {
            for (int i = 0; i < Order; i++) {
                children[i] = nullptr;
            }
        }

        ~Node(){
            delete[] keys;
            for(int i= 0 ; i<Order ; i++){
                delete children[i];
            }
            delete[] children;
        }
    };


    Node *root;

    void print(Node* node, int level, string indent) const {
        if (!node) return;
        cout << indent;
        for (int i = 0; i < node->keyCount; i++) {
            cout << node->keys[i];
            if (i != node->keyCount - 1) cout << ",";
        }
        cout << endl;

        if (node->children[0] != nullptr) {
            for (int i = 0; i <= node->keyCount; i++) {
                print(node->children[i], level + 1, indent + "  ");
            }
        }
    }


    //split a full child node
    Node* splitChild(Node *node, T*value) {
        int keycount = node->keyCount;
        Node* newnode = new Node();

        int mid = keycount/ 2; // Middle index for splitting keys
        *value = node->keys[mid];

        for (int j = mid+1 ; j < keycount; j++) {
            newnode->pos ++;
            newnode->keys[newnode->pos] = node->keys[j];
            newnode->children[newnode->pos] = node->children[j];
            newnode->keyCount++;
            node->children[j] = nullptr;
        }

        newnode->children[newnode->pos+1] = node->children[keycount];
        node->children[keycount] = nullptr;

        node->keyCount = mid;
        node->pos = mid-1;
        return newnode;
    }

    int insertInNode(Node*node ,const T key) {

        if(node->children[0] == nullptr){ //if leaf insert direct at the end
            node->pos++;
            node->keys[node->pos] = key;
            node->keyCount++;

            //sort
            for(int i=node->pos; i>0 ; i--){ //iterate from the insertion pos(i.e end) to the right place
                if(node->keys[i]<node->keys[i-1]){
                    swap(node->keys[i], node->keys[i-1]);
                }
            }
        }
        else {
            int i=0;
            while(i<node->keyCount && key > node->keys[i]) { i++; }
            int check = insertInNode(node->children[i], key);
            if(check){
                T mid;
                Node* newNode = splitChild(node->children[i], &mid);
                for(int j = node->keyCount; j>i ;j--){
                    node->keys[j] = node->keys[j-1];
                }
                node->keys[i] = mid;
                node->keyCount++;
                node->pos++;
                for (int j = node->keyCount; j > i + 1; j--) {
                    node->children[j] = node->children[j - 1];
                }
                node->children[i+1] = newNode;
            }
        }
        return (node->keyCount == Order)? 1:0;
    }

public:
    BTree() : root(nullptr){};

    void Insert(T key){
        if(root == nullptr){
            root = new Node();
            root->pos++;
            root->keys[root->pos] = key;
            root->keyCount = 1;
        }else{
            int check = insertInNode(root, key);
            if(check){
                T mid;
                Node* spletted = splitChild(root, &mid);
                Node* newRoot = new Node();
                newRoot->pos++;
                newRoot->keys[newRoot->pos] = mid;
                newRoot->keyCount = 1;
                newRoot->children[0] = root;
                newRoot->children[1] = spletted;
                root = newRoot;
            }
        }
    };
    void Print() const {
        if (root != nullptr) {
            print(root, 1, "");
        } else {
            cout << "The Tree Is Empty\n";
        }
    }
};
int main() {
    BTree<int, 3> t1;
    t1.Insert(1);
    t1.Insert(5);
    t1.Insert(0);
    t1.Insert(4);
    t1.Insert(3);
    t1.Insert(2);
    t1.Print();


    BTree<char, 5> t;
    t.Insert('G');
    t.Insert('I');
    t.Insert('B');
    t.Insert('J');
    t.Insert('C');
    t.Insert('A');
    t.Insert('K');
    t.Insert('E');
    t.Insert('D');
    t.Insert('S');
    t.Insert('T');
    t.Insert('R');
    t.Insert('L');
    t.Insert('F');
    t.Insert('H');
    t.Insert('M');
    t.Insert('N');
    t.Insert('P');
    t.Insert('Q');
    t.Print();

    return 0;
}
