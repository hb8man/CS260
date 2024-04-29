#include <queue>
#include <iostream>

struct Node {
    int data;
    Node* next;

    Node(int d) : data(d), next(nullptr) {}
};

class LinkedQueue {
public:
    Node* front;  
    Node* rear; 

    LinkedQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(int newData) {
        Node* newNode = new Node(newData);
        if (rear == nullptr) {
            front = rear = newNode; 
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    int deQueue() {
        if (front == nullptr) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = front;
        int data = front->data;
        front = front->next;
        if (front == nullptr) {
            rear = nullptr;
        }
        delete temp;
        return data;
    }

    int peek() {
        if (!front) {
            throw std::runtime_error("Queue is empty");
        }
        return front->data;
    }
};

int main() {
    LinkedQueue q;
    q.enqueue(9);
    q.enqueue(2);
    q.enqueue(6);
    q.enqueue(4);
    q.deQueue();
    q.deQueue();
    q.deQueue();

    std::cout << "Front: " << q.peek() << std::endl;
}