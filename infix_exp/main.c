#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* addr;
};

struct CharNode{
    char data;
    struct CharNode* addr;
};

struct Node* valTop = NULL;
struct CharNode* opTop = NULL;

void pushVal(int x){
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->addr = valTop;
    valTop = newNode;
}

int popVal(){
    if(valTop==NULL) 
        return -1;

    int val = valTop->data;
    valTop = valTop->addr;
    return val;
}

void pushOp(char ch) {
    struct CharNode* newNode = malloc(sizeof(struct CharNode));
    newNode->data = ch;
    newNode->addr = opTop;
    opTop = newNode;
}

char popOp() {
    if (opTop == NULL) 
        return '\0';

    char val = opTop->data;
    opTop = opTop->addr;
    return val;
}

int precedence(char op){
    if (op=='+'||op=='-') 
        return 1;
    if (op=='*'||op=='/') 
        return 2;
    return 0;
}

int applyOp(int a,int b,char op) {
    if (op=='+')
        return a+b;
    if (op=='-')
        return a-b;
    if (op=='*')
        return a*b;
    return a/b;
}

int evaluate(char exp[]){

    for (int i=0;exp[i]!='\0';i++){

        char ch = exp[i];

        if(ch>='0' && ch<='9'){
            pushVal(ch - '0');
        }

        else if (ch=='('){
            pushOp(ch);
        }

        else if (ch==')'){

            while (opTop != NULL && opTop->data!='('){

                int val2 = popVal();
                int val1 = popVal();
                char op = popOp();

                pushVal(applyOp(val1,val2,op));
            }
            popOp();
        }

        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){

            while(opTop != NULL && precedence(opTop->data) >= precedence(ch)){

                int val2 = popVal();
                int val1 = popVal();
                char op = popOp();

                pushVal(applyOp(val1,val2,op));
            }
            pushOp(ch);
        }
    }

    while(opTop != NULL){

        int val2 = popVal();
        int val1 = popVal();
        char op = popOp();

        pushVal(applyOp(val1,val2,op));
    }
    return popVal();
}

int main(){
    char infix[100];
    scanf("%s",infix);
    printf("%d",evaluate(infix));
    return 0;
}