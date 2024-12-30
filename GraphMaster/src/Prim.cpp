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
    std::vector<EdgePair> minHeap;
    minHeap.emplace_back(0, 0);  // 从第一个节点开始
    std::make_heap(minHeap.begin(), minHeap.end(), std::greater<>());

    std::vector<bool> inMST(n, false);
    std::vector<std::shared_ptr<Edge>> result;
    std::vector<std::vector<EdgePair>> adjList(n);

    // Create a mapping for node names to indices
    std::unordered_map<std::string, int> mapping_name_to_idx = graph->_graph->nodes->mapping_name_to_idx;
    const auto edges = graph->_graph->edges->_edges;
    for (const auto& edge: edges) {
        auto [from, to] = Graph::parse_edge_name(edge->name);
        int fromIdx = mapping_name_to_idx[from];
        int toIdx = mapping_name_to_idx[to];
        adjList[fromIdx].emplace_back(edge->val, toIdx);
        adjList[toIdx].emplace_back(edge->val, fromIdx);
    }

    while (!minHeap.empty()) {
        const auto [weight, u] = minHeap.front();  // Extract the edge with minimum weight
        std::pop_heap(minHeap.begin(), minHeap.end(), std::greater<>()); // 取出最小值
        minHeap.pop_back();

        // If vertex u is already in MST, continue to next
        if (inMST[u]) {
            continue;
        }

        // Add the vertex to the MST
        inMST[u] = true;
        mstWeight += weight;

        // Explore all edges from the current vertex u
        for (const auto &[weight, v] : adjList[u]) {
            if (!inMST[v]) {
                minHeap.emplace_back(weight, v);
                std::push_heap(minHeap.begin(), minHeap.end(), std::greater<>()); // 维持堆
            }
        }
    }

    // Ensure we visited all nodes
    if (std::any_of(inMST.begin(), inMST.end(), [](const bool visited) { return !visited; })) {
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

