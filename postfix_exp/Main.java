import java.util.Scanner;

class Node{
    int data;
    Node addr;

    Node(int val){
        data=val;
        addr=null;
    }
}

class Stack{
    Node top;

    Stack(){
        top=null;
    }

    void push(int val){
        Node newNode = new Node(val);
        newNode.addr = top;
        top=newNode;
    }

    int pop(){
        int val = top.data;
        top=top.addr;
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

    int evaluate(String exp){
        for(int i=0;i<exp.length();i++){
            char ch = exp.charAt(i);

            if(ch>='0' && ch<='9')
                push(ch-'0');

            else if(ch=='+' || ch=='-' || ch=='*' || ch=='/'){
                int b = pop();
                int a=pop();
                int res = apply(a,b,ch);
                push(res);
            }
        }
        return pop();
    }
}


public class Main{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Stack s = new Stack();
        String postfix = sc.next();
        System.out.println(s.evaluate(postfix));
    }
}
