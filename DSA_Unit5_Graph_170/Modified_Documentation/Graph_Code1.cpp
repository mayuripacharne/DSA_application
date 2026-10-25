#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
using namespace std;

const int INF = INT_MAX;

vector<string> stops = {
    "Bus Stand",
    "College",
    "Railway Station",
    "Hospital",
    "Market"
};

vector<vector<int>> graph = {
    {0, 4, 2, 0, 0},
    {4, 0, 1, 5, 0},
    {2, 1, 0, 8, 10},
    {0, 5, 8, 0, 2},
    {0, 0, 10, 2, 0}
};

void addStop() {
    string name;

    cout << "Enter new stop name: ";
    cin.ignore();
    getline(cin, name);

    int n = stops.size();

    stops.push_back(name);

    for (int i = 0; i < n; i++)
        graph[i].push_back(0);

    graph.push_back(vector<int>(n + 1, 0));

    cout << "New stop added successfully.\n";
}

void addRoute() {
    int u, v, w;
    int n = stops.size();

    cout << "\nAvailable stops:\n";

    for (int i = 0; i < n; i++)
        cout << i << ". " << stops[i] << endl;

    cout << "Enter first stop number: ";
    cin >> u;

    cout << "Enter second stop number: ";
    cin >> v;

    cout << "Enter route distance/cost: ";
    cin >> w;

    if (u < 0 || u >= n ||
        v < 0 || v >= n ||
        u == v || w <= 0) {
        cout << "Invalid route details.\n";
        return;
    }

    graph[u][v] = w;
    graph[v][u] = w;

    cout << "Route added successfully.\n";
}

void bfs() {
    int n = stops.size();
    vector<bool> visited(n, false);
    queue<int> q;

    cout << "\nBFS Traversal: ";

    for (int start = 0; start < n; start++) {
        if (visited[start])
            continue;

        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int u = q.front();
            q.pop();

            cout << stops[u] << " ";

            for (int v = 0; v < n; v++) {
                if (graph[u][v] > 0 &&
                    !visited[v]) {
                    visited[v] = true;
                    q.push(v);
                }
            }
        }

        if (start < n - 1)
            cout << "| ";
    }

    cout << endl;
}

void primMST() {
    int n = stops.size();

    vector<int> key(n, INF);
    vector<int> parent(n, -1);
    vector<bool> selected(n, false);

    int totalCost = 0;
    int edgeCount = 0;

    key[0] = 0;

    cout << "\nMST Edges:\n";

    for (int count = 0; count < n; count++) {
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!selected[i] &&
                (u == -1 || key[i] < key[u]))
                u = i;
        }

        if (u == -1 || key[u] == INF) {
            cout << "Graph is disconnected.\n"
                 << "A complete MST does not exist.\n";
            return;
        }

        selected[u] = true;

        if (parent[u] != -1) {
            cout << stops[parent[u]] << " - "
                 << stops[u] << " : "
                 << graph[parent[u]][u] << endl;

            totalCost += graph[parent[u]][u];
            edgeCount++;
        }

        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 &&
                !selected[v] &&
                graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Total MST Cost: "
         << totalCost << endl;
}

void dijkstra(int source, int destination) {
    int n = stops.size();

    vector<int> dist(n, INF);
    vector<int> parent(n, -1);
    vector<bool> visited(n, false);

    dist[source] = 0;

    for (int count = 0; count < n; count++) {
        int u = -1;

        for (int i = 0; i < n; i++) {
            if (!visited[i] &&
                (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        if (u == -1 || dist[u] == INF)
            break;

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] > 0 &&
                !visited[v] &&
                dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (dist[destination] == INF) {
        cout << "No path exists between "
             << stops[source] << " and "
             << stops[destination] << ".\n";
        return;
    }

    vector<int> path;

    for (int v = destination; v != -1;
         v = parent[v])
        path.push_back(v);

    cout << "Shortest Route: ";

    for (int i = (int)path.size() - 1; i >= 0; i--) {
        cout << stops[path[i]];

        if (i > 0)
            cout << " -> ";
    }

    cout << "\nShortest Distance: "
         << dist[destination] << endl;
}

void displayResults() {
    int n = stops.size();

    cout << "\n--- Transport Network Results ---\n";

    cout << "Number of stops: " << n << endl;

    bfs();
    primMST();

    int source, destination;

    cout << "\nAvailable stops:\n";

    for (int i = 0; i < n; i++)
        cout << i << ". " << stops[i] << endl;

    cout << "Enter source stop number: ";
    cin >> source;

    cout << "Enter destination stop number: ";
    cin >> destination;

    if (source < 0 || source >= n ||
        destination < 0 || destination >= n) {
        cout << "Invalid stop number.\n";
        return;
    }

    dijkstra(source, destination);
}

int main() {
    int choice;

    cout << "DYNAMIC TRANSPORT NETWORK\n";

    cout << "\nResults Before Update:\n";
    displayResults();

    cout << "\n--- Update Transport Network ---\n";
    cout << "1. Add New Transport Stop\n";
    cout << "2. Add New Route\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1)
        addStop();
    else if (choice == 2)
        addRoute();
    else {
        cout << "Invalid choice.\n";
        return 0;
    }

    cout << "\nResults After Update:\n";
    displayResults();

    cout << "\nComparison completed.\n";

    return 0;
}