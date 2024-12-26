//
// Created by yuyuan on 2024/12/25.
//

#ifndef PRIM_H
#define PRIM_H

#include "Graph.h"
#include <algorithm>
#include <queue>
#include <limits>

class Prim {
public:
    explicit Prim(const std::weak_ptr<Graph>& graph) : graph_(graph) {};
    [[nodiscard]] int solve(bool is_strict = false) const;
private:
    std::weak_ptr<Graph> graph_;
};

#endif //PRIM_H
