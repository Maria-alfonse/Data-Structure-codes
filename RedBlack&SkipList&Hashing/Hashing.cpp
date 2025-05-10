#include <bits/stdc++.h>
using namespace std;
struct Node {
    int key;
    Node* next;
    Node(int k) : key(k), next(nullptr) {}
};
class Hashing{
private :
    vector<Node*> Chainedhash;
    vector<int> hash;
    int size;
public:
    Hashing(int s) : size(s) {
        Chainedhash.resize(size, nullptr);
        hash.resize(size, -1);
    }

    int divisionMethod(int key) {
        return key % size;
    }

    double multiplicationConstant = 0.6180339887;
    int multiplicationMethod(int key) {
        double fractionalPart = fmod(key * multiplicationConstant, 1);
        return (int)(fractionalPart * size);
    }

    int midSquareMethod(int key) {
        int square = key * key;
        int middle = (square / 100) % 100;
        return middle % size;
    }
    void clear(){
    fill(hash.begin(), hash.end(), -1);
        for (int i = 0; i < size; i++) {
            Node* current = Chainedhash[i];
            while (current) {
                Node* temp = current;
                current = current->next;
                delete temp;  // Free the allocated memory for nodes
            }
            Chainedhash[i] = nullptr;  // Reset the pointer to nullptr
        }
    }
    int foldingMethod(int key) {
        string keyStr = to_string(key);
        int sum = 0;
        for (size_t i = 0; i < keyStr.length(); i += 2) {
            string part = keyStr.substr(i, 2);
            sum += stoi(part);
        }
        return sum % size;
    }

    void chainingMethod(int key) {
        int index = divisionMethod(key);
        Node* newNode = new Node(key);
        newNode->next = Chainedhash[index];
        Chainedhash[index] = newNode;
    }

    int openAddressingMethod(int key) {
        int index = divisionMethod(key);
        int originalIndex = index;
        while (hash[index] != -1) {
            index = (index + 1) % size;
            if (index == originalIndex) return -1;
        }
        hash[index] = key;
        return index;
    }

    int doubleHashing(int key) {
        int hash1 = divisionMethod(key);
        int PRIME = 7;
        int hash2 = PRIME - (key % PRIME);
        int originalIndex = hash1;
        for (int i = 0; i < size; i++) {
            int index = (hash1 + i * hash2) % size;
            if (hash[index] == -1) {
                hash[index] = key;
                return index;
            }
            if (index == originalIndex && i !=0) break;
        }

        return -1;
    }
    void insert(int key, string method) {
        if (method == "division") {
            int index = divisionMethod(key);
            hash[index] = key;
            cout << "Inserted " << key << " using Division Method at index " << index << endl;
        } else if (method == "multiplication") {
            int index = multiplicationMethod(key);
            hash[index] = key;
            cout << "Inserted " << key << " using Multiplication Method at index " << index << endl;
        } else if (method == "midSquare") {
            int index = midSquareMethod(key);
            hash[index] = key;
            cout << "Inserted " << key << " using Mid Square Method at index " << index << endl;
        } else if (method == "folding") {
            int index = foldingMethod(key);
            hash[index] = key;
            cout << "Inserted " << key << " using Folding Method at index " << index << endl;
        } else if (method == "chaining") {
            chainingMethod(key);
            cout << "Inserted " << key << " using Chaining Method." << endl;
        } else if (method == "openAddressing") {
            int index = openAddressingMethod(key);
            if (index != -1)
                cout << "Inserted " << key << " using Open Addressing at index " << index << endl;
            else
                cout << "Failed to insert " << key << " using Open Addressing (table is full)" << endl;
        } else if (method == "doubleHashing") {
            int index = doubleHashing(key);
            if (index != -1)
                cout << "Inserted " << key << " using Double Hashing at index " << index << endl;
            else
                cout << "Failed to insert " << key << " using Double Hashing (table is full)" << endl;
        } else {
            cout << "Invalid method." << endl;
        }
    }


    void printChaining() {
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            Node* current = Chainedhash[i];
            while (current) {
                cout << current->key << " -> ";
                current = current->next;
            }
            cout << "NULL" << endl;
        }
    }
    void resize(int s){
        size = s;
    }

    void printHash() {
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": " << (hash[i] == -1 ? "EMPTY" : to_string(hash[i])) << endl;
        }
    }
};

int main() {
    int tableSize = 11;
    Hashing hashing(tableSize);

    int key = 123;
    hashing.insert(key,"division") ;
    hashing.insert(key,"multiplication");
    hashing.insert(key,"midSquare");
    hashing.insert(12345,"folding");
    hashing.clear();
    hashing.resize(10);
    cout << "\nChaining Method:" << endl;
    hashing.insert(123,"chaining");
    hashing.insert(133,"chaining");
    hashing.insert(143,"chaining");
    hashing.printChaining();

    hashing.resize(11);
    cout << "\nOpen Addressing Method:" << endl;
    hashing.insert(36,"openAddressing");
    hashing.insert(7,"openAddressing");
    hashing.insert(18,"openAddressing");
    hashing.insert(62,"openAddressing");
    hashing.insert(51,"openAddressing");
    hashing.printHash();
    hashing.clear();
    hashing.resize(10);

    cout << "\nDouble Hashing Method:" << endl;
    hashing.insert(37,"doubleHashing");
    hashing.insert(90,"doubleHashing");
    hashing.insert(45,"doubleHashing");
    hashing.insert(22,"doubleHashing");
    hashing.insert(17,"doubleHashing");
    hashing.insert(49,"doubleHashing");
    hashing.insert(55,"doubleHashing");
    hashing.printHash();
    hashing.clear();
    string method;


    while (true) {
        int s;
        cout<<"\nEnter size of hash table:";
        cin>>s;
        hashing.resize(s);
        cout << "\nEnter hashing method (division, multiplication, midSquare, folding, chaining, openAddressing, doubleHashing) or 'exit' to quit: ";
        cin >> method;

        if (method == "exit") {
            break;
        }

        cout << "Enter key to insert: ";
        cin >> key;

        hashing.insert(key, method);
    }

    cout << "\nHash Table after Insertions:" << endl;
    hashing.printHash();

    cout << "\nChaining Table after Insertions:" << endl;
    hashing.printChaining();


    return 0;
}
