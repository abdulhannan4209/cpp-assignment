#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <algorithm>

using namespace std;

// Structure representing each item in the priority queue
struct QueueNode {
    string vertex;
    int totalCost;
    vector<string> pathSoFar;

    // Comparator for min-heap
    bool operator>(const QueueNode& other) const {
        return totalCost > other.totalCost;
    }
};

// Function to compute shortest path using Dijkstra's algorithm
pair<int, vector<string>> findShortestPath(
    unordered_map<string, unordered_map<string, int>>& network,
    const string& source,
    const string& destination
) {
    priority_queue<QueueNode, vector<QueueNode>, greater<QueueNode>> minHeap;
    unordered_map<string, bool> visited;

    minHeap.push({source, 0, {source}});

    while (!minHeap.empty()) {
        QueueNode current = minHeap.top();
        minHeap.pop();

        if (visited[current.vertex]) continue;
        visited[current.vertex] = true;

        if (current.vertex == destination) {
            return {current.totalCost, current.pathSoFar};
        }

        // Explore neighbors
        for (const auto& neighborPair : network[current.vertex]) {
            const string& neighbor = neighborPair.first;
            int edgeWeight = neighborPair.second;

            if (!visited[neighbor]) {
                vector<string> newPath = current.pathSoFar;
                newPath.push_back(neighbor);
                minHeap.push({neighbor, current.totalCost + edgeWeight, newPath});
            }
        }
    }

    return {numeric_limits<int>::max(), {}};
}

int main() {
    // Customized example network
    unordered_map<string, unordered_map<string, int>> network = {
        {"Home", {{"School", 7}, {"Market", 2}}},
        {"School", {{"Home", 7}, {"Market", 3}, {"Park", 4}}},
        {"Market", {{"Home", 2}, {"School", 3}, {"Park", 6}, {"Library", 5}}},
        {"Park", {{"School", 4}, {"Market", 6}, {"Library", 1}}},
        {"Library", {{"Market", 5}, {"Park", 1}}}
    };

    string startPoint, endPoint;
    cout << "Enter starting point: ";
    cin >> startPoint;
    cout << "Enter ending point: ";
    cin >> endPoint;

    auto result = findShortestPath(network, startPoint, endPoint);
    int pathCost = result.first;
    vector<string> shortestPath = result.second;

    if (pathCost != numeric_limits<int>::max()) {
        cout << "Shortest path from " << startPoint << " to " << endPoint << ": ";
        for (size_t i = 0; i < shortestPath.size(); ++i) {
            cout << shortestPath[i];
            if (i != shortestPath.size() - 1) cout << " -> ";
        }
        cout << " with total cost " << pathCost << endl;
    } else {
        cout << "No available path from " << startPoint << " to " << endPoint << endl;
    }

    return 0;
}
