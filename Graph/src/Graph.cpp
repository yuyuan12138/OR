#include "../include/Graph.h"

void
Graph::add_node(const std::string& name, int val){
    // std::cout << "-------" << std::endl;
    this->_graph->nodes->add_node(name, val);
    // update data in _graph
    // std::cout << "-------" << std::endl;
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