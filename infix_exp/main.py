class Node:
    def __init__(self,val):
        self.data = val
        self.addr = None


class Stack:
    def __init__(self):
        self.top = None

    def push(self,val):
        newNode = Node(val)
        newNode.addr = self.top
        self.top = newNode

    def pop(self):
        val = self.top.data
        self.top = self.top.addr
        return val

def precedence(op):
    if op=='+' or op=='-':
        return 1
    if op=='*' or op=='/':
        return 2
    return 0


def apply(a,b,op):
    if op=='+':
        return a+b
    if op=='-':
        return a-b
    if op=='*':
        return a*b
    return a//b


def evaluate(exp):

    val = Stack()
    ops = Stack()

    for ch in exp:

        if ch>='0' and ch<='9':
            val.push(ord(ch)-ord('0'))

        elif ch=='(':
            ops.push(ch)

        elif ch==')':

            while ops.peek()!='(':
                b = val.pop()
                a = val.pop()
                op = ops.pop()

                val.push(apply(a,b,op))

            ops.pop()

        elif ch in "+-*/":

            while ops.top!=None and precedence(ops.top.data)>=precedence(ch):

                b = val.pop()
                a = val.pop()
                op = ops.pop()

                val.push(apply(a,b,op))

            ops.push(ch)

    while ops.top!=None:

        b = val.pop()
        a = val.pop()
        op = ops.pop()

        val.push(apply(a,b,op))

    return val.pop()


exp = input()
print(evaluate(exp))