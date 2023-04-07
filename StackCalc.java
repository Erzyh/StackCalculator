import java.util.Stack;
import java.util.Scanner;

public class StackCalc {

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("중위 수식을 입력하세요: ");
        String infix = sc.nextLine();

        String postfix = infixToPostfix(infix);
        System.out.println("후위 수식: " + postfix);

        int result = evaluatePostfix(postfix);
        System.out.println("결과: " + result);
        
        sc.close();
    }

    // 중위 수식을 후위 수식으로 변환하는 메서드
    public static String infixToPostfix(String infix) {
        String postfix = "";
        Stack<Character> stack = new Stack<>();
        for (int i = 0; i < infix.length(); i++) {
            char c = infix.charAt(i);
            if (Character.isDigit(c)) {
                postfix += c;
            } else if (c == '(') {
                stack.push(c);
            } else if (c == ')') {
                while (!stack.isEmpty() && stack.peek() != '(') {
                    postfix += stack.pop();
                }
                stack.pop();
            } else {
                while (!stack.isEmpty() && precedence(c) <= precedence(stack.peek())) {
                    postfix += stack.pop();
                }
                stack.push(c);
            }
        }
        while (!stack.isEmpty()) {
            postfix += stack.pop();
        }
        return postfix;
    }

    // 후위 수식을 계산하는 메서드
    public static int evaluatePostfix(String postfix) {
        Stack<Integer> stack = new Stack<>();
        for (int i = 0; i < postfix.length(); i++) {
            char c = postfix.charAt(i);
            if (Character.isDigit(c)) {
                stack.push(c - '0');
            } else {
                int operand2 = stack.pop();
                int operand1 = stack.pop();
                int result = 0;
                switch (c) {
                    case '+':
                        result = operand1 + operand2;
                        break;
                    case '-':
                        result = operand1 - operand2;
                        break;
                    case '*':
                        result = operand1 * operand2;
                        break;
                    case '/':
                        result = operand1 / operand2;
                        break;
                }
                stack.push(result);
            }
        }
        return stack.pop();
    }

    // 연산자 우선순위를 반환하는 메서드
    public static int precedence(char operator) {
        switch (operator) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
            default:
                return -1;
        }
    }
}
