#include <iostream>

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
public:
    TreeNode(T value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T, typename Compare>
class BinarySearchTree {
    TreeNode<T>* root;
    Compare comp;
public:
    BinarySearchTree() {
        root = nullptr;
    }

    void add(T value) {
        TreeNode<T>* newNode = new TreeNode<T>(value);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        TreeNode<T>* current = root;
        TreeNode<T>* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (comp(value, current->data)) {
                current = current->left;
            }
            else if (comp(current->data, value)) {
                current = current->right;
            }
            else {
                delete newNode;
                return;
            }
        }
        if (comp(value, parent->data)) {
            parent->left = newNode;
        }
        else {
            parent->right = newNode;
        }
    }

    // Helper function to find the minimum value node in a subtree
    TreeNode<T>* findAddressMin(TreeNode<T>* node) {
        if (node == nullptr) {
            return nullptr;
        }
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode<T>* findAddressMin() {
        return findAddressMin(root);
    }

    T findMin() {
        TreeNode<T>* addressMin = findAddressMin();
        return addressMin->data;
    }

    // Helper function to remove a node recursively
    TreeNode<T>* removeNode(TreeNode<T>* node, T value) {
        // Base case: if node is null, return null
        if (node == nullptr) {
            return nullptr;
        }

        // Recursively search for the node to delete
        if (comp(value, node->data)) {
            node->left = removeNode(node->left, value);
        }
        else if (comp(node->data, value)) {
            node->right = removeNode(node->right, value);
        }
        else {
            // Node found - handle the three cases

            // Case 1: Leaf node
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: Node with one child
            else if (node->left == nullptr) {
                TreeNode<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                TreeNode<T>* temp = node->left;
                delete node;
                return temp;
            }
            // Case 3: Node with two children
            else {
                // Find inorder successor (smallest value in right subtree)
                TreeNode<T>* successor = findAddressMin(node->right);
                // Copy successor data to current node
                node->data = successor->data;
                // Delete the successor
                node->right = removeNode(node->right, successor->data);
            }
        }
        return node;
    }

    // Public remove function
    void remove(T value) {
        root = removeNode(root, value);
    }

    TreeNode<T>* search(TreeNode<T>* node, T value) {
        if (node == nullptr || (!comp(value, node->data) && !comp(node->data, value))) {
            return node;
        }
        if (comp(value, node->data)) {
            return search(node->left, value);
        }
        else {
            return search(node->right, value);
        }
    }

    TreeNode<T>* search(T value) {
        return search(root, value);
    }

    void printInorder(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        printInorder(node->left);
        std::cout << node->data << " ";
        printInorder(node->right);
    }

    void printInorder() {
        printInorder(root);
    }

    void printPreorder(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        std::cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }

    void printPreorder() {
        printPreorder(root);
    }

    void printPostorder(TreeNode<T>* node) {
        if (node == nullptr) {
            return;
        }
        printPostorder(node->left);
        printPostorder(node->right);
        std::cout << node->data << " ";
    }

    void printPostorder() {
        printPostorder(root);
    }
};
