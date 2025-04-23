#include <iostream>
#include <queue>
#include <string>
using namespace std;

// Part A: B-Tree of order 3
class BTree {
private:
    struct BTreeNode {
        int keys[2];
        BTreeNode* children[3];
        int keyCount;
        bool leaf;
        BTreeNode(bool isLeaf) : keyCount(0), leaf(isLeaf) {
            for (int i = 0; i < 3; i++) children[i] = nullptr;
        }
    };
    BTreeNode* root;
    const int MIN_KEYS = 1;
    const int MAX_KEYS = 2;

    void insertNonFull(BTreeNode* node, int key) {
        int i = node->keyCount - 1;
        if (node->leaf) {
            while (i >= 0 && key < node->keys[i]) {
                node->keys[i + 1] = node->keys[i];
                i--;
            }
            node->keys[i + 1] = key;
            node->keyCount++;
        } else {
            while (i >= 0 && key < node->keys[i]) i--;
            i++;
            if (node->children[i]->keyCount == MAX_KEYS) {
                splitChild(node, i);
                if (key > node->keys[i]) i++;
            }
            insertNonFull(node->children[i], key);
        }
    }

    void splitChild(BTreeNode* parent, int childIndex) {
        BTreeNode* child = parent->children[childIndex];
        BTreeNode* newNode = new BTreeNode(child->leaf);
        newNode->keyCount = MIN_KEYS;
        newNode->keys[0] = child->keys[1]; // Right key to new node
        if (!child->leaf) {
            for (int j = 0; j <= MIN_KEYS; j++) {
                newNode->children[j] = child->children[j + MIN_KEYS];
            }
        }
        child->keyCount = MIN_KEYS;
        for (int j = parent->keyCount; j >= childIndex + 1; j--)
            parent->children[j + 1] = parent->children[j];
        parent->children[childIndex + 1] = newNode;
        for (int j = parent->keyCount - 1; j >= childIndex; j--)
            parent->keys[j + 1] = parent->keys[j];
        parent->keys[childIndex] = child->keys[1];

        parent->keyCount++;
    }

public:
    BTree() : root(nullptr) {}

    void insert(int key) {
        if (root == nullptr) {
            root = new BTreeNode(true);
            root->keys[0] = key;
            root->keyCount = 1;
        } else {
            if (root->keyCount == MAX_KEYS) {
                BTreeNode* newNode = new BTreeNode(false);
                newNode->children[0] = root;
                splitChild(newNode, 0);
                root = newNode;
            }
            insertNonFull(root, key);
        }
    }

    void levelOrderDisplay() {
        if (root == nullptr) return;
        queue<BTreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int levelSize = q.size();
            while (levelSize--) {
                BTreeNode* current = q.front();
                q.pop();
                cout << "[";
                for (int i = 0; i < current->keyCount; i++) {
                    cout << current->keys[i];
                    if (i != current->keyCount - 1) cout << " ";
                }
                cout << "] ";
                if (!current->leaf) {
                    for (int i = 0; i <= current->keyCount; i++) {
                        if (current->children[i])
                            q.push(current->children[i]);
                    }
                }
            }
            cout << endl;
        }
    }
};

// Part B: File System using Red-Black Tree
class FileSystem {
private:
    enum Color { RED, BLACK };
    struct Directory {
        string name;
        Directory* parent;
        Directory* left;
        Directory* right;
        Color color;
        Directory(string n) : name(n), parent(nullptr), left(nullptr),
        right(nullptr), color(RED) {}
    };
    Directory* root;

    void rotateLeft(Directory* x) {
        Directory* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Directory* x) {
        Directory* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void fixViolation(Directory* node) {
        Directory* parent = nullptr;
        Directory* grandparent = nullptr;
        while (node != root && node->color == RED && node->parent->color == RED) {
            parent = node->parent;
            grandparent = parent->parent;
            if (parent == grandparent->left) {
                Directory* uncle = grandparent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->right) {
                        rotateLeft(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateRight(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            } else {
                Directory* uncle = grandparent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    node = grandparent;
                } else {
                    if (node == parent->left) {
                        rotateRight(parent);
                        node = parent;
                        parent = node->parent;
                    }

                    rotateLeft(grandparent);
                    swap(parent->color, grandparent->color);
                    node = parent;
                }
            }
        }
        root->color = BLACK;
    }

    void inOrderTraversal(Directory* node) {
        if (node == nullptr) return;
        inOrderTraversal(node->left);
        cout << node->name << " ";
        inOrderTraversal(node->right);
    }

public:
    FileSystem() : root(nullptr) {}

    void addDirectory(const string& name) {
        Directory* newNode = new Directory(name);
        if (root == nullptr) {
            root = newNode;
            root->color = BLACK;
            return;
        }
        Directory* current = root;
        Directory* parent = nullptr;
        while (current != nullptr) {
            parent = current;
            if (name < current->name) current = current->left;
            else current = current->right;
        }
        newNode->parent = parent;
        if (name < parent->name) parent->left = newNode;
        else parent->right = newNode;
        fixViolation(newNode);
    }

    void displayStructure() {
        cout << "File System Structure (In-order): ";
        inOrderTraversal(root);
        cout << endl;
    }
};

int main() {
    // B-Tree operations
    BTree bTree;
    bTree.insert(10);
    bTree.insert(20);
    bTree.insert(5);
    bTree.insert(6);
    bTree.insert(15);
    bTree.insert(30);
    cout << "B-Tree Level Order Display:\n";
    bTree.levelOrderDisplay();

    // FileSystem operations
    FileSystem fs;
    fs.addDirectory("Documents");
    fs.addDirectory("Downloads");
    fs.addDirectory("Music");
    fs.addDirectory("Pictures");
    cout << "File System Structure (In-order):\n";
    fs.displayStructure();

    return 0;
}
