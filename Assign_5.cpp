#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
// Consider the scenario of the supply chain management system. The supply chain involves
// multiple locations, such as suppliers, warehouses, distribution centers, and retail stores,
// connected by transportation networks. Find the shortest possible route using Dijkstra's algorithm
// to optimize transportation path and inventory management.
vector<int> Dijkstra(vector<pair<int, int>> Adj[], int vertex, int source, vector<int>& parent)
{
    vector<bool> explored(vertex, false);
    vector<int> distance(vertex, INT_MAX);
    distance[source] = 0;
    parent[source] = -1;

    for (int count = 0; count < vertex; count++)
    {
        int node = -1, value = INT_MAX;
        for (int i = 0; i < vertex; i++)
        {
            if (!explored[i] && value > distance[i])
            {
                node = i;
                value = distance[i];
            }
        }

        if (node == -1) break; // all reachable nodes explored

        explored[node] = true;

        for (int i = 0; i < Adj[node].size(); i++)
        {
            int neighbour = Adj[node][i].first;
            int weight = Adj[node][i].second;
            if (!explored[neighbour] && distance[node] + weight < distance[neighbour])
            {
                distance[neighbour] = distance[node] + weight;
                parent[neighbour] = node;
            }
        }
    }

    return distance;
}

// void printPath(int node, vector<int>& parent, vector<string>& locations)
// {
//     if (node == -1)
//         return;
//     printPath(parent[node], parent, locations);
//     cout << locations[node];
//     if (parent[node] != -1) cout << " -> ";
// }
void printPath(int node, vector<int>& parent, vector<string>& locations)
{
    vector<int> path;
    while (node != -1)
    {
        path.push_back(node);
        node = parent[node];
    }

    reverse(path.begin(), path.end());

    for (int i = 0; i < path.size(); i++)
    {
        cout << locations[path[i]]<<"->";
        // if (i != path.size() - 1)
        //     cout << " -> ";
    }
}
int main()
{
    int vertex = 5;
    vector<string> locations = {"Supplier", "Warehouse", "Distribution Center", "Retail Store 1", "Retail Store 2"};

    vector<pair<int, int>> AdjList[vertex];

    AdjList[0].push_back({1, 10}); // Supplier to Warehouse
    AdjList[1].push_back({0, 10});

    AdjList[1].push_back({2, 20}); // Warehouse to Distribution Center
    AdjList[2].push_back({1, 20});

    AdjList[2].push_back({3, 30}); // Distribution Center to Retail Store 1
    AdjList[3].push_back({2, 30});

    AdjList[2].push_back({4, 25}); // Distribution Center to Retail Store 2
    AdjList[4].push_back({2, 25});

    vector<int> parent(vertex, -1);
    int source = 0; // Supplier
    vector<int> result = Dijkstra(AdjList, vertex, source, parent);

    cout << "\nShortest distances and paths from Supplier:\n";
    for (int i = 0; i < vertex; i++)
    {
        cout << "To " << locations[i] << ": " << result[i] << " units | Path: ";
        printPath(i, parent, locations);
        cout << endl;
    }

    return 0;
}
