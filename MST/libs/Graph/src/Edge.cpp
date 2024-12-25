#include "../include/Edge.h"

void Edges::add_edge(const std::string& name, const int val) {
    const auto new_edge = std::make_shared<Edge>();
    new_edge->idx = this->_number_of_edges;
    new_edge->name = name;
    new_edge->val = val;
    this->_number_of_edges += 1;
    this->_edges.push_back(new_edge);
}

void Edges::delete_edge(const std::string& name) {
    this->_edges.erase(
        std::remove_if(
            _edges.begin(), _edges.end(),
            [&name](const std::shared_ptr<Edge>& edge) {
                return edge->name == name;
            }
        ),
        _edges.end()
    );
    this->_number_of_edges = this->_edges.size();
    // Update indices for the remaining edges
    for (size_t i = 0; i < _edges.size(); ++i) {
        _edges[i]->idx = static_cast<int>(i);
    }
}

void Edges::show_edges() const {
    for (const auto& edge : this->_edges) {
        std::cout << "Edge: " << edge->idx;
        std::cout << " Name: " << edge->name;
        std::cout << " Value: " << edge->val << std::endl;
    }
}
