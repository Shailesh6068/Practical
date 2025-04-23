#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class MazeBFS {
private:
    vector<vector<int>> maze;
    int rows, cols;
    vector<pair<int, int>> directions;

public:
    MazeBFS(vector<vector<int>> m) {
        maze = m;
        rows = maze.size();
        cols = maze[0].size();
        directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}}; // up, down, left, right
    }

    bool isValid(int x, int y, vector<vector<int>>& visited) {
        return x >= 0 && x < rows && y >= 0 && y < cols &&
               maze[x][y] == 1 && visited[x][y] == 0;
    }

    void BFS(int startX, int startY) {
        vector<vector<int>> visited(rows, vector<int>(cols, 0));
        queue<pair<int, int>> q;

        cout << "BFS Traversal from (" << startX << "," << startY << "):\n";

        if (maze[startX][startY] == 0) {
            cout << "Start cell is a wall.\n";
            return;
        }

        q.push(make_pair(startX, startY));
        visited[startX][startY] = 1;

        while (!q.empty()) {
            
            int x = q.front().first;
            int y = q.front().second;
            q.pop();
          

            cout << "(" << x << "," << y << ") ";

            for (int i = 0; i < directions.size(); i++) {
                int newX = x + directions[i].first;
                int newY = y + directions[i].second;

                if (isValid(newX, newY, visited)) {
                    visited[newX][newY] = 1;
                    q.push(make_pair(newX, newY));
                }
            }
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

    MazeBFS bfsSolver(maze);
    bfsSolver.BFS(0, 0);

    return 0;
}
