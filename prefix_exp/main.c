#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node{
    int data;
    struct Node *addr;
};

struct Node *top = NULL;

void push(int val){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = val;

    newNode->addr = top;
    top = newNode;
}

int pop(){
    int val = top->data;
    struct Node *temp = top;
    top = top->addr;
    free(temp);
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

int evaluate(char exp[100]){
    int len = strlen(exp);
    for(int i=len-1;i>=0;i--){
        char ch = exp[i];
        
        if(ch>='0' && ch<='9')
            push(ch-'0');

        else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
            int a = pop();
            int b = pop();

            int res = apply(a,b,ch);
            push(res);
        }
    }
    return pop();
}

int main(){
    char prefix[100];
    scanf("%s",prefix);
    printf("%d",evaluate(prefix));
    return 0;
}