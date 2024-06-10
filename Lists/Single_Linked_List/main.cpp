#include <iostream>
using namespace std;

template<class T>
struct nodeType {
    T info;
    nodeType<T> *link;
};

template<class T>
class Single_Linked_List{ //Queue Like FIF access
protected:
    int count;
    nodeType<T>* head;
    nodeType<T>* tail;

public:
    Single_Linked_List<T>(){
        count=0;
        head=NULL;
        tail=NULL;
    };

    virtual bool isEmpty()const{
        return (count==0);
    };

    virtual int length()const{
        return count;
    };

    virtual void print()const{
        nodeType<T>*current = head;
        while(current!=NULL){
            cout<<current->info<<" ";
            current = current->link;
        }
        cout<<endl;
    };

    //Backward
    virtual void pushFront(T info){
        nodeType<T>* newNode = new nodeType<T>(); //newNode saves the address of the nodetype element
        newNode->info = info; //sets the nodetype data
        newNode->link = head;
        head = newNode;
        tail = newNode;
        count++;
    };

    //Forward
    virtual void pushPack(T info){
        nodeType<T>* newNode = new nodeType<T>(); //newNode saves the address of the nodetype element
        newNode->info = info; //sets the nodetype data
        newNode->link = NULL;
        if(head == NULL){
            pushFront(info);
            return;
        }else{
            tail->link = newNode;
            tail = newNode;
            count++;
        }
    };

    virtual void popFront(){
        count--;
        nodeType<T>*front = head;
        head = head->link;
        delete front;
    }

    virtual void popBack(){
        if(head==NULL){
            return;
        }else if(head==tail){
            delete head; //or tail
            head = NULL;
            tail = NULL;
            count--;
        }else {
            nodeType<T> *current = head;
            while (current->link != tail) {
                current = current->link;
            }
            nodeType<T> *Back = tail;
            tail = current;
            tail->link = NULL;
            delete Back;
            count--;
        }

    }

    virtual void insert(int index, T& info){
        if (index < 0 || index > count)
            throw std::out_of_range("Index out of range");
        if (index == 0) {
            pushFront(info);
            return;
        }

        nodeType<T>*newNode = new nodeType<T>();
        newNode->info = info;

        nodeType<T>*current = head;
        /*for(int i=1 ; i<index; i++){
            current = current->link;
        }
        newNode->link = current->link;
        current->link = newNode;
         */
        nodeType<T>*prev = NULL;
        for(int i=0 ; i<index ;i++){
            prev = current;
            current = current->link;
        }
        prev->link = newNode;
        newNode->link = current;

        if(newNode->link==NULL){
            tail = newNode;
        }
        count++;
    }

    virtual void remove(int index){
        if (index < 0 || index > count)
            throw std::out_of_range("Index out of range");
        if (index == 0) {
            popFront();
            return;
        }
        nodeType<T>*current = head, *prev = NULL;
        for(int i=0 ; i<index ;i++){
            prev = current;
            current = current->link;
        }
        prev->link = current->link;
        delete current;
        if(prev->link == NULL){
            tail=prev;
        }
       /* for(int i=1 ; i<index; i++){
            current = current->link;
        }
        nodeType<T>*temp=current->link;
        current->link = current->link->link;
        delete temp;*/

        count--;
    }

    virtual void clear(){
        while (head != NULL){
            popFront();
        }
    }

    virtual ~Single_Linked_List(){
        clear();
    }
};

template<class T>
class Ordered_Single_Linked_List: public Single_Linked_List<T>{

};

template <typename T>
class CircularLinkedList {
private:
    nodeType<T>* head;
    size_t size;

public:
    CircularLinkedList() : head(nullptr), size(0) {}

    ~CircularLinkedList() {
        if (head != nullptr) {
            nodeType<T>* current = head;
            do {
                nodeType<T>* nextNode = current->next;
                delete current;
                current = nextNode;
            } while (current != head);
        }
    }

    // Function to insert a new node at the beginning of the list
    void pushFront(const T& newData) {
        if (head == nullptr) {
            head = new nodeType<T>(newData);
            head->next = head; // Point back to itself to form a loop
        } else {
            head = new nodeType<T>(newData, head);
            nodeType<T>* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = head; // Update last node to point back to the new head
        }
        size++;
    }

    // Function to remove the node at the front of the list
    void popFront() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        nodeType<T>* temp = head;
        if (head->next == head) { // Only one node in the list
            head = nullptr;
        } else {
            nodeType<T>* current = head;
            while (current->next != head) {
                current = current->next;
            }
            head = head->next;
            current->next = head; // Update last node to point to the new head
        }
        delete temp;
        size--;
    }

    // Function to get the size of the list
    size_t getSize() const {
        return size;
    }

    // Function to check if the list is empty
    bool isEmpty() const {
        return size == 0;
    }
};

template <typename T>
struct Node {
    T data;
    Node* prev;
    Node* next;

    Node(const T& newData, Node* newPrev = nullptr, Node* newNext = nullptr)
            : data(newData), prev(newPrev), next(newNext) {}
};

template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    size_t size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Function to insert a new node at the beginning of the list
    void pushFront(const T& newData) {
        Node<T>* newNode = new Node<T>(newData, nullptr, head);
        if (head != nullptr) {
            head->prev = newNode;
        } else {
            tail = newNode;
        }
        head = newNode;
        size++;
    }

    // Function to insert a new node at the end of the list
    void pushBack(const T& newData) {
        Node<T>* newNode = new Node<T>(newData, tail, nullptr);
        if (tail != nullptr) {
            tail->next = newNode;
        } else {
            head = newNode;
        }
        tail = newNode;
        size++;
    }

    // Function to remove the node at the front of the list
    void popFront() {
        if (head == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }

    // Function to remove the node at the end of the list
    void popBack() {
        if (tail == nullptr) {
            throw std::out_of_range("List is empty");
        }
        Node<T>* temp = tail;
        tail = tail->prev;
        if (tail != nullptr) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }

    // Function to get the size of the list
    size_t getSize() const {
        return size;
    }

    // Function to check if the list is empty
    bool isEmpty() const {
        return size == 0;
    }
};


int main() {


    return 0;
}
