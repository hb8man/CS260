#include <iostream>
#include <stdexcept>

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void add(int value, int position) {
        Node* newNode = new Node(value);
        if (position == 0) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* current = head;
        for (int i = 0; i < position - 1; ++i) {
            if (current == nullptr) {
                throw std::out_of_range("Position out of range");
            }
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }

    int remove(int position) {
        if (head == nullptr) {
            throw std::out_of_range("Position out of range");
        }
        if (position == 0) {
            Node* temp = head;
            head = head->next;
            int value = temp->data;
            delete temp;
            return value;
        }
        Node* current = head;
        for (int i = 0; i < position - 1; ++i) {
            if (current->next == nullptr) {
                throw std::out_of_range("Position out of range");
            }
            current = current->next;
        }
        Node* temp = current->next;
        current->next = temp->next;
        int value = temp->data;
        delete temp;
        return value;
    }

    int get(int position) {
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            if (current == nullptr) {
                throw std::out_of_range("Position out of range");
            }
            current = current->next;
        }
        return current->data;
    }
};

// Test functions
void testAdd() {
    LinkedList list;
    list.add(10, 0);
    list.add(20, 1);
    list.add(30, 1);
    std::cout << "Add test passed\n";
}

void testRemove() {
    LinkedList list;
    list.add(10, 0);
    list.add(20, 1);
    list.add(30, 1);
    int removedValue = list.remove(1);
    if (removedValue == 30 && list.get(1) == 20) {
        std::cout << "Remove test passed\n";
    } else {
        std::cout << "Remove test failed\n";
    }
}

void testGet() {
    LinkedList list;
    list.add(10, 0);
    list.add(20, 1);
    list.add(30, 1);
    if (list.get(0) == 10 && list.get(1) == 30 && list.get(2) == 20) {
        std::cout << "Get test passed\n";
    } else {
        std::cout << "Get test failed\n";
    }
}

int main() {
    testAdd();
    testRemove();
    testGet();
    return 0;
}
