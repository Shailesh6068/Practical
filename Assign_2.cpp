// Implement a multiplayer game system that uses an AVL tree data structure to organize and
// manage player data efficiently. The multiplayer game supports multiple players participating
// simultaneously, and the AVL tree is used to store player information such as player_id and
// scores (key, value pair). The system should provide following operation:
// 1. Player Registration
// 2. Leaderboard Display
// 3. Remove player from game

#include <iostream>
#include <vector>
using namespace std;
class Node
{
public:
    int id, score;
    Node *left;
    Node *right;
    int height;

    Node(int id1, int score1)
    {
        id = id1;
        score = score1;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};
int getheight(Node *root)
{
    if (!root)
    {
        return 0;
    }
    return root->height;
}
int getbalance(Node *root)
{
    return getheight(root->left) - getheight(root->right);
}
Node *rightrotation(Node *root)
{
    Node *child = root->left;
    Node *childright = root->left->right;

    child->right = root;
    root->left = childright;

    child->height = 1 + max(getheight(child->left), getheight(child->right));
    root->height = 1 + max(getheight(root->left), getheight(root->right));

    return child;
}
Node *leftrotation(Node *root)
{
    Node *child = root->right;
    Node *childleft = root->right->left;

    child->left = root;
    root->right = childleft;

    child->height = 1 + max(getheight(child->left), getheight(child->right));
    root->height = 1 + max(getheight(root->left), getheight(root->right));

    return child;
}
class Tree
{

public:
    // insert data In AVL
    // insert data (As BST)
    Node *Insert(Node *root, int id, int score)
    {
        if (!root)
        {
            Node *temp = new Node(id, score);
            return temp;
        }

        if (score < root->score)
        {
            root->left = Insert(root->left, id, score);
        }
        else if (score > root->score)
        {
            root->right = Insert(root->right, id, score);
        }
        else // score == root->score
        {
            if (id < root->id)
            {
                root->left = Insert(root->left, id, score);
            }
            else if (id > root->id)
            {
                root->right = Insert(root->right, id, score);
            }
            else
            {
                // Duplicate id and score — already exists
                return root;
            }
        }
        
        // update height
        root->height = 1 + max(getheight(root->left), getheight(root->right));

        // Check balance
        int balance = getbalance(root);

        // rotation to balance
        if (balance > 1)
        {
            if (score < root->left->score) // LL
            {
                return rightrotation(root);
            }
            else if (score > root->left->score) // LR
            {
                root->left = leftrotation(root->left);
                return rightrotation(root);
            }
        }
        else if (balance < -1)
        {
            // RR
            if (score > root->right->score)
            {
                return leftrotation(root);
            }
            // RL
            else if (score < root->right->score)
            {
                root->right = rightrotation(root->right);
                return leftrotation(root);
            }
        }

        return root;
    }

    void inorder(Node *node)
    {

        if (!node)
        {
            return;
        }

        inorder(node->right);
        cout << "Player ID: " << node->id << ", Score: " << node->score << endl;
        inorder(node->left);
    }

    Node *RemovePlayer(Node *root, int score)
    {
        if (!root)
        {
            return nullptr;
        }

        if (root->score < score)
        {
            root->right = RemovePlayer(root->right, score);
        }
        else if (root->score > score)
        {
            root->left = RemovePlayer(root->left, score);
        }
        else
        {
            // leaf
            if (!root->left && !root->right)
            {
                delete root;
                return nullptr;
            }
            else if (!root->left)
            {
                Node *child = root->right;
                delete root;
                return child;
            }
            else if (!root->right)
            {
                Node *child = root->left;
                delete root;
                return child;
            }
            else
            {
                Node *child = root->left;

                while (child->right)
                {
                    child = child->right;
                }

                root->score = child->score;
                root->id = child->id;
                root->left = RemovePlayer(root->left, child->score);
            }
        }

        root->height = 1 + max(getheight(root->left), getheight(root->right));

        int balance = getbalance(root);

        if (balance > 1)
        {
            if (getbalance(root->left) >= 0) // LL
            {
                return rightrotation(root);
            }
            else // LR
            {
                root->left = leftrotation(root->left);
                return rightrotation(root);
            }
        }
        else if (balance < -1)
        {
            if (getbalance(root->right) <= 0) // RR
            {
                return leftrotation(root);
            }
            else
            {
                root->right = rightrotation(root->right); // RL
                return leftrotation(root);
            }
        }

        return root;
    }
};
int main()
{
    Tree game;
    Node *root = nullptr;

    // insert data
    root = game.Insert(root, 1, 100);
    root = game.Insert(root, 2, 200);
    root = game.Insert(root, 3, 150);
    root = game.Insert(root, 4, 180);
    root = game.Insert(root, 5, 120);
    root = game.Insert(root, 8, 200);

    // Leaderboard Display
    cout<<"\nLeaderboard On Score :\n";
    game.inorder(root);

    // remove player
    root = game.RemovePlayer(root, 200);

    cout << "\nAfter Remove Player:\n";
    game.inorder(root);
}