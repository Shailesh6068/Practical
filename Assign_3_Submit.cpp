// Consider the scenario of a maze. The maze is represented as a grid of cells, where each cell
// can be either open or blocked. Each cell in the maze represents a vertex. The goal is to find
// a path from the starting point to the goal within a given maze using DFS and BFS.


#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Class representing a Maze Graph and its traversal algorithms
class MazeGraph {
private:
    vector<vector<int>> Graph; // Adjacency matrix representation of the maze
    int vertex; // Number of vertices (nodes)

public:
    // Constructor to initialize the maze graph
    MazeGraph(vector<vector<int>> graph) {
        Graph = graph;
        vertex = graph.size();
    }

    // Function to perform BFS traversal in the maze graph
    void BFS(int start) {
        vector<int> visited(vertex, 0);
        queue<int> Q;

        cout << "BFS Traversal from " << start << ": ";
        visited[start] = 1;
        Q.push(start);

        while (!Q.empty()) {
            int node = Q.front(); // renamed from i to node
            Q.pop();
            cout << node << " ";
            for (int j = 1; j < vertex; j++) {
                if (Graph[node][j] == 1 && visited[j] == 0) {
                    
                    visited[j] = 1;
                    Q.push(j);
                }
            }
        }
        cout << endl;
    }

    // Function to perform DFS traversal in the maze graph
    void DFS(int node, vector<int> &visited) 
    {
        if (visited[node] == 0) 
        {
            cout << node << " ";
            visited[node] = 1;

            for (int j = 1; j < vertex; j++) 
            {
                if (Graph[node][j] == 1 && visited[j] == 0) {
                    DFS(j, visited);
                }
            }
        }
    }

    // Helper function to start DFS with fresh visited array
    void startDFS(int start) {
        vector<int> visited(vertex, 0);
        cout << "DFS Traversal from " << start << ": ";
        DFS(start, visited);
        cout << endl;
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

    // Creating MazeGraph object
    MazeGraph maze(G);

    // Perform DFS and BFS
    maze.startDFS(3);
    maze.BFS(3);

    return 0;
}
