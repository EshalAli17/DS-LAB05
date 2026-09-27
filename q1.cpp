#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

int main() {
    stack<int> s;
    int n;

    cout << "Enter the number of elements: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Stack is empty." << endl;
        return 0;
    }

    cout << "Enter " << n << " elements (bottom to top): ";
    for (int i = 0; i < n; ++i) {
        int val;
        cin >> val;
        s.push(val);
    }

    int* elements = new int[n];
    stack<int> tempStack;

    for (int i = n - 1; i >= 0; --i) {
        int topVal = s.top();
        s.pop();
        elements[i] = topVal; 
        tempStack.push(topVal);
    }
    while (!tempStack.empty()) {
        s.push(tempStack.top());
        tempStack.pop();
    }

    int minVal = elements[0];
    int maxVal = elements[0];
    for (int i = 0; i < n; ++i) {
        if (elements[i] < minVal) minVal = elements[i];
        if (elements[i] > maxVal) maxVal = elements[i];
    }

    cout << "Maximum Value: " << maxVal << endl;
    cout << "Minimum Value: " << minVal << endl;

    if (n % 2 != 0) {
        cout << "Middle Element: " << elements[n / 2] << endl;
    } else {
        cout << "Middle Elements (Even size): " 
             << elements[(n / 2) - 1] << " and " << elements[n / 2] 
             << " (Average: " << (elements[(n / 2) - 1] + elements[n / 2]) / 2.0 << ")" << endl;
    }

    delete[] elements;
    return 0;
}
