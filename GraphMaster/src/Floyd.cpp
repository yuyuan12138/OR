//
// Created by yuyuan on 2024/12/25.
//

#include "../include/Floyd.h"

std::vector<std::vector<int>> Floyd::solve(const bool is_strict) const {
    const auto& graph = this->_graph.lock();
    const size_t n = graph->_graph->nodes->_number_of_nodes;
    std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = graph->_graph->adjacency_matrix->matrix[i][j];
            if (result[i][j] == 0) {
                result[i][j] = std::numeric_limits<int>::max() / 2;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        result[i][i] = 0;
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                result[i][j] = std::min(result[i][j], result[i][k] + result[k][j]);
            }
        }
    }
    if (is_strict) {
        std::cout << "Floyd Distance Matrix: " << std::endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << result[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
    return result;
}

