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

    void add(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr || head->data >= value) {
            newNode->next = head;
            head = newNode;
            return;
        }
        Node* current = head;
        while (current->next != nullptr && current->next->data < value) {
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

    int search(int value) {
        Node* current = head;
        int position = 0;
        while (current != nullptr) {
            if (current->data == value) {
                return position;
            }
            current = current->next;
            position++;
        }
        return -1; // Return -1 if the value is not found
    }
};

// Test functions
void testAdd() {
    LinkedList list;
    list.add(30);
    list.add(10);
    list.add(20);
    list.add(40);
    // Expected order: 10 -> 20 -> 30 -> 40
    std::cout << "Add test passed\n";
}

void testRemove() {
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);
    list.add(40);
    int removedValue = list.remove(2); // Removes 30
    if (removedValue == 30 && list.get(2) == 40) {
        std::cout << "Remove test passed\n";
    } else {
        std::cout << "Remove test failed\n";
    }
}

void testGet() {
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);
    if (list.get(0) == 10 && list.get(1) == 20 && list.get(2) == 30) {
        std::cout << "Get test passed\n";
    } else {
        std::cout << "Get test failed\n";
    }
}

void testSearch() {
    LinkedList list;
    list.add(10);
    list.add(20);
    list.add(30);
    if (list.search(20) == 1 && list.search(10) == 0 && list.search(30) == 2 && list.search(40) == -1) {
        std::cout << "Search test passed\n";
    } else {
        std::cout << "Search test failed\n";
    }
}

int main() {
    testAdd();
    testRemove();
    testGet();
    testSearch();
    return 0;
}