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
            for (const auto& edge : graph->_graph->edges->_edges) {
                auto [from, to] = Graph::parse_edge_name(edge->name);
                int fromIdx = graph->_graph->nodes->mapping_name_to_idx[from];
                int toIdx = graph->_graph->nodes->mapping_name_to_idx[to];

                if ((fromIdx == u || toIdx == u) && !inMST[(fromIdx == u) ? toIdx : fromIdx]) {
                    result.push_back(edge);
                    break;  // Only add one edge for this step
                }
            }
        }

        // Explore all edges from the current vertex u
        for (const auto& edge : graph->_graph->edges->_edges) {
            auto [from, to] = Graph::parse_edge_name(edge->name);
            int fromIdx = graph->_graph->nodes->mapping_name_to_idx[from];
            int toIdx = graph->_graph->nodes->mapping_name_to_idx[to];

            // Check if either of the vertices can be connected
            if (fromIdx == u && !inMST[toIdx]) {
                minHeap.emplace(edge->val, toIdx);
            } else if (toIdx == u && !inMST[fromIdx]) {
                minHeap.emplace(edge->val, fromIdx);
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

