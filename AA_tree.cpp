#include <iostream>
using namespace std;

struct Node {
    int key;
    int level;
    Node* left;
    Node* right;

    Node(int k) {
        key = k;
        level = 1;
        left = nullptr;
        right = nullptr;
    }
};

// Skew operation: right rotation
Node* skew(Node* node) {
    if (!node || !node->left)
        return node;
    if (node->left->level == node->level) {
        Node* L = node->left;
        node->left = L->right;
        L->right = node;
        return L;
    }
    return node;
}

// Split operation: left rotation
Node* split(Node* node) {
    if (!node || !node->right || !node->right->right)
        return node;
    if (node->level == node->right->right->level) {
        Node* R = node->right;
        node->right = R->left;
        R->left = node;
        R->level++;
        return R;
    }
    return node;
}

// Decrease level if needed after deletion
Node* decreaseLevel(Node* node) {
    int shouldBe = 1;
    if (node->left && node->right)
        shouldBe = min(node->left->level, node->right->level) + 1;
    else if (node->left)
        shouldBe = node->left->level + 1;
    else if (node->right)
        shouldBe = node->right->level + 1;

    if (shouldBe < node->level) 
    {
        node->level = shouldBe;
        if (node->right && shouldBe < node->right->level)
        {
            node->right->level = shouldBe;
        }
    }
    return node;
}

// Insertion
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    else
        return root; // Duplicate

    root = skew(root);
    root = split(root);
    return root;
}

// Search
Node* search(Node* root, int key) {
    if (!root || root->key == key)
        return root;
    return key < root->key ? search(root->left, key) : search(root->right, key);
}

// In-order traversal
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
    }
}

// Deletion
Node* deleteNode(Node* root, int key) {
    if (!root) return nullptr;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node found
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }
        else if (!root->left || !root->right) {
            Node* child = root->left ? root->left : root->right;
            delete root;
            return child;
        }
        else {
            // Find in-order predecessor (max in left subtree)
            Node* pred = root->left;
            while (pred->right) pred = pred->right;
            root->key = pred->key;
            root->left = deleteNode(root->left, pred->key);
        }
    }

    root = decreaseLevel(root);
    root = skew(root);
    if (root->right)
    {
        root->right = skew(root->right);
    }
    if (root->right && root->right->right)
    {
        root->right->right = skew(root->right->right);
    }

    root = split(root);

    if (root->right) 
    {
        root->right = split(root->right);
    }

    return root;
}

int main() {
    Node* root = nullptr;
    int keys[] = {20, 10, 30, 5, 15, 25, 35};

    for (int key : keys)
        root = insert(root, key);

    cout << "In-order before deletion: ";
    inorder(root);
    cout << endl;

    // Delete node
    int delKey = 10;
    root = deleteNode(root, delKey);

    cout << "In-order after deleting " << delKey << ": ";
    inorder(root);
    cout << endl;

    return 0;
}
