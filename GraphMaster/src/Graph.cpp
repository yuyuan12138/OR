#include "../include/Graph.h"
#include <stdexcept>

void Graph::add_node(const std::string& name, const int val) const {
    if (_graph->nodes->is_repeatable_node(name)) {
        std::cout << "Error: Node already exists!" << std::endl;
        return;
    }
    _graph->nodes->add_node(name, val);
    _graph->adjacency_matrix->name_of_all_nodes.push_back(name);
    _graph->adjacency_matrix->size = _graph->nodes->_number_of_nodes;

    std::vector<std::vector<int>> new_matrix(_graph->adjacency_matrix->size, std::vector<int>(_graph->adjacency_matrix->size));
    for (int i = 0; i < _graph->adjacency_matrix->size - 1; ++i) {
        for (int j = 0; j < _graph->adjacency_matrix->size - 1; ++j) {
            new_matrix[i][j] = _graph->adjacency_matrix->matrix[i][j];
        }
    }
    _graph->adjacency_matrix->matrix = new_matrix;
}

void Graph::delete_node(const std::string &name) const {
    if (!_graph->nodes->is_repeatable_node(name)) {
        std::cout << "Error: Node not found" << std::endl;
        return;
    }
    _graph->nodes->delete_node(name);

    const auto it = std::find(_graph->adjacency_matrix->name_of_all_nodes.begin(),
                              _graph->adjacency_matrix->name_of_all_nodes.end(), name);
    if (it == _graph->adjacency_matrix->name_of_all_nodes.end()) return;
    const int index = std::distance(_graph->adjacency_matrix->name_of_all_nodes.begin(), it);

    _graph->adjacency_matrix->matrix.erase(_graph->adjacency_matrix->matrix.begin() + index);
    for (auto &row : _graph->adjacency_matrix->matrix) {
        row.erase(row.begin() + index);
    }

    _graph->adjacency_matrix->name_of_all_nodes.erase(it);
    _graph->adjacency_matrix->size -= 1;

    // Validate graph integrity after deletion
    const_cast<Graph*>(this)->validate_graph();
}

void Graph::delete_edge(const std::string& name) const {
    _graph->edges->delete_edge(name);

    auto& matrix = _graph->adjacency_matrix->matrix;
    const auto& names = _graph->adjacency_matrix->name_of_all_nodes;

    for (int i = 0; i < names.size(); ++i) {
        for (int j = 0; j < names.size(); ++j) {
            if (matrix[i][j] != 0) {
                if (std::string expected_name = names[i] + "-" + names[j]; expected_name == name) {
                    matrix[i][j] = 0;
                    if (!_graph->is_directed) {
                        matrix[j][i] = 0;
                    }
                }
            }
        }
    }
}

std::pair<std::string, std::string> Graph::parse_edge_name(const std::string& edge_name) {
    const size_t delimiter_pos = edge_name.find('-');
    if (delimiter_pos == std::string::npos) {
        throw std::invalid_argument("Invalid edge name format. Expected format: from-to");
    }

    std::string from = edge_name.substr(0, delimiter_pos);
    std::string to = edge_name.substr(delimiter_pos + 1);

    return {from, to};
}

void Graph::add_edge(const std::string& name, const int val) const {
    try {
        auto [from, to] = parse_edge_name(name);

        const auto& nodes = _graph->nodes;
        if (!nodes->is_repeatable_node(from) || !nodes->is_repeatable_node(to)) {
            std::cout << "Error: One or both nodes do not exist!" << std::endl;
            return;
        }

        const int from_idx = nodes->mapping_name_to_idx[from];
        const int to_idx = nodes->mapping_name_to_idx[to];

        auto& matrix = _graph->adjacency_matrix->matrix;
        if (from_idx >= _graph->adjacency_matrix->size || to_idx >= _graph->adjacency_matrix->size) {
            std::cout << "Error: Invalid indices for adjacency matrix!" << std::endl;
            return;
        }
        matrix[from_idx][to_idx] = val;

        if (!_graph->is_directed) {
            matrix[to_idx][from_idx] = val;
        }

        _graph->edges->add_edge(name, val);
    } catch (const std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void Graph::validate_graph() const {
    auto& edges = _graph->edges->_edges;
    auto& nodes = _graph->nodes->mapping_name_to_idx;
    auto& matrix = _graph->adjacency_matrix->matrix;

    // Remove edges that no longer connect valid nodes
    edges.erase(
        std::remove_if(edges.begin(), edges.end(),
            [&nodes, &matrix, this](const std::shared_ptr<Edge>& edge) {
                auto [from, to] = parse_edge_name(edge->name);
                // Check if both nodes are valid and findable in the adjacency matrix and mapping
                return (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end() ||
                        matrix[nodes[from]][nodes[to]] == 0);
            }),
        edges.end()
    );

    // Update number of edges after cleanup
    _graph->edges->_number_of_edges = edges.size();

    // Reassign edge indices after deletion
    for (size_t i = 0; i < edges.size(); ++i) {
        edges[i]->idx = static_cast<int>(i);
    }
}

void
Graph::show_graph() const {
    this->_graph->edges->show_edges();
    this->_graph->nodes->show_nodes();
    const size_t n = this->_graph->adjacency_matrix->matrix.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            std::cout << this->_graph->adjacency_matrix->matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void
Graph::add_nodes(const std::vector<std::pair<std::string, int>>& nodes) const {
    for (const auto&[fst, snd] : nodes) {
        this->add_node(fst, snd);
    }
}

void
Graph::add_edges(const std::vector<std::pair<std::string, int>>& edges) const {
    for (const auto&[fst, snd]: edges) {
        this->add_edge(fst, snd);
    }
}

bool
Graph::is_graph_connected() const {
    const auto& adj = this->_graph->adjacency_matrix->matrix;
    const int size = this->_graph->adjacency_matrix->size;
    std::vector<bool> visited(size, false);
    this->is_graph_connected_dfs(0, adj, visited);
    return all_of(visited.begin(), visited.end(), [](const bool v) { return v; });
}

void
Graph::is_graph_connected_dfs(const int vertex, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) const {
    visited[vertex] = true;
    for (size_t i = 0; i < adj[vertex].size(); ++i) {
        if (adj[vertex][i] >= 1 && !visited[i]) {
            Graph::is_graph_connected_dfs(i, adj, visited);
        }
    }
}


