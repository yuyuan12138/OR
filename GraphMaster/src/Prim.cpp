//
// Created by yuyuan on 2024/12/25.
//

#include "../include/Prim.h"

int
Prim::solve() const {
    const std::shared_ptr<Graph> graph = graph_.lock();

    if (!graph) {
        std::cerr << "Graph is not available!" << std::endl;
        return -1;
    }

    const int n = graph->_graph->nodes->_number_of_nodes;

    int mstWeight = 0;

    using EdgePair = std::pair<int, int>;
    std::priority_queue<EdgePair, std::vector<EdgePair>, std::greater<>> minHeap;

    std::vector<bool> inMST(n, false);

    minHeap.emplace(0, 0);

    while (!minHeap.empty()) {
        const auto [weight, u] = minHeap.top();
        minHeap.pop();

        if (inMST[u]) {
            continue;
        }

        inMST[u] = true;
        mstWeight += weight;

        for (const auto& edge : graph->_graph->edges->_edges) {
            if (auto [from, to] = Graph::parse_edge_name(edge->name); graph->_graph->nodes->mapping_name_to_idx[from] == u ||
                                                                      graph->_graph->nodes->mapping_name_to_idx[to] == u){
                    const int v = (graph->_graph->nodes->mapping_name_to_idx[from] == u)
                                  ? graph->_graph->nodes->mapping_name_to_idx[to]
                                  : graph->_graph->nodes->mapping_name_to_idx[from];
                    const int edgeWeight = edge->val;

                    if (!inMST[v]) {
                        minHeap.emplace(edgeWeight, v);
                    }
                }
        }
    }

    if (std::any_of(inMST.begin(), inMST.end(), [](const bool visited) { return !visited; })) {
        std::cerr << "Graph is not connected!" << std::endl;
        return -1;
    }

    return mstWeight;
}

