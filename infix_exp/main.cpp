#include <iostream>
#include <string>
using namespace std;

class Node{
public:
    int data;
    Node* addr;

    Node(int val){
        data = val;
        addr = nullptr;
    }
};

class CharNode{
public:
    char data;
    CharNode* addr;

    CharNode(char val){
        data = val;
        addr = nullptr;
    }
};

class Stack{
public:
    Node* top;

    Stack(){
        top = nullptr;
    }

    void push(int val){
        Node* newNode = new Node(val);
        newNode->addr = top;
        top = newNode;
    }

    int pop(){
        if(top == nullptr)
            return -1;

        int val = top->data;
        top = top->addr;
        return val;
    }
};

class CharStack{
public:
    CharNode* top;

    CharStack(){
        top = nullptr;
    }

    void push(char val){
        CharNode* newNode = new CharNode(val);
        newNode->addr = top;
        top = newNode;
    }

    char pop(){
        if(top == nullptr)
            return '\0';

        char val = top->data;
        top = top->addr;
        return val;
    }
};

int precedence(char op){
    if(op=='+'||op=='-')
        return 1;
    if(op=='*'||op=='/')
        return 2;
    return 0;
}

int applyOp(int a,int b,char op){
    if(op=='+')
        return a+b;
    if(op=='-')
        return a-b;
    if(op=='*')
        return a*b;
    return a/b;
}

int evaluate(string exp){

    Stack val;
    CharStack ops;

    for(int i=0;i<exp.length();i++){

        char ch = exp[i];

        if(ch>='0' && ch<='9')
            val.push(ch-'0');

        else if(ch=='(')
            ops.push(ch);

        else if(ch==')'){

            while(ops.top!=nullptr && ops.top->data!='('){

                int val2 = val.pop();
                int val1 = val.pop();

                char op = ops.pop();

                val.push(applyOp(val1,val2,op));
            }
            ops.pop();
        }

        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){

            while(ops.top!=nullptr && precedence(ops.top->data)>=precedence(ch)){

                int val2 = val.pop();
                int val1 = val.pop();

                char op = ops.pop();

                val.push(applyOp(val1,val2,op));
            }
            ops.push(ch);
        }
    }

    while(ops.top!=nullptr){

        int val2 = val.pop();
        int val1 = val.pop();
        char op = ops.pop();

        val.push(applyOp(val1,val2,op));
    }
    return val.pop();
}

int main(){
    string infix;
    cin >> infix;
    cout << evaluate(infix);
}