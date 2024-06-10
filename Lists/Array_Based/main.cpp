#include <iostream>
#include <cassert>
using namespace std;
template<class T>
class ArrayList{
protected:
    T * list;
    int length, maxSize;
public:
    ArrayList(int size){
        if(size<0){
            cout<<"wrong :)\n Size set to 100";
            maxSize = 100;
        }else{
            maxSize = size;
        }
        length = 0;
        list = new T[maxSize];
        assert(list != NULL);  //This line checks that the new operation was successful in allocating memory for the list.
        //If list is NULL, it means memory allocation failed, and assert will cause the program to abort, preventing further execution with a potentially invalid pointer.
    }

    ArrayList(const ArrayList<T>& other){
        maxSize = other.maxSize;
        length = other.length;
        list = new T[maxSize];
        assert(list!=NULL);
        for(int i=0 ; i<length ;i++){
            list[i] = other.list[i];
        }
    }

    virtual ArrayList<T>& operator=(const ArrayList<T>& other){
        if(this!=other){
            delete [] list;
            maxSize = other.maxSize;
            length = other.length;
            list = new T[maxSize];
            assert(list!=NULL);
            for(int i=0 ; i<length ;i++){
                list[i] = other.list[i];
            }
        }
        return *this;
    }

    virtual bool isEmpty()const {
        return (length==0);
    }

    virtual bool isFull()const{
        return (maxSize==length);
    }

    virtual int listSize()const{
        return length;
    }

    virtual int maxListSize()const{
        return maxSize;
    }

    virtual void print()const{
        for(int i=0; i<length;i++){
            cout<<list[i]<<' ';
        }cout<<endl;
    }

    virtual bool isItemAtEqual(int index, const T& item) const{
        return (list[index] == item);
    }

    virtual void insertAt(int index, const T& item){
        if(index<0||index>=maxSize){
            cout<<"Out of range";
            return;
        }
        if(length>=maxSize){
            cout<<"List is Full";
            return;
        }
        for (int i = length; i > index; i--) {
            list[i] = list[i-1];
        }
        list[index] = item;
        length++;
    }

    virtual void removeAt(int index){
        if(index<0||index>=length){
            cout<<"Out of range";
            return;
        }
        for(int i=index ; i<length-1 ;i++){
            list[i] = list[i+1];
        }
        length--;
    }

    virtual void retrieveAt(int index,  T& item){
        if(index<0||index>=length){
            cout<<"Out of range";
            return;
        }
        item = list[index];
    }

    virtual void replaceAt(int index, const T& item){
        if(index<0||index>=length){
            cout<<"Out of range";
            return;
        }
        list[index] = item;
    }

    virtual void clearList(){
        length = 0;
    }

    virtual int seqSearch(const T& item)const{
        for(int i=0 ; i<length ; i++){
            if(list[i]==item){
                return i;
            }
        }
        return -1; // Return -1 if item is not found
    }

    virtual void pushFront(const T& item){
        insertAt(0,item);
    }

    virtual void popFront(){
        removeAt(0);
    }

    virtual void pushBack(const T& item){
        if(length>=maxSize){
            cout<<"List is Full";
            return;
        }
        list[length] = item;
        length++;
    }

    virtual void popBack(){
        length--;
    }

    virtual void remove(const T& item){
        if(length == 0){
            cout<<"List is empty\n";
            return;
        }
        int i = seqSearch(item);
        if(i != -1){
            removeAt(i);
        }else{
            cout<<"Item is not in the list\n";
        }
    }

    virtual ~ArrayList(){
        delete [] list;
    }

};

