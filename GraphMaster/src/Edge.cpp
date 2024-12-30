#include "../include/Edge.h"

void Edges::add_edge(const std::string& edge_name, const int edge_value) {
    const auto new_edge = std::make_shared<Edge>(this->_number_of_edges, edge_value, edge_name);
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

    for (size_t i = 0; i < _edges.size(); ++i) {
        _edges[i]->idx = static_cast<int>(i);
    }
}

void Edges::show_edges() const {
    for (const auto& edge : this->_edges) {
        std::cout << "Edge idx: " << edge->idx;
        std::cout << " Name: " << edge->name;
        std::cout << " Value: " << edge->val << std::endl;
    }
}
