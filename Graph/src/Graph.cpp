#include "../include/Graph.h"

void
Graph::add_node(const std::string& name, int val){
    this->_graph->nodes->add_node(name, val);
}