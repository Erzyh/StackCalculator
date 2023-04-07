class Stack:
    def __init__(self):
        self.items = []
        
    def is_empty(self):
        return len(self.items) == 0
    
    def push(self, item):
        self.items.append(item)
        
    def pop(self):
        if self.is_empty():
            return None
        return self.items.pop()
    
    def top(self):
        if self.is_empty():
            return None
        return self.items[-1]
    
    def size(self):
        return len(self.items)

def is_operator(char):
    return char in "+-*/"

def precedence(operator):
    if operator in "+-":
        return 1
    elif operator in "*/":
        return 2
    else:
        return 0

def infix_to_postfix(infix_expression):
    operator_stack = Stack()
    postfix_expression = []
    for char in infix_expression:
        if char.isdigit():
            postfix_expression.append(char)
        elif is_operator(char):
            while (not operator_stack.is_empty()) and precedence(char) <= precedence(operator_stack.top()):
                postfix_expression.append(operator_stack.pop())
            operator_stack.push(char)
        elif char == "(":
            operator_stack.push(char)
        elif char == ")":
            while operator_stack.top() != "(":
                postfix_expression.append(operator_stack.pop())
            operator_stack.pop()
    while not operator_stack.is_empty():
        postfix_expression.append(operator_stack.pop())
    return " ".join(postfix_expression)

def evaluate_postfix(postfix_expression):
    operand_stack = Stack()
    for char in postfix_expression:
        if char.isdigit():
            operand_stack.push(char)
        elif is_operator(char):
            operand2 = operand_stack.pop()
            operand1 = operand_stack.pop()
            result = evaluate(operand1, operand2, char)
            operand_stack.push(result)
    return operand_stack.pop()

def evaluate(operand1, operand2, operator):
    operand1 = int(operand1)
    operand2 = int(operand2)
    if operator == "+":
        return str(operand1 + operand2)
    elif operator == "-":
        return str(operand1 - operand2)
    elif operator == "*":
        return str(operand1 * operand2)
    elif operator == "/":
        return str(operand1 / operand2)

if __name__ == "__main__":
    infix_expression = input("중위 수식을 입력하세요: ")
    postfix_expression = infix_to_postfix(infix_expression)
    result = evaluate_postfix(postfix_expression)

    print("후위 수식: ", postfix_expression)
    print("결과: ", result)
