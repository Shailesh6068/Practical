#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class BST {
public:
    vector<int> tree;
    int size;

    BST(int n) {
        size = 100; 
        tree.assign(size, -1); 
        for (int i = 0; i < n; i++) {
            int val;
            cin >> val;
            insert(0, val); 
        }
    }


    void insert(int index, int val) {
        if (index >= size) return; 

        if (tree[index] == -1) {
            tree[index] = val;
        }
        else if (val < tree[index]) {
            insert(2 * index + 1, val); 
        }
        else if (val > tree[index]) {
            insert(2 * index + 2, val); 
        }
    }

    void postorder(int index = 0) {
        if (index >= size || tree[index] == -1) return;

        postorder(2 * index + 1); 
        postorder(2 * index + 2); 
        cout << tree[index] << " "; 
    }

    int height() {
        int h = 0;
        queue<int> q;

        if (tree[0] == -1) 
        {
            return 0;
        }

        q.push(0); 

        while (!q.empty()) {
            int levelSize = q.size();
            while (levelSize--) {
                int i = q.front();
                q.pop();
                int left = 2 * i + 1;
                int right = 2 * i + 2;

                if (left < size && tree[left] != -1) 
                {
                    q.push(left);
                }
                if (right < size && tree[right] != -1) 
                { 
                    q.push(right);
                }    
            }
            h++;
        }

        return h;
    }

    // int height(int index = 0) {
    //     if (index >= size || tree[index] == -1)
    //         return 0;
    
    //     int leftHeight = height(2 * index + 1);
    //     int rightHeight = height(2 * index + 2);
    
    //     return 1 + max(leftHeight, rightHeight);
    // }
    
};
int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    BST tree(n);

    cout << "Post-order Traversal: ";
    tree.postorder();
    cout << endl;

    cout << "Height of the tree: " << tree.height() << endl;

    return 0;
}