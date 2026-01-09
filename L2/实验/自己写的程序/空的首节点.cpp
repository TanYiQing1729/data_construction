#include <iostream>
using namespace std;

// 定义链表结点
struct Node {
    int data;
    Node* next;
    Node(int val = 0) : data(val), next(nullptr) {}
};

// 带头结点的链表插入操作
void insert(Node* head, int pos, int val) {
    Node* p = head;
    // 找到插入位置的前驱结点
    for (int i = 0; i < pos; ++i) {
        if (p->next == nullptr && i != pos - 1) {
            cout << "插入位置超出链表长度！" << endl;
            return;
        }
        p = p->next;
    }
    Node* newNode = new Node(val);
    newNode->next = p->next;
    p->next = newNode;
}

void printList(Node* head) {
    Node* p = head->next; // 跳过头结点
    while (p) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main() {
    Node* head = new Node(); // 创建头结点
    // 插入元素
    insert(head, 0, 10); // 在第0个位置插入10
    insert(head, 1, 20); // 在第1个位置插入20
    insert(head, 1, 15); // 在第1个位置插入15
    printList(head); // 输出：10 15 20
    return 0;
}