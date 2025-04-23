#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define V 5

void Prims(vector<pair<int, int>> Adj[], int vertex, vector<string> departmentNames)
{
    vector<bool> isMST(vertex, false);
    vector<int> parent(vertex, -1);

    // priority queue of {weight, {node, parent}}
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> q;

    q.push({0, {0, -1}});
    int cost = 0;

    while (!q.empty())
    {
        int weight = q.top().first;
        int node = q.top().second.first;
        int par = q.top().second.second;
        q.pop();

        if (!isMST[node])
        {
            isMST[node] = true;
            cost += weight;
            parent[node] = par;

            for (int i = 0; i < Adj[node].size(); i++)
            {
                int adjNode = Adj[node][i].first;
                int adjWeight = Adj[node][i].second;

                if (!isMST[adjNode])
                {
                    q.push({adjWeight, {adjNode, node}});
                }
            }
        }
    }

    // Print MST
    cout << "Minimum Spanning Tree (MST) of College Campus:\n";
    for (int i = 0 ; i < vertex; i++)
    {  
        if (parent[i] != -1)
        {
            cout << departmentNames[parent[i]] << " - " << departmentNames[i]<<endl;
        }
    }
    cout << "Total Minimum Distance to Connect All Departments: " << cost << " meters\n";
}
int main()
{
    // Adjacency matrix input
    int inputGraph[V][V] = {
        {0, 70, 90, 0, 0},   // ENTC
        {30, 0, 35, 40, 0},  // AIML
        {70, 50, 0, 47, 85}, // CS
        {0, 89, 55, 0, 23},  // IT
        {0, 0, 67, 34, 0}    // MECH
    };

    // Department names
    vector<string> departmentNames = {"ENTC", "AIML", "CS", "IT", "MECH"};

    // Create adjacency list from matrix
    vector<pair<int, int>> AdjList[V];
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            if (inputGraph[i][j] != 0)
            {
                AdjList[i].push_back({j, inputGraph[i][j]});
                AdjList[j].push_back({i, inputGraph[i][j]}); // Add reverse edge
            }
                                 //  index       weight
        }
    }

    // Display Adjacency List
    cout << "Adjacency List:\n";
    for (int i = 0; i < V; i++)
    {
        cout << departmentNames[i] << " -> ";
        for (int j = 0; j < AdjList[i].size(); j++)
        {
            cout << "(" << departmentNames[AdjList[i][j].first] << ", " << AdjList[i][j].second << "m) ";
        }
        cout << endl;
    }

    // Run Prim’s Algorithm
    Prims(AdjList, V, departmentNames);

    return 0;
}
