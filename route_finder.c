
#include <stdio.h>

#define V 5
#define INF 999999

char *cities[V] = {
    "Mumbai",
    "Pune",
    "Nashik",
    "Thane",
    "Nagpur"
};

int graph[V][V] = {
    {0, 150, 0, 25, 0},
    {150, 0, 210, 0, 720},
    {0, 210, 0, 140, 0},
    {25, 0, 140, 0, 0},
    {0, 720, 0, 0, 0}
};

int findMinimum(int distance[], int visited[]) {
    int minimum = INF;
    int index = -1;

    for (int i = 0; i < V; i++) {
        if (!visited[i] && distance[i] < minimum) {
            minimum = distance[i];
            index = i;
        }
    }

    return index;
}

void dijkstra(int source, int destination) {
    int distance[V];
    int visited[V] = {0};
    int parent[V];

    for (int i = 0; i < V; i++) {
        distance[i] = INF;
        parent[i] = -1;
    }

    distance[source] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = findMinimum(distance, visited);

        if (u == -1)
            break;

        visited[u] = 1;

        for (int v = 0; v < V; v++) {
            if (!visited[v] &&
                graph[u][v] > 0 &&
                distance[u] != INF &&
                distance[u] + graph[u][v] < distance[v]) {

                distance[v] = distance[u] + graph[u][v];
                parent[v] = u;
            }
        }
    }

    if (distance[destination] == INF) {
        printf("\nNo route available.\n");
        return;
    }

    int path[V];
    int count = 0;
    int current = destination;

    while (current != -1) {
        path[count++] = current;
        current = parent[current];
    }

    printf("\n===== SHORTEST ROUTE =====\n");

    for (int i = count - 1; i >= 0; i--) {
        printf("%s", cities[path[i]]);

        if (i > 0)
            printf(" -> ");
    }

    printf("\nTotal Distance: %d km\n",
           distance[destination]);
}

int main() {
    int source, destination;

    printf("===== CITY ROUTE FINDER =====\n");

    printf("\nAvailable Cities:\n");

    for (int i = 0; i < V; i++) {
        printf("%d. %s\n", i, cities[i]);
    }

    printf("\nEnter source city number: ");
    scanf("%d", &source);

    printf("Enter destination city number: ");
    scanf("%d", &destination);

    if (source < 0 || source >= V ||
        destination < 0 || destination >= V) {
        printf("Invalid city selection!\n");
        return 1;
    }

    dijkstra(source, destination);

    return 0;
}
