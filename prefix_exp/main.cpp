#include <iostream>
#include <string>
using namespace std;

class Node{
public:
    int data;
    Node* addr;

    Node(int val){
        data = val;
        addr = NULL;
    }
};

class Stack{
public:
    Node* top;

    Stack(){
        top = NULL;
    }

    void push(int val){
        Node* newNode = new Node(val);
        newNode->addr = top;
        top = newNode;
    }

    int pop(){
        int val = top->data;
        top = top->addr;
        return val;
    }

    int apply(int a,int b,char op){
        if(op=='+')
            return a+b;
        if(op=='-')
            return a-b;
        if(op=='*')
            return a*b;
        return a/b;
    }

    int evaluate(string exp){
        for(int i=exp.length();i>=0;i--){
            char ch = exp[i];

            if(ch>='0' && ch<='9')
                push(ch-'0');

            else if(ch=='+' || ch=='-' || ch=='*' || ch=='/'){
                int a = pop();
                int b = pop();
                int res = apply(a,b,ch);
                push(res);
            }
        }
        return pop();
    }
};

int main(){
    Stack s;
    string postfix;
    cin>>postfix;
    cout<<s.evaluate(postfix);
}