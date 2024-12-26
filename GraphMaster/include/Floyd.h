//
// Created by yuyuan on 2024/12/25.
//

#ifndef FLOYD_H
#define FLOYD_H

#include "Graph.h"
#include <limits>

class Floyd {
private:
    std::weak_ptr<Graph> _graph;
public:
    explicit Floyd(const std::weak_ptr<Graph>& graph): _graph(graph) {};
    [[nodiscard]] std::vector<std::vector<int>>  solve(bool is_strict = false) const;
};

#endif //FLOYD_H
