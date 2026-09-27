#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <cctype>

using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

string infixToPostfix(const string& infix) {
    stack<char> s;
    string postfix = "";

    for (size_t i = 0; i < infix.length(); ++i) {
        char c = infix[i];
        if (isspace(c)) continue;

        if (isalnum(c) || c == '?' || c == 'a' || c == 'ß' || c == '±' || c == 'v') {
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
        } else if (isOperator(c)) {
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

string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    for (size_t i = 0; i < infix.length(); ++i) {
        if (infix[i] == '(') infix[i] = ')';
        else if (infix[i] == ')') infix[i] = '(';
    }

    string postfix = infixToPostfix(infix);
    reverse(postfix.begin(), postfix.end());
    
    if (!postfix.empty() && postfix[0] == ' ') {
        postfix.erase(postfix.begin());
    }
    return postfix;
}

void processExpression(const string& name, const string& rhsInfix) {
    cout << "\n=== " << name << " ===" << endl;
    cout << "RHS Infix  : " << rhsInfix << endl;
    cout << "RHS Postfix: " << infixToPostfix(rhsInfix) << endl;
    cout << "RHS Prefix : " << infixToPrefix(rhsInfix) << endl;
}

int main() {
    processExpression("1. Double-Angle Formula (RHS)", "± v ( ( 1 - cos? ) / ( 1 + cos? ) )");
    processExpression("2. Pythagorean Identity (RHS)", "1 - ( cos? ^ 2 )");
    processExpression("3. Product-to-Sum Identity (RHS)", "( 1 / 2 ) * ( cos(a-ß) - cos(a+ß) )");

    return 0;
}
