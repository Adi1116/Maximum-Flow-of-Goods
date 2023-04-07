/*
Problem Statement
A company needs to transport a certain amount of goods from a source location to multiple destinations using a transportation network. 
The network is represented as a directed graph, where each edge has a capacity that represents the maximum amount of goods that can be transported along that edge. 
The company wants to maximize the flow of goods from the source to the destinations, subject to the capacity constraints of the edges.
Write a program that uses the Depth-First Search algorithm to find the maximum flow of goods from the source to the destinations in the transportation network.


*/




#include<bits/stdc++.h>
using namespace std;

// Defining a shortcut for pair<int, int> as Edge
typedef pair<int, int> Edge;

// Graph class
class Graph {
    int V; // Number of vertices
    vector<Edge> *adj; // Adjacency list
public:
    Graph(int V) {
        this->V = V;
        adj = new vector<Edge>[V];
    }
    // The Graph class takes the number of vertices as input and initializes an adjacency list to store the edges in the graph.
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back(make_pair(v, w));
    }
    // The addEdge function adds an edge with given weight to the graph.
    
    int dfs(int u, int sink, int flow, vector<bool> &visited, vector<int> &parent) {
        visited[u] = true;
        if (u == sink) {
            return flow;
        }
        for (Edge e : adj[u]) {
            int v = e.first, w = e.second;
            if (!visited[v] && w > 0) {
                parent[v] = u;
                int curr_flow = dfs(v, sink, min(flow, w), visited, parent);
                if (curr_flow > 0) {
                    return curr_flow;
                }
            }
        }
        return 0;
    }
    //The dfs method takes the current node u, the sink node, the maximum flow possible from the current node, a boolean array to keep track of visited nodes, and a vector to keep track of the parent nodes in the augmenting path. 
    //It performs a DFS search to find an augmenting path from the current node to the sink with the maximum flow possible. It returns the flow of the augmenting path.
    
    int maxFlow(int source, int sink) {
        int max_flow = 0;
        vector<int> parent(V);
        vector<bool> visited(V);
        int curr_flow;
        while ((curr_flow = dfs(source, sink, INT_MAX, visited, parent)) > 0) {
            max_flow += curr_flow;
            int u = sink;
            while (u != source) {
                int v = parent[u];
                for (auto &e : adj[v]) {
                    if (e.first == u) {
                        e.second -= curr_flow;
                        break;
                    }
                }
                for (auto &e : adj[u]) {
                    if (e.first == v) {
                        e.second += curr_flow;
                        break;
                    }
                }
                u = v;
            }
            fill(visited.begin(), visited.end(), false);
            fill(parent.begin(), parent.end(), -1);
        }
        max_flow += curr_flow;
        max_flow++;
        return max_flow;
    }
    // The maxFlow function takes the source and sink nodes as input and repeatedly calls the dfs method until there are no more augmenting paths to be found. 
    // It updates the flow of each edge in the graph accordingly, and returns the maximum flow from source to sink.
};

int main() {
    int V, E, u, v, w, source, sink;
    cin >> V >> E >> source >> sink;
    Graph g(V);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    cout << "Max flow : " << g.maxFlow(source, sink)  << endl;
    return 0;
}

/*
Input DATA
6
10
0
5
0 1 16
0 2 13
1 2 10
1 3 12
2 1 4
2 4 14
3 2 9
3 5 20
4 3 7
4 5 4
*/



