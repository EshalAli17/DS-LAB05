#include <iostream>
#include <string>
#include <stack>
#include <sstream> 

using namespace std;

string intToString(int num) {
    stringstream ss;
    ss << num;
    return ss.str();
}

int main() {
    int n;
    cout << "Enter the number of terms n: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Invalid n." << endl;
        return 0;
    }

    int totalTokens = 2 * n - 1;
    string* infixTokens = new string[totalTokens];
    string seriesStr = "";

    int tokenIdx = 0;
    for (int i = 1; i <= n; ++i) {
        int term = 3 * i - 2;
        string termStr = intToString(term);
        infixTokens[tokenIdx++] = termStr;
        seriesStr += termStr;

        if (i < n) {
            infixTokens[tokenIdx++] = "+";
            seriesStr += " + ";
        }
    }

    string* postfixTokens = new string[totalTokens];
    int postfixIdx = 0;
    stack<string> opStack;

    for (int i = 0; i < totalTokens; ++i) {
        string token = infixTokens[i];
        if (token == "+") {
            while (!opStack.empty()) {
                postfixTokens[postfixIdx++] = opStack.top();
                opStack.pop();
            }
            opStack.push(token);
        } else {
            postfixTokens[postfixIdx++] = token;
        }
    }
    while (!opStack.empty()) {
        postfixTokens[postfixIdx++] = opStack.top();
        opStack.pop();
    }

    string* prefixTokens = new string[totalTokens];
    int prefixIdx = 0;
    stack<string> prefixOpStack;
    stack<string> valStack;

    for (int i = totalTokens - 1; i >= 0; --i) {
        if (infixTokens[i] == "+") {
            prefixOpStack.push("+");
        } else {
            valStack.push(infixTokens[i]);
        }
    }

    while (!prefixOpStack.empty()) {
        prefixTokens[prefixIdx++] = prefixOpStack.top();
        prefixOpStack.pop();
    }
    while (!valStack.empty()) {
        prefixTokens[prefixIdx++] = valStack.top();
        valStack.pop();
    }

    cout << "\nSeries: " << seriesStr << endl;

    cout << "Postfix: ";
    for (int i = 0; i < totalTokens; ++i) cout << postfixTokens[i] << " ";
    cout << endl;

    cout << "Prefix: ";
    for (int i = 0; i < totalTokens; ++i) cout << prefixTokens[i] << " ";
    cout << endl;

    delete[] infixTokens;
    delete[] postfixTokens;
    delete[] prefixTokens;

    return 0;
}
