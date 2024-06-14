#include <iostream>
#include <vector>

struct Node {
    int key;
    Node* next;

    Node(int key) : key(key), next(nullptr) {}
};


class HashTable {
private:
    std::vector<Node*> table;
    int capacity;  // Number of "buckets" in hash table

    int hashFunction(int key) {
        return key % capacity;
    }

public:
    // Constructor
    HashTable(int size) : capacity(size) {
        table.resize(capacity, nullptr);
    }

    // Destructor to clean memory
    ~HashTable() {
        for (int i = 0; i < capacity; ++i) {
            Node* entry = table[i];
            while (entry != nullptr) {
                Node* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }

    // Insert key into hash table
    void insert(int key) {
        int index = hashFunction(key);
        Node* newNode = new Node(key);

        // Insert new node at beginning of list
        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index] = newNode;
        }
    }

    // Check if key exists in hash table
    bool contains(int key) {
        int index = hashFunction(key);
        Node* entry = table[index];

        while (entry != nullptr) {
            if (entry->key == key) {
                return true;
            }
            entry = entry->next;
        }

        return false;
    }

    // Delete key from hash table and return its value
    int deleteKey(int key) {
        int index = hashFunction(key);
        Node* entry = table[index];
        Node* prev = nullptr;

        while (entry != nullptr) {
            if (entry->key == key) {
                if (prev == nullptr) {
                    table[index] = entry->next;  // Remove first node
                } else {
                    prev->next = entry->next;  // Remove node not at start
                }
                int retKey = entry->key;
                delete entry;
                return retKey;
            }
            prev = entry;
            entry = entry->next;
        }

        return -1;  // Key not found
    }

    // Display the hash table
    void display() {
        for (int i = 0; i < capacity; ++i) {
            Node* entry = table[i];
            std::cout << "[" << i << "]:";
            while (entry != nullptr) {
                std::cout << " -> " << entry->key;
                entry = entry->next;
            }
            std::cout << std::endl;
        }
    }
};


int main() {
    HashTable ht(10);  // Create a hash table of size 10

    // Insert values
    ht.insert(12);
    ht.insert(22);
    ht.insert(34);
    ht.insert(320);
    ht.insert(42);
    ht.insert(54);
    ht.insert(2);  // This will cause a collision at index 2

    // Display the hash table
    ht.display();

    // Check if a key is present
    std::cout << "Contains 22: " << ht.contains(22) << std::endl;

    // Delete a key and display the result
    std::cout << "Deleted Key: " << ht.deleteKey(12) << std::endl;

    // Display the hash table after deletion
    ht.display();

    return 0;
}
