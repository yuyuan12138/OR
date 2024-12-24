#include "../include/Graph.h"

void
Graph::add_node(const std::string& name, const int val) const {
    // update data in _graph
    this->_graph->nodes->add_node(name, val);
    // update namelist
    this->_graph->adjacency_matrix->name_of_all_nodes.push_back(name);

    // update size
    this->_graph->adjacency_matrix->size += 1;

    // new matrix
    std::vector<std::vector<int>> new_matrix(this->_graph->adjacency_matrix->size, std::vector<int>(this->_graph->adjacency_matrix->size));
    for(int i = 0; i < this->_graph->adjacency_matrix->size - 1; i++){
        for(int j = 0; j < this->_graph->adjacency_matrix->size - 1; j++){
            new_matrix[i][j] = this->_graph->adjacency_matrix->matrix[i][j];
        }
    }
    this->_graph->adjacency_matrix->matrix = new_matrix;
}

// TODO
void
Graph::delete_node(const std::string &name) const {
    this->_graph->nodes->delete_node(name);
    this->_graph->adjacency_matrix->name_of_all_nodes.erase(
        std::remove_if(
            this->_graph->adjacency_matrix->name_of_all_nodes.begin(), this->_graph->adjacency_matrix->name_of_all_nodes.end(),
            [&name](const std::string& n) {
                if (n == name) {
                    return true;
                }
                return false;
            }
        ),
        this->_graph->adjacency_matrix->name_of_all_nodes.end()
    );

    this->_graph->adjacency_matrix->size -= 1;
    std::vector<std::vector<int>> new_matrix(this->_graph->adjacency_matrix->size, std::vector<int>(this->_graph->adjacency_matrix->size));

}

