//
// Created by yuyuan on 2024/12/25.
//

#include "../include/Prim.h"

int Prim::solve(const bool is_strict) const {
    const auto graph = graph_.lock();

    if (!graph) {
        std::cerr << "Graph is not available!" << std::endl;
        return -1;
    }

    const int n = graph->_graph->nodes->_number_of_nodes;

    int mstWeight = 0;

    using EdgePair = std::pair<int, int>; // (weight, vertex)
    std::priority_queue<EdgePair, std::vector<EdgePair>, std::greater<>> minHeap;

    std::vector<bool> inMST(n, false);
    std::vector<std::shared_ptr<Edge>> result;

    // Create a mapping for node names to indices
    std::unordered_map<std::string, int> mapping_name_to_idx = graph->_graph->nodes->mapping_name_to_idx;

    // Prepare edge indices
    size_t edgeCount = graph->_graph->edges->_edges.size();
    std::vector<int> from_indices(edgeCount);
    std::vector<int> to_indices(edgeCount);
    std::vector<int> edge_weights(edgeCount);

    for (size_t i = 0; i < edgeCount; ++i) {
        auto [from, to] = Graph::parse_edge_name(graph->_graph->edges->_edges[i]->name);
        from_indices[i] = mapping_name_to_idx[from];
        to_indices[i] = mapping_name_to_idx[to];
        edge_weights[i] = graph->_graph->edges->_edges[i]->val;
    }

    // Start from the first node (index 0)
    minHeap.emplace(0, 0);

    while (!minHeap.empty()) {
        const auto [weight, u] = minHeap.top();  // Extract the edge with minimum weight
        minHeap.pop();

        // If vertex u is already in MST, continue to next
        if (inMST[u]) {
            continue;
        }

        // Add the vertex to the MST
        inMST[u] = true;
        mstWeight += weight;

        // Record the edge, but only if weight > 0 and MST is meant to be strict
        if (is_strict && weight > 0) {
            // Find and record the edge corresponding to this vertex addition
            for (size_t i = 0; i < edgeCount; ++i) {
                if ((from_indices[i] == u || to_indices[i] == u) && !inMST[(from_indices[i] == u) ? to_indices[i] : from_indices[i]]) {
                    result.push_back(graph->_graph->edges->_edges[i]);
                    break;  // Only add one edge for this step
                }
            }
        }

        // Explore all edges from the current vertex u
        for (size_t i = 0; i < edgeCount; ++i) {
            if (from_indices[i] == u && !inMST[to_indices[i]]) {
                minHeap.emplace(edge_weights[i], to_indices[i]);
            } else if (to_indices[i] == u && !inMST[from_indices[i]]) {
                minHeap.emplace(edge_weights[i], from_indices[i]);
            }
        }
    }

    // Ensure we visited all nodes
    if (std::any_of(inMST.begin(), inMST.end(), [](bool visited) { return !visited; })) {
        std::cerr << "Graph is not connected!" << std::endl;
        return -1;
    }

    // Output resulting MST edges if is_strict is true
    if (is_strict) {
        std::cout << "Prim MST Path:" << std::endl;
        for (const auto& edge : result) {
            std::cout << "Edge idx: "<< edge->idx << " Edge name: " << edge->name << " Edge value: " << edge->val << std::endl;
        }
    }

    return mstWeight;
}

