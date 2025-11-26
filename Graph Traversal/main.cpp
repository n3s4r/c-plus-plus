#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Graph {
public:
    // A map to represent the adjacency list
    // Key: Node ID, Value: List of neighbors
    map<int, vector<int>> adj;

    // Function to add an edge to the graph
    void addEdge(int v, int w) {
        adj[v].push_back(w); // Add w to v's list.
        adj[w].push_back(v); // Add v to w's list (Undirected).
    }

    // A recursive function used by DFS
    void DFSUtil(int v, map<int, bool>& visited) {
        // Mark the current node as visited and print it
        visited[v] = true;
        cout << v << " ";

        // Recur for all the vertices adjacent to this vertex
        for (int i : adj[v]) {
            if (!visited[i]) {
                DFSUtil(i, visited);
            }
        }
    }

    // The main function to do DFS traversal
    void DFS(int v) {
        // Mark all the vertices as not visited initially
        map<int, bool> visited;

        cout << "Depth First Traversal starting from vertex " << v << ":\n";

        // Call the recursive helper function
        DFSUtil(v, visited);

        cout << endl;
    }
};

int main() {
    Graph g;

    // Building the graph
    // Structure:
    //     0 -- 1 -- 3
    //     |    |
    //     2 -- 4

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 4);

    g.DFS(0); // Start DFS from node 0

    return 0;
}


/*

To handle disconnected graphs, you can modify the DFS function to loop through all nodes:

void DFS_Disconnected() {
    map<int, bool> visited;
    // Iterate over all keys in the map
    for (auto const& [node, neighbors] : adj) {
        if (!visited[node]) {
            DFSUtil(node, visited);
        }
    }
}

*/
