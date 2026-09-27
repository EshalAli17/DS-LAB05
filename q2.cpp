#include <iostream>
#include <algorithm>
#include <cstddef> // i used for NULL 

using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(NULL) {}
};

class LinkedStack {
private:
    Node* topNode;
    int count;
public:
    LinkedStack() : topNode(NULL), count(0) {}

    void push(int val) {
        Node* newNode = new Node(val);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    int pop() {
        if (isEmpty()) return -1;
        Node* temp = topNode;
        int val = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return val;
    }

    bool isEmpty() const {
        return topNode == NULL;
    }

    int size() const {
        return count;
    }

    void getBottomToTopArray(int arr[]) const {
        Node* curr = topNode;
        int idx = count - 1;
        while (curr) {
            arr[idx--] = curr->data;
            curr = curr->next;
        }
    }

    ~LinkedStack() {
        while (!isEmpty()) pop();
    }
};

class CircularQueue {
private:
    int* arr;
    int front, rear, capacity, count;
public:
    CircularQueue(int cap) : capacity(cap), front(0), rear(-1), count(0) {
        arr = new int[capacity];
    }

    void enqueue(int val) {
        if (count == capacity) return;
        rear = (rear + 1) % capacity;
        arr[rear] = val;
        count++;
    }

    void display() const {
        cout << "Circular Queue Elements: ";
        for (int i = 0; i < count; ++i) {
            cout << arr[(front + i) % capacity] << " ";
        }
        cout << endl;
    }

    ~CircularQueue() {
        delete[] arr;
    }
};

int main() {
    int n1, n2;
    cout << "Enter size of Stack 1: ";
    cin >> n1;
    int* arr1 = new int[n1];
    cout << "Enter Stack 1 elements (bottom to top): ";
    for (int i = 0; i < n1; ++i) cin >> arr1[i];

    cout << "Enter size of Stack 2: ";
    cin >> n2;
    int* arr2 = new int[n2];
    cout << "Enter Stack 2 elements (bottom to top): ";
    for (int i = 0; i < n2; ++i) cin >> arr2[i];

    LinkedStack stack3;
    int i = 0, j = 0;
    while (i < n1 || j < n2) {
        if (i < n1) stack3.push(arr1[i++]);
        if (j < n2) stack3.push(arr2[j++]);
    }

    int totalSize = stack3.size();
    int* thirdArray = new int[totalSize];
    stack3.getBottomToTopArray(thirdArray);

    cout << "\nInterleaved Stack (Bottom to Top): ";
    for (int k = 0; k < totalSize; ++k) cout << thirdArray[k] << " ";
    cout << endl;

    sort(thirdArray, thirdArray + totalSize);

    cout << "Sorted Stack Elements: ";
    for (int k = 0; k < totalSize; ++k) cout << thirdArray[k] << " ";
    cout << endl;

    CircularQueue cq(totalSize);
    for (int k = 0; k < totalSize; ++k) {
        cq.enqueue(thirdArray[k]);
    }

    cq.display();

    delete[] arr1;
    delete[] arr2;
    delete[] thirdArray;

    return 0;
}
