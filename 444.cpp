#include <iostream>
#include <string>
using namespace std;

class Graph {
    int n, edges;
    string cities[10];
    int dist[10][10];

public:
    void accept();
    void display();
    void primsMST();
};

void Graph::accept() {
    cout << "Enter number of cities: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter city name: ";
        cin >> cities[i];
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = (i == j) ? 0 : 999;

    cout << "Enter number of connections: ";
    cin >> edges;

    for (int i = 0; i < edges; i++) {
        string city1, city2;
        int weight, idx1 = -1, idx2 = -1;
        cout << "Enter connection (City1 City2 Distance): ";
        cin >> city1 >> city2 >> weight;

        for (int j = 0; j < n; j++) {
            if (cities[j] == city1) idx1 = j;
            if (cities[j] == city2) idx2 = j;
        }

        if (idx1 != -1 && idx2 != -1) {
            dist[idx1][idx2] = dist[idx2][idx1] = weight;
        } else {
            cout << "Invalid city names, try again!\n";
            i--;
        }
    }
}

void Graph::display() {
    cout << "\nDistance Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dist[i][j] << "\t";
        }
        cout << endl;
    }
}

void Graph::primsMST() {
    bool visited[10] = {false};
    int parent[10], key[10];
    int totalWeight = 0;

    for (int i = 0; i < n; i++) {
        key[i] = 999;
        parent[i] = -1;
    }

    key[0] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = 999, u;
        for (int v = 0; v < n; v++) {
            if (!visited[v] && key[v] < min) {
                min = key[v];
                u = v;
            }
        }

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (!visited[v] && dist[u][v] && dist[u][v] < key[v]) {
                parent[v] = u;
                key[v] = dist[u][v];
            }
        }
    }

    cout << "\nMinimum Spanning Tree:\n";
    for (int i = 1; i < n; i++) {
        cout << cities[parent[i]] << " - " << cities[i] << " : " << dist[i][parent[i]] << endl;
        totalWeight += dist[i][parent[i]];
    }
    cout << "Total MST Distance: " << totalWeight << endl;
}

int main() {
    Graph g;
    g.accept();
    g.display();
    g.primsMST();
    return 0;
}
