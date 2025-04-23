#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Class representing a Maze Graph and its traversal algorithms
class MazeGraph {
private:
    vector<int> adjancyList[50]; // Adjacency list representation (assuming maximum 50 nodes)
    int vertex; // Number of vertices (nodes)

public:
    // Constructor to initialize the maze graph
    MazeGraph(vector<vector<int>> graph) {
        vertex = graph.size();
        
        // Building adjacency list from the maze grid
        for (int i = 0; i < vertex; i++) {
            for (int j = 0; j < vertex; j++) {
                if (graph[i][j] == 1) {
                    adjancyList[i].push_back(j);
                }
            }
        }
    }

    // Helper function for DFS traversal
    void DFS_Traversal(int node, vector<int>& visited, vector<int>& ans) {
        visited[node] = 1;
        ans.push_back(node);

        for (int i = 0; i < adjancyList[node].size(); i++) {
            int neighbor = adjancyList[node][i];
            if (!visited[neighbor]) {
                DFS_Traversal(neighbor, visited, ans);
            }
        }
    }

    // Function to start DFS traversal
    void startDFS(int start) {
        vector<int> visited(vertex, 0);
        vector<int> ans;
    
        DFS_Traversal(start, visited, ans);
    
        cout << "DFS Traversal from " << start << ": ";
        for (int i = 0; i < ans.size(); i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }    

    // Function to perform BFS traversal
    void BFS(int start) {
        vector<int> visited(vertex, 0);
        queue<int> Q;

        cout << "BFS Traversal from " << start << ": ";
        visited[start] = 1;
        Q.push(start);

        while (!Q.empty()) {
            int node = Q.front();
            Q.pop();
            cout << node << " ";

            for (int i = 0; i < adjancyList[node].size(); i++) {
                int neighbor = adjancyList[node][i];
                if (!visited[neighbor]) {
                    visited[neighbor] = 1;
                    Q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Display adjacency list (optional for debugging)
    void displayAdjacencyList() {
        cout << "\nAdjacency List:" << endl;
        for (int i = 0; i < vertex; i++) {
            cout << i << " -> ";
            for (int j = 0; j < adjancyList[i].size(); j++) {
                cout << adjancyList[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Graph representation of a sample maze (0 = wall, 1 = path)
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

    maze.displayAdjacencyList(); // Optional: view how graph is built

    // Perform DFS and BFS
    maze.startDFS(3);
    maze.BFS(3);

    return 0;
}
