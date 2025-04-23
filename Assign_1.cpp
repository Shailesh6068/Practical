#include <iostream> 
#include <queue> 
#include <string> 
using namespace std; 
 
class Node { 

    public:
    string key, value; 
    Node* left;
    Node* right; 
    Node(string k, string v)
    {
        key = k; 
        value = v;
        left = nullptr; 
        right = nullptr; 
    } 
}; 
class DictionaryBST { 

    public:
 
    Node* insert(Node* node, string key, string value) 
    { 
        if (!node) 
        {
            Node* temp = new Node(key, value);
            return temp;
        } 
        if (key < node->key) 
        { 
            node->left = insert(node->left, key, value); 
        }
        else if (key > node->key) 
        {
            node->right = insert(node->right, key, value);
        } 
        else node->value = value; // Update value for duplicate keys 
        return node; 
    } 
       
    void inorder(Node* node) { 
        if (!node) 
        { 
            return;
        }

        inorder(node->left); 
        cout << node->key << ": " << node->value << " | "; 
        inorder(node->right);   
    } 
 
    Node* deleteNode(Node* node, string key) { 
        
        if (!node)
        {
            return nullptr;
        }

        // Find Position of the element
        if (node->key < key)
        {
            node->right = deleteNode(node->right,key);
            return node;
        }
        else if (node->key > key)
        {
            node->left = deleteNode(node->left,key);
            return node;
        }
        // We find our element 
        else
        {
            // Delete element
            // Leaf Node
            if (!node->left && !node->right)
            {
                delete node;
                return nullptr;
            }
            // 1 Child Node
            else if(!node->right)
            {
                Node* child = node->left;
                delete node;
                return child;
            }
            else if (!node->left)
            {
                Node* child = node->right;
                delete node;
                return child;
            }
            // 2 Child Node
            else if (node->left && node->right)
            {
                Node* parent = node;
                Node* child = parent->left;

                while (child->right)  //Find Rightmost Element to replace
                {
                    parent = child;
                    child = child->right;
                }
                // parent != node
                // parent == node

                if (parent != node)
                {
                    parent->right = child->left;
                    child->left = node->left;
                    child->right = node->right;
                    delete node;
                    return child;
                }
                else if (parent == node)
                {
                    child->right = node->right;
                    delete node;
                    return child;
                }
            }          
        }  
    } 
 
    bool search(Node* node, string key) {
        if (!node)
        {
            return 0;
        }
        
        if (node->key == key)
        {
            return 1;
        }
        else if (node->key < key)
        {
            return search(node->right,key);
        }
        else if (node->key > key)
        {
            return search(node->left,key);
        }
    }


    Node* findMin(Node* node) { 
        while (node && node->left) node = node->left; 
        return node; 
    } 
 
    void mirror(Node* node) { 
       if (!node)
       {
            return;
       }

       Node* temp = node->left;
       node->left = node->right;
       node->right = temp;
       
       mirror(node->left);
       mirror(node->right);
    } 
 
    Node* copyTree(Node* node) { 
        if (!node) 
        {
            return nullptr;
        } 
        Node* newNode = new Node(node->key, node->value); 
        newNode->left = copyTree(node->left); 
        newNode->right = copyTree(node->right); 
        return newNode; 
    } 
 
    void displayLevelWise(Node* node)
    {
        if (!node)
        {
            return;
        }

        queue<Node*> q;
        q.push(node);

        while (!q.empty())
        {
            Node* temp = q.front();
            q.pop();
            cout<<temp->key<<":"<<temp->value<<" | ";

            if (temp->left)
            {
                q.push(temp->left);
            }
            if (temp->right)
            {
                q.push(temp->right);
            } 
        }
    }
}; 
int main() { 
    DictionaryBST dict; 
    Node* root = nullptr; 

    // 1. Insert word (Handle insertion of duplicate entry) 
    root = dict.insert(root,"book", "Written pages");
    root = dict.insert(root,"car", "Four-wheeler");
    root = dict.insert(root,"door", "Room entry");
    root = dict.insert(root,"egg", "Bird food");
    root = dict.insert(root,"fish", "Water animal");

 
    cout << "Inorder Traversal:\n"; 
    dict.inorder(root); 
 
    // 2. Delete word 
    cout << "\nDeleting 'car':\n"; 
    root = dict.deleteNode(root,"car"); 
    dict.inorder(root); 
    
    // 3. Search specific word
    cout << "\nSearching for 'door':\n"; 
    if(dict.search(root,"door"))
    {
        cout<<"It is present.";
    }
    else
    {
        cout<<"It is Not Present.";
    }
    
    // 4. Display dictionary (Traversal)
    cout << "\nInorder Traversal:\n"; 
    dict.inorder(root);
 
    // 5. Mirror image of dictionary 
    cout << "\nMirroring Dictionary:\n"; 
    dict.mirror(root); 
    dict.inorder(root); 
 
    // 6. Create a copy of dictionary 
    cout << "\nCreating Copy of Dictionary:\n"; 
    Node* copiedDict = dict.copyTree(root); 
    dict.inorder(root); 

    // 7. Display dictionary level wise
    cout << "\nLevel-wise Traversal:\n"; 
    dict.displayLevelWise(root); 
   
    return 0; 
}