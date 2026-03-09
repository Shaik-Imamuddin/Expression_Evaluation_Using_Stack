import java.util.Scanner;

class Node{
    int data;
    Node addr;

    Node(int val){
        data=val;
        addr=null;
    }
}

class CharNode{
    char data;
    CharNode addr;

    CharNode(char val){
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
        top = newNode;
    }

    int pop(){

        if(top==null)
            return -1;

        int val = top.data;
        top=top.addr;
        return val;
    }
}

class CharStack{
    CharNode top;

    CharStack(){
        top=null;
    }

    void push(char val){
        CharNode newNode = new CharNode(val);
        newNode.addr = top;
        top = newNode;
    }

    char pop(){

        if(top==null)
            return '\0';

        char val = top.data;
        top=top.addr;
        return val;
    }
}

public class Main{

    static int precedence(char op){
        if(op=='+'||op=='-')
            return 1;
        if(op=='*'||op=='/')
            return 2;
        return 0;
    }

    static int applyOp(int a,int b,char op){
        if(op=='+')
            return a+b;
        if(op=='-')
            return a-b;
        if(op=='*')
            return a*b;
        return a/b;
    }

    static int evaluate(String exp){
        Stack val = new Stack();
        CharStack ops = new CharStack();

        for(int i=0;i<exp.length();i++){
            char ch = exp.charAt(i);
    
            if(ch>='0' && ch<='9')
                val.push(ch-'0');

            else if(ch=='(')
                ops.push(ch);

            else if(ch==')'){
                while(ops.top!=null && ops.top.data!='('){
                    
                    int val2=val.pop();
                    int val1=val.pop();

                    char op = ops.pop();
                    val.push(applyOp(val1,val2,op));
                }
                ops.pop();
            }

            else if(ch=='+'||ch=='-'||ch=='*'||ch=='/'){
                while(ops.top!=null && precedence(ops.top.data)>=precedence(ch)){
                    int val2 = val.pop();
                    int val1 = val.pop();

                    char op = ops.pop();

                    val.push(applyOp(val1,val2,op));
                }
                ops.push(ch);
            }
        }
        while(ops.top!=null){
            int val2 = val.pop();
            int val1 = val.pop();

            char op = ops.pop();

            val.push(applyOp(val1,val2,op));
        }
        return val.pop();
    }

    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        String infix = sc.next();
        System.out.println(evaluate(infix));
    }
}