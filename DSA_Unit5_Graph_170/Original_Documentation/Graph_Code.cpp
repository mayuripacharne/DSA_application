#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

const int INF = INT_MAX;

string stops[] = {
    "Bus Stand",
    "College",
    "Railway Station",
    "Hospital",
    "Market"
};

int graph[5][5] = {
    {0, 4, 2, 0, 0},
    {4, 0, 1, 5, 0},
    {2, 1, 0, 8, 10},
    {0, 5, 8, 0, 2},
    {0, 0, 10, 2, 0}
};

void primMST() {
    int key[5], parent[5];
    bool selected[5] = {false};
    int totalCost = 0;

    for (int i = 0; i < 5; i++) {
        key[i] = INF;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < 5; count++) {
        int u = -1;

        for (int i = 0; i < 5; i++) {
            if (!selected[i] &&
                (u == -1 || key[i] < key[u]))
                u = i;
        }

        if (u == -1 || key[u] == INF) {
            cout << "\nGraph is disconnected."
                 << "\nMST does not exist.\n";
            return;
        }

        selected[u] = true;

        if (parent[u] != -1) {
            cout << stops[parent[u]] << " - "
                 << stops[u] << " : "
                 << graph[parent[u]][u] << endl;

            totalCost += graph[parent[u]][u];
        }

        for (int v = 0; v < 5; v++) {
            if (graph[u][v] != 0 &&
                !selected[v] &&
                graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "Total MST Cost: " << totalCost << endl;
}

void dijkstra(int source, int destination) {
    int dist[5], parent[5];
    bool visited[5] = {false};

    for (int i = 0; i < 5; i++) {
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int count = 0; count < 5; count++) {
        int u = -1;

        for (int i = 0; i < 5; i++) {
            if (!visited[i] &&
                (u == -1 || dist[i] < dist[u]))
                u = i;
        }

        if (u == -1 || dist[u] == INF)
            break;

        visited[u] = true;

        for (int v = 0; v < 5; v++) {
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
        cout << "\nNo route exists between "
             << stops[source] << " and "
             << stops[destination] << ".\n";
        return;
    }

    vector<int> path;

    for (int v = destination; v != -1;
         v = parent[v])
        path.push_back(v);

    cout << "\nShortest Route: ";

    for (int i = (int)path.size() - 1; i >= 0; i--) {
        cout << stops[path[i]];

        if (i > 0)
            cout << " -> ";
    }

    cout << "\nShortest Distance: "
         << dist[destination] << endl;
}

int main() {
    cout << "TRANSPORT NETWORK OPTIMIZATION\n";

    cout << "\nMinimum Spanning Tree:\n";
    primMST();

    cout << "\nAvailable Stops:\n";

    for (int i = 0; i < 5; i++)
        cout << i << ". " << stops[i] << endl;

    int source, destination;

    cout << "\nEnter source stop number: ";
    cin >> source;

    cout << "Enter destination stop number: ";
    cin >> destination;

    if (source < 0 || source >= 5 ||
        destination < 0 || destination >= 5) {
        cout << "Invalid stop number.\n";
        return 0;
    }

    dijkstra(source, destination);

    return 0;
}