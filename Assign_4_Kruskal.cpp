#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

// Function to find the parent of a node with path compression
int UltimateParent(int ve, vector<int> &parent)
{
    if (ve == parent[ve])
    {
        return ve;
    }
    return parent[ve] = UltimateParent(parent[ve], parent); // Path compression
}

// Function to perform union of two sets by rank
void UnionByRank(int u, int v, vector<int> &rank, vector<int> &parent)
{
    int upu = UltimateParent(u, parent);
    int upv = UltimateParent(v, parent);

    // Union by rank
    if (rank[upu] > rank[upv])
    {
        parent[upv] = upu; // Make smaller rank parent of larger rank
    }
    else if (rank[upv] > rank[upu])
    {
        parent[upu] = upv;
    }
    else
    {
        parent[upv] = upu;         // Union of same rank
        rank[upu] = rank[upu] + 1; // Increase rank of the new parent
    }
}

// Kruskal's Algorithm to find the Minimum Spanning Tree (MST)
void Kruskal(vector<pair<int, int>> Adj[], int Vertex, vector<string> departmentNames)
{
    int cost = 0;
    int edge = 0;

    vector<int> parent(Vertex);
    vector<int> rank(Vertex, 0);
    vector<pair<int, pair<int, int>>> path;

    // Initialize the parent of each vertex to itself
    for (int i = 0; i < Vertex; i++)
    {
        parent[i] = i;
    }

    vector<pair<int, pair<int, int>>> temp;

    // Fill temp vector with all edges (weight, node1, node2)
    for (int i = 0; i < Vertex; i++)
    {
        for (int j = 0; j < Adj[i].size(); j++)
        {
            temp.push_back({Adj[i][j].second, {i, Adj[i][j].first}}); // {weight, {node1, node2}}
        }
    }

    // Create priority queue and push all edges (from temp)
    priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq(temp.begin(), temp.end());

    // Process edges in increasing order of weights
    while (!pq.empty())
    {
        int weight = pq.top().first;
        int u = pq.top().second.first;
        int v = pq.top().second.second;
        pq.pop();

        // Check if the edge creates a cycle (i.e., both vertices have the same parent)
        if (UltimateParent(u, parent) != UltimateParent(v, parent))
        {
            cost += weight;                       // Add the weight to the total cost
            UnionByRank(u, v, rank, parent);      // Union of the sets
            path.push_back({weight, {u, v}}); // Store the edge in MST
            edge++;
        }

        if (edge == Vertex - 1) // When we have enough edges for the MST
        {
            break;
        }
    }

    // Print the MST with department names
    cout << "Minimum Spanning Tree (MST) of College Campus:\n";
    for (int i = 0; i < path.size(); i++) // Using 'i' for iteration
    {
        int u = path[i].second.first;
        int v = path[i].second.second;
        int weight = path[i].first;
        cout << departmentNames[u] << " - " << departmentNames[v] << " Distance: " << weight << " meters\n";
    }
    cout << "Total Minimum Distance to Connect All Departments: " << cost << " meters\n";
}
int main()
{
    // Adjacency matrix input
    int inputGraph[5][5] = {
        {0, 70, 90, 0, 0},   // ENTC
        {30, 0, 35, 40, 0},  // AIML
        {70, 50, 0, 47, 85}, // CS
        {0, 89, 55, 0, 23},  // IT
        {0, 0, 67, 34, 0}    // MECH
    };

    // Department names
    vector<string> departmentNames = {"ENTC", "AIML", "CS", "IT", "MECH"};

    int vertex = 5; // Number of vertices
    vector<pair<int, int>> AdjList[vertex];

    // Create adjacency list from the adjacency matrix
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            if (inputGraph[i][j] != 0) // Check for non-zero weights
            {
                AdjList[i].push_back({j, inputGraph[i][j]});
            }
        }
    }

    // Find the minimum cost of the Minimum Spanning Tree (MST)
    Kruskal(AdjList, vertex, departmentNames);

    return 0;
}
