#include <iostream>
using namespace std;

enum Color
{
    RED,
    BLACK
};
class Node
{
public:
    int data;
    bool color; // RED = 1, BLACK = 0
    Node *left;
    Node *right;
    Node *parent;
    
    Node(int val)
    {
        data = val;
        color = RED; // New node is always RED
        left = right = parent = nullptr;
    }
};

class RedBlackTree
{
public:
    Node *root;

    RedBlackTree()
    {
        root = nullptr;
    }

    void rotateLeft(Node *&root, Node *node)
    {
        Node *child = node->right;
        Node *childleft = child->left;
        node->right = childleft;

        if (childleft != nullptr)
            childleft->parent = node;

        child->parent = node->parent;

        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->left)
            node->parent->left = child;
        else
            node->parent->right = child;

        child->left = node;
        node->parent = child;
    }

    void rotateRight(Node *&root, Node *node)
    {
        Node *child = node->left;
        node->left = child->right;

        if (child->right != nullptr)
            child->right->parent = node;

        child->parent = node->parent;

        if (node->parent == nullptr)
            root = child;
        else if (node == node->parent->right)
            node->parent->right = child;
        else
            node->parent->left = child;

        child->right = node;
        node->parent = child;
    }

    void fixViolation(Node *&root, Node *&pt)
    {
        Node *parent = nullptr;
        Node *grandparent = nullptr;

        while (pt != root && pt->color == RED && pt->parent->color == RED)
        {
            parent = pt->parent;
            grandparent = parent->parent;

            // Case A: Parent is left child
            if (parent == grandparent->left)
            {
                Node *uncle = grandparent->right;

                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    pt = grandparent;
                }
                else
                {
                    // Case 2: pt is right child
                    if (pt == parent->right) // Case 2: pt is right child
                    {
                        rotateLeft(root, parent);   // Rotate left on parent to make pt the parent
                        rotateRight(root, grandparent); // Rotate right on grandparent to fix the violation
                        swap(parent->color, grandparent->color);  // Swap colors of parent and grandparent
                        pt = parent; // Update pt to be the new parent
                        parent = pt->parent; // Move to the next level
                    }
                    // Case 3: pt is left child
                    else 
                    { 
                        rotateRight(root, grandparent);  // Rotate right on grandparent
                        swap(parent->color, grandparent->color);  // Swap colors of parent and grandparent
                        pt = parent; // Update pt to be the parent
                    }
                    
                }
            }
            else
            { // Case B: Parent is right child
                Node *uncle = grandparent->left;

                // Case 1: Uncle is RED
                if (uncle != nullptr && uncle->color == RED)
                {
                    grandparent->color = RED;
                    parent->color = BLACK;
                    uncle->color = BLACK;
                    pt = grandparent;
                }
                else
                {
                    // Case 2: pt is left child
                    if (pt == parent->left)
                    {
                        rotateRight(root, parent);
                        pt = parent;
                        parent = pt->parent;
                    }
                    // Case 3: pt is right child
                    rotateLeft(root, grandparent);
                    swap(parent->color, grandparent->color);
                    pt = parent;
                }
            }
        }

        root->color = BLACK;
    }

    Node *InsertNode(Node *root, Node *pt)
    {
        if (root == nullptr)
            return pt;

        if (pt->data < root->data)
        {
            root->left = InsertNode(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data)
        {
            root->right = InsertNode(root->right, pt);
            root->right->parent = root;
        }

        return root;
    }

    void Insert(int key)
    {
        Node *pt = new Node(key); // Create a new node with the given key
        root = InsertNode(root, pt); // Insert node into the tree
        fixViolation(root, pt); // Fix any violation of Red-Black properties
    }

    void Preorder(Node *root)
    {
        if (!root)
            return;
        cout << root->data << "(" << (root->color == RED ? "R" : "B") << ") ";
        Preorder(root->left);
        Preorder(root->right);
    }

    void Inorder(Node *root)
    {
        if (!root)
            return;
        Inorder(root->left);
        cout << root->data << "(" << (root->color == RED ? "R" : "B") << ") ";
        Inorder(root->right);
    }

    void showTraversal()
    {
        cout << "\nPreorder:\n";
        Preorder(root);
        cout << "\nInorder:\n";
        Inorder(root);
        cout << endl;
    }
};

int main()
{
    RedBlackTree tree;
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(30);
    tree.Insert(15);

    tree.showTraversal();

    return 0;
}
