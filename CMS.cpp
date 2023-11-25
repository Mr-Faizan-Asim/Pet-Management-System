#include <iostream>

class Cat {
public:
    int id;
    std::string name;

    Cat(int _id, const std::string& _name) : id(_id), name(_name) {}
};

class Node {
public:
    Cat cat;
    Node* left;
    Node* right;

    Node(const Cat& _cat) : cat(_cat), left(nullptr), right(nullptr) {}
};

class CatsManagementSystem {
private:
    Node* root;

    // Helper functions
    Node* insert(Node* node, const Cat& cat);
    Node* findMin(Node* node);
    Node* remove(Node* node, int id);
    void printInOrder(Node* node);

public:
    CatsManagementSystem() : root(nullptr) {}

    // CRUD operations
    void addCat(int id, const std::string& name);
    void removeCat(int id);
    void displayCats();
};

// Insert a cat into the tree
Node* CatsManagementSystem::insert(Node* node, const Cat& cat) {
    if (node == nullptr) {
        return new Node(cat);
    }

    if (cat.id < node->cat.id) {
        node->left = insert(node->left, cat);
    } else if (cat.id > node->cat.id) {
        node->right = insert(node->right, cat);
    }

    return node;
}

// Find the node with the minimum value in a subtree
Node* CatsManagementSystem::findMin(Node* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

// Remove a cat from the tree
Node* CatsManagementSystem::remove(Node* node, int id) {
    if (node == nullptr) {
        return nullptr;
    }

    if (id < node->cat.id) {
        node->left = remove(node->left, id);
    } else if (id > node->cat.id) {
        node->right = remove(node->right, id);
    } else {
        // Node with only one child or no child
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children, get the inorder successor (smallest in the right subtree)
        Node* temp = findMin(node->right);

        // Copy the inorder successor's data to this node
        node->cat = temp->cat;

        // Delete the inorder successor
        node->right = remove(node->right, temp->cat.id);
    }

    return node;
}

// Display cats in ascending order of their IDs
void CatsManagementSystem::printInOrder(Node* node) {
    if (node != nullptr) {
        printInOrder(node->left);
        std::cout << "ID: " << node->cat.id << ", Name: " << node->cat.name << std::endl;
        printInOrder(node->right);
    }
}

// Public method to add a cat
void CatsManagementSystem::addCat(int id, const std::string& name) {
    Cat newCat(id, name);
    root = insert(root, newCat);
}

// Public method to remove a cat
void CatsManagementSystem::removeCat(int id) {
    root = remove(root, id);
}

// Public method to display all cats
void CatsManagementSystem::displayCats() {
    printInOrder(root);
}

int main() {
    CatsManagementSystem catsSystem;

    catsSystem.addCat(3, "Whiskers");
    catsSystem.addCat(1, "Fluffy");
    catsSystem.addCat(5, "Mittens");
    catsSystem.addCat(2, "Shadow");
    catsSystem.addCat(4, "Oreo");

    std::cout << "All Cats:" << std::endl;
    catsSystem.displayCats();

    catsSystem.removeCat(2);
    std::cout << "\nAfter removing cat with ID 2:" << std::endl;
    catsSystem.displayCats();

    return 0;
}
