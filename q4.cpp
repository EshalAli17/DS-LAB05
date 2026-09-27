#include <iostream>
#include <string>
#include <stack>
#include <cctype>
#include <cmath>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

string toPostfix(const string& infix) {
    string postfix = "";
    stack<char> s;

    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        if (isspace(c)) continue;

        if (isalnum(c)) {
            postfix += c;
            postfix += ' ';
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }
            if (!s.empty()) s.pop();
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                postfix += ' ';
                s.pop();
            }
            s.push(c);
        }
    }

    while (!s.empty()) {
        postfix += s.top();
        postfix += ' ';
        s.pop();
    }
    return postfix;
}

double evaluatePostfix(const string& postfix, double xVal) {
    stack<double> s;

    for (size_t i = 0; i < postfix.length(); ++i) {
        if (isspace(postfix[i])) continue;

        if (postfix[i] == 'x' || postfix[i] == 'X') {
            s.push(xVal);
        } else if (isdigit(postfix[i])) {
            double num = 0;
            while (i < postfix.length() && isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }
            i--;
            s.push(num);
        } else {
            double val2 = s.top(); s.pop();
            double val1 = s.top(); s.pop();

            switch (postfix[i]) {
                case '+': s.push(val1 + val2); break;
                case '-': s.push(val1 - val2); break;
                case '*': s.push(val1 * val2); break;
                case '/': s.push(val1 / val2); break;
                case '^': s.push(pow(val1, val2)); break;
            }
        }
    }
    return s.top();
}

int main() {
    string expr1, cond1, expr2, cond2;
    double x;

    cout << "Enter Expression 1: ";
    getline(cin, expr1);
    cout << "Enter Condition 1 (e.g., x >= 0): ";
    getline(cin, cond1);

    cout << "Enter Expression 2: ";
    getline(cin, expr2);
    cout << "Enter Condition 2 (e.g., x < 0): ";
    getline(cin, cond2);

    cout << "Enter x: ";
    cin >> x;

    string selectedExpr, selectedCond;
    if (x >= 0) {
        selectedExpr = expr1;
        selectedCond = cond1;
    } else {
        selectedExpr = expr2;
        selectedCond = cond2;
    }

    string postfix = toPostfix(selectedExpr);
    double result = evaluatePostfix(postfix, x);

    cout << "\nOutput :\nThe program selects:\n";
    cout << "Condition: " << selectedCond << "\n";
    cout << "Expression: " << selectedExpr << "\n";
    cout << "Postfix Expression: " << postfix << "\n";
    cout << "Calculated Value f(" << x << ") = " << result << endl;

    return 0;
}
