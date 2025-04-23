#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class MazeGraph {
public:
    int vertex;
    vector<int> adjacencyList[100]; // Adjust size if needed

    MazeGraph(vector<vector<int>> &adjMatrix) {
        vertex = adjMatrix.size();
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                if (adjMatrix[i][j] == 1) {
                    adjacencyList[i].push_back(j);
                }
            }
        }
    }

    void DFS_Traversal(int node, vector<bool> &visited, vector<int> &ans) {
        visited[node] = true;
        ans.push_back(node);

        for (int i = 0; i < adjacencyList[node].size(); i++) 
        {
            if (!visited[adjacencyList[node][i]]) 
            {
                DFS_Traversal(adjacencyList[node][i], visited, ans);
            }
        }
    }

    void startDFS(int start) {
        vector<bool> visited(vertex, false);
        vector<int> ans;
        DFS_Traversal(start, visited, ans);

        cout << "DFS Traversal from " << start << ": ";
        for (int node : ans) {
            cout << node << " ";
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<int> visited(vertex, 0);
        queue<int> Q;
        cout << "BFS Traversal from " << start << ": ";
        cout << start << " ";
        visited[start] = 1;
        Q.push(start);

        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();

            for (int i = 0; i < adjacencyList[node].size(); i++) {
                int neighbor = adjacencyList[node][i];
                if (!visited[neighbor]) {
                    cout << neighbor << " ";
                    visited[neighbor] = 1;
                    Q.push(neighbor);
                }
            }
        }
        cout << endl;
    }
};
int main() {
    vector<vector<int>> G = {
        {0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 0},
        {0, 1, 0, 1, 1, 0, 0},
        {0, 1, 1, 0, 1, 0, 1},
        {0, 0, 1, 1, 0, 1, 1},
        {0, 1, 0, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 0, 1}
    };

    MazeGraph maze(G);
    maze.startDFS(3);
    maze.BFS(3);

    return 0;
}
