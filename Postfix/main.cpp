#include <iostream>
#include <stack>
#include <string>
using namespace std;
void print_stack(stack<char>& print){
    stack<char>s = print;
    while (!s.empty()) {
        cout<<s.top()<<' ';
        s.pop();
    }
    cout<<endl;
}
void convert_to_postfix(string & line){
    string postfix ="";
    stack<char>operations;
    for(int i=0 ; i<line.size(); i++){
        if(isdigit(line[i])){
            while (i < line.size() && isdigit(line[i])) {
                postfix += line[i];
                i++;
            }
            postfix += ' ';  // Add space to separate numbers in the postfix expression
            i--; // Adjust for the increment in the outer for loop
            cout << "first if\n" << postfix << '\n';
            print_stack(operations);
        }else{
            if(operations.empty()){
                operations.push(line[i]);

                cout<<"second if\n"<<postfix<<'\n';
                print_stack(operations);
            }else{
                if(line[i] == '+' || line[i] == '-') {
                    while (!operations.empty() && (operations.top() == '*' || operations.top() == '/')) {
                        postfix += operations.top();
                        postfix +=" ";
                        operations.pop();
                    }
                    postfix += operations.top();
                    postfix +=" ";
                    operations.pop();

                    cout<<"third if\n"<<postfix<<'\n';
                    print_stack(operations);
                }
                operations.push(line[i]);

                cout<<"last one\n"<<postfix<<'\n';
                print_stack(operations);
            }
        }
    }
    while (!operations.empty()) {
        postfix += operations.top();
        postfix +=" ";
        operations.pop();
    }
    line = postfix;
}
int main() {
    string expression = "10+2*8-3";
    convert_to_postfix(expression);
    cout << "Postfix: " << expression << endl;
    return 0;
}
