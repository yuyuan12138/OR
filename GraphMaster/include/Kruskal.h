//
// Created by yuyuan on 2024/12/25.
//

#ifndef KRUSKAL_H
#define KRUSKAL_H

#include "Graph.h"
#include <algorithm>

class Kruskal {
private:
    int find(std::vector<int> &parent, int u);
    void unionSets(std::vector<int>& parent, std::vector<int>& rank, int u, int v);
    std::weak_ptr<Graph> graph_;

public:
    explicit Kruskal(const std::weak_ptr<Graph>& graph): graph_(graph){}

    int solve(bool is_strict = false);
};

#endif //KRUSKAL_H
