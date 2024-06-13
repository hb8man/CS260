#include <iostream>
#include <queue>

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    void add(int value) {
        Node** cur = &root;
        while (*cur) {
            Node& node = **cur;
            if (value <= node.value)
                cur = &node.left;
            else
                cur = &node.right;
        }
        *cur = new Node(value);
        std::cout << "New node: " << value << std::endl;
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }

    Node* removeRecursive(Node* node, int value) {
        if (!node) return node;
        if (value < node->value)
            node->left = removeRecursive(node->left, value);
        else if (value > node->value)
            node->right = removeRecursive(node->right, value);
        else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->value = temp->value;
            node->right = removeRecursive(node->right, temp->value);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) current = current->left;
        return current;
    }

    void inOrderTraversal(Node* node) {
        if (node) {
            inOrderTraversal(node->left);
            std::cout << node->value << " ";
            inOrderTraversal(node->right);
        }
    }


    ~BST() {
        clear(root);
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

int main() {
    BST tree;
    tree.add(10);
    tree.add(5);
    tree.add(15);
    tree.add(11);
    tree.add(9);
    tree.add(1);
    std::cout << "In order Traversal: ";
    tree.inOrderTraversal(tree.root);
    std::cout << std::endl;
    return 0;
}
