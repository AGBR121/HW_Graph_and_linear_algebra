#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V;  // Número de vértices
    vector<vector<int>> adj;  // Lista de adyacencia

public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);  // Arista dirigida de u a v
    }

    void DFS(int v, vector<bool>& visited, stack<int>& Stack) {
        visited[v] = true;
        for (int neighbor : adj[v]) {
            if (!visited[neighbor])
                DFS(neighbor, visited, Stack);
        }
        Stack.push(v);
    }

    void DFSUtil(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        for (int neighbor : adj[v]) {
            if (!visited[neighbor])
                DFSUtil(neighbor, visited, component);
        }
    }

    Graph getTranspose() {
        Graph gT(V);
        for (int v = 0; v < V; ++v) {
            for (int neighbor : adj[v]) {
                gT.adj[neighbor].push_back(v);
            }
        }
        return gT;
    }

    void printStronglyConnectedComponents() {
        stack<int> Stack;
        vector<bool> visited(V, false);

        // Paso 1: DFS para llenar el stack con el orden de finalización
        for (int i = 0; i < V; ++i) {
            if (!visited[i])
                DFS(i, visited, Stack);
        }

        // Paso 2: Transponer el grafo
        Graph gT = getTranspose();

        // Paso 3: DFS sobre el grafo transpuesto en el orden del stack
        fill(visited.begin(), visited.end(), false);
        while (!Stack.empty()) {
            int v = Stack.top();
            Stack.pop();

            if (!visited[v]) {
                vector<int> component;
                gT.DFSUtil(v, visited, component);

                cout << "Componente fuertemente conexo: ";
                for (int node : component)
                    cout << node << " ";
                cout << endl;
            }
        }
    }
};

int main() {
    
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);   // CFC: {0, 1, 2}

    g.addEdge(3, 4);   
    g.addEdge(4, 5);
    g.addEdge(5, 3);   // CFC: {3, 4, 5}

    g.addEdge(6, 5);   // 6 apunta a 5, pero no puede volver => {6} solo


    cout << "Las componentes fuertemente conexas son:\n";
    g.printStronglyConnectedComponents();

    return 0;
}