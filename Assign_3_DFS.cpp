#include <iostream>
#include <vector>
using namespace std;

class MazeDFS {
private:
    vector<vector<int>> maze;
    int rows, cols;
    vector<pair<int, int>> directions;

public:
    MazeDFS(vector<vector<int>> m) {
        maze = m;
        rows = maze.size();
        cols = maze[0].size();
        directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // up, down, left, right
    }
    
    bool isValid(int x, int y, vector<vector<int>>& visited) {
        return (x >= 0 && x < rows) && (y >= 0 && y < cols) &&
               (maze[x][y] == 1 && visited[x][y] == 0);
    }
    
    void DFS(int x, int y, vector<vector<int>>& visited) {
        visited[x][y] = 1;
        cout << "(" << x << "," << y << ") ";

        for (int i = 0; i < directions.size(); i++) 
        {
            int newX = x + directions[i].first;
            int newY = y + directions[i].second;
            if (isValid(newX, newY, visited)) 
            {
                DFS(newX, newY, visited);
            }
        }
    }
    
    void startDFS(int startX, int startY) 
    {
        vector<vector<int>> visited(rows, vector<int>(cols, 0));

        cout << "DFS Traversal from (" << startX << "," << startY << "):\n";
        if (maze[startX][startY] == 1) {
            DFS(startX, startY, visited);
        } else {
            cout << "Start cell is a wall.\n";
        }
        cout << endl;
    }
};

int main() {
    vector<vector<int>> maze = {
        {1, 1, 1, 0, 0, 0},
        {0, 0, 1, 1, 0, 0},
        {1, 1, 0, 1, 1, 1},
        {0, 1, 1, 0, 1, 0},
        {1, 1, 0, 1, 1, 1}
    };

    MazeDFS dfsSolver(maze);
    dfsSolver.startDFS(0, 2);

    return 0;
}
