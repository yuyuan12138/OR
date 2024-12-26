//
// Created by yuyuan on 2024/12/25.
//

#include "../include/Kruskal.h"

int
Kruskal::find(std::vector<int>& parent, int u){
    if (parent[u] != u) {
        parent[u] = find(parent, parent[u]);
    }
    return parent[u];
}

void
Kruskal::unionSets(std::vector<int>& parent, std::vector<int>& rank, const int u, const int v) {
    const int rootU = find(parent, u);

    if (const int rootV = find(parent, v); rootU != rootV) {

        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

int
Kruskal::solve(const bool is_strict) {
    const std::shared_ptr<Graph> graph = graph_.lock();

    if (!graph) {
        std::cerr << "Graph is not available!" << std::endl;
        return -1;
    }
    const int n = graph->_graph->nodes->_number_of_nodes;

    std::vector<int> parent(n);
    std::vector<int> rank(n, 0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    std::vector<std::shared_ptr<Edge>> edges = graph->_graph->edges->_edges;
    std::sort(edges.begin(), edges.end(),
    [this](const std::shared_ptr<Edge>&a, const std::shared_ptr<Edge>& b) {
        return a->val < b->val;
    });
    std::vector<std::shared_ptr<Edge>> result;
    int mstWeight = 0;
    for (const auto& edge : edges) {
        auto [from, to] = Graph::parse_edge_name(edge->name);
        const int u = graph->_graph->nodes->mapping_name_to_idx[from];

        if (const int v = graph->_graph->nodes->mapping_name_to_idx[to]; find(parent, u) != find(parent, v)) {

            unionSets(parent, rank, u, v);
            mstWeight += edge->val;
            if (is_strict) {
                result.push_back(edge);
            }
        }
    }
    if (is_strict) {
        std::cout << "Kruskal MST Path:" << std::endl;
        for (const auto& edge : result) {
            std::cout << "Edge idx: "<< edge->idx << " Edge name: " << edge->name << " Edge value: " << edge->val << std::endl;
        }
    }
    return mstWeight;
}



