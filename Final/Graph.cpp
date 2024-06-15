#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>
#include <cassert>
#include <sstream>  // For string manipulation

class Graph {
private:
    std::map<int, std::vector<std::pair<int, int> > > adjList;

public:
    void add_vertex(int vertex) {
        if (adjList.find(vertex) == adjList.end()) {
            adjList[vertex] = std::vector<std::pair<int, int> >();
        }
    }

    void add_edge(int source, int destination, int weight) {
        if (adjList.find(source) == adjList.end() || adjList.find(destination) == adjList.end()) {
            throw std::runtime_error("One or both vertices not found");
        }
        adjList[source].push_back(std::make_pair(destination, weight));
        adjList[destination].push_back(std::make_pair(source, weight)); // Assuming undirected graph
    }

    std::map<int, int> shortest_path(int start) {
        if (adjList.find(start) == adjList.end()) {
            throw std::runtime_error("Start vertex not found");
        }

        std::set<std::pair<int, int> > queue;
        std::map<int, int> distances;
        for (auto& node : adjList) {
            distances[node.first] = std::numeric_limits<int>::max();
        }
        distances[start] = 0;
        queue.insert(std::make_pair(0, start));

        while (!queue.empty()) {
            int current = queue.begin()->second;
            queue.erase(queue.begin());

            for (auto& edge : adjList[current]) {
                int neighbor = edge.first;
                int weight = edge.second;
                if (distances[current] + weight < distances[neighbor]) {
                    queue.erase(std::make_pair(distances[neighbor], neighbor));
                    distances[neighbor] = distances[current] + weight;
                    queue.insert(std::make_pair(distances[neighbor], neighbor));
                }
            }
        }
        return distances;
    }

    std::vector<std::pair<int, std::pair<int, int> > > min_span_tree(int start) {
        if (adjList.empty()) {
            throw std::runtime_error("Graph is empty");
        }
        if (adjList.find(start) == adjList.end()) {
            throw std::runtime_error("Start vertex not found");
        }

        std::set<std::pair<int, int> > queue;
        std::map<int, int> key;
        std::map<int, int> parent;
        std::vector<bool> inMST(adjList.size(), false);

        for (auto& node : adjList) {
            key[node.first] = std::numeric_limits<int>::max();
            parent[node.first] = -1;
        }

        queue.insert(std::make_pair(0, start));
        key[start] = 0;

        while (!queue.empty()) {
            int u = queue.begin()->second;
            queue.erase(queue.begin());
            inMST[u] = true;

            for (auto& i : adjList[u]) {
                int v = i.first;
                int weight = i.second;

                if (!inMST[v] && key[v] > weight) {
                    queue.erase(std::make_pair(key[v], v));
                    key[v] = weight;
                    queue.insert(std::make_pair(key[v], v));
                    parent[v] = u;
                }
            }
        }

        std::vector<std::pair<int, std::pair<int, int> > > mst_edges;
        for (auto& vertex : adjList) {
            int v = vertex.first;
            if (parent[v] != -1) {
                mst_edges.push_back(std::make_pair(key[v], std::make_pair(parent[v], v)));
            }
        }
        return mst_edges;
    }

    void display_ascii() {
        for (auto& vertex : adjList) {
            std::cout << vertex.first << " -> ";
            std::stringstream ss;
            for (auto& edge : vertex.second) {
                ss << edge.first << "[" << edge.second << "] ";
            }
            std::cout << ss.str() << std::endl;
        }
    }
};

int main() {
    Graph g;

    // Constructing a simple example graph
    g.add_vertex(1);
    g.add_vertex(2);
    g.add_vertex(3);
    g.add_edge(1, 2, 1);
    g.add_edge(1, 3, 4);
    g.add_edge(2, 3, 2);

    // Display ASCII art of the graph
    g.display_ascii();

    return 0;
}
