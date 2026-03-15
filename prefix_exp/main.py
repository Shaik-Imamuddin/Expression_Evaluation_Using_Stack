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

    def apply(self,a,b,op):
        if op=='+':
            return a+b
        if op=='-':
            return a-b
        if op=='*':
            return a*b
        return a//b

    def evaluate(self,exp):
        for i in range(len(exp)-1,-1,-1):
            ch = exp[i]
            if ch>='0' and ch<='9':
                self.push(ord(ch)-ord('0'))

            elif ch in "+-*/":
                a = self.pop()
                b = self.pop()

                res = self.apply(a,b,ch)
                self.push(res)

        return self.pop()


s = Stack()
postfix = input()
print(s.evaluate(postfix))