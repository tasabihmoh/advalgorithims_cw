#include <iostream>
#include <vector>
#include <stack>
#include <list>
using namespace std;

// Class to represent a directed graph using adjacency list representation
class DirectedGraph {
    int vertices;    // Number of vertices
    list<int> *adjacencyList; // Adjacency lists for each vertex

public:
    // Constructor to initialize the graph with a given number of vertices
    DirectedGraph(int numVertices) {
        this->vertices = numVertices;
        adjacencyList = new list<int>[numVertices];
    }

    // Add a directed edge from vertex 'from' to vertex 'to'
    void addDirectedEdge(int from, int to) {
        adjacencyList[from].push_back(to); // Add to to from’s list.
    }

    // Perform DFS starting from vertex v and track finish time in a stack
    void depthFirstSearch(int vertex, vector<bool>& visited, stack<int>& finishOrder) {
        visited[vertex] = true;  // Mark the current vertex as visited

        // Recursively visit all the adjacent vertices
        for (auto adjVertex = adjacencyList[vertex].begin(); adjVertex != adjacencyList[vertex].end(); ++adjVertex)
            if (!visited[*adjVertex])
                depthFirstSearch(*adjVertex, visited, finishOrder);

        // Push the vertex to the stack after all its adjacents are processed
        finishOrder.push(vertex);
    }

    // Generate the transpose of this graph
    DirectedGraph getTranspose() {
        DirectedGraph graphTranspose(vertices);
        for (int v = 0; v < vertices; v++) {
            // Recur for all the vertices adjacent to this vertex
            for (auto i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i) {
                graphTranspose.adjacencyList[*i].push_back(v);
            }
        }
        return graphTranspose;
    }

    // Find and print all strongly connected components of the graph
    void findAndPrintSCCs() {
        stack<int> Stack;

        // Initialize all vertices as not visited
        vector<bool> visited(vertices, false);

        // Fill vertices in stack with their finishing times
        for (int i = 0; i < vertices; i++)
            if (!visited[i])
                depthFirstSearch(i, visited, Stack);

        // Get the transpose of the graph
        DirectedGraph transpose = getTranspose();

        // Mark all vertices as not visited for the second DFS
        fill(visited.begin(), visited.end(), false);

        // Process all vertices in the order defined by their finishing times
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            // Print Strongly connected component of the popped vertex if not visited
            if (!visited[v]) {
                transpose.exploreDFS(v, visited);
                cout << endl;
            }
        }
    }

    // Utility DFS to explore the graph starting from vertex v
    void exploreDFS(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for (auto i = adjacencyList[v].begin(); i != adjacencyList[v].end(); ++i)
            if (!visited[*i])
                exploreDFS(*i, visited);
    }
};

int main() {
    // Create a graph with 6 vertices (0 to 5)
    DirectedGraph graph(6);
    graph.addDirectedEdge(0, 1);
    graph.addDirectedEdge(1, 2);
    graph.addDirectedEdge(2, 0);
    graph.addDirectedEdge(1, 3);
    graph.addDirectedEdge(3, 4);
    graph.addDirectedEdge(4, 5);
    graph.addDirectedEdge(5, 3);  // Adding more complexity

    cout << "Following are strongly connected components in the given graph:\n";
    graph.findAndPrintSCCs();

    return 0;
}
