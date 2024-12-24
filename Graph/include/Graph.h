
#ifndef _Graph_H_
#define _Graph_H_

#include "Edge.h"
#include "Node.h"
#include <unordered_map>


struct Adjacency_Matrix{
    int size;
    std::vector<std::string> name_of_all_nodes;
    std::vector<std::vector<int>> matrix;
};
class s_Graph
{
public:
    std::shared_ptr<Nodes> nodes = std::make_shared<Nodes>();
    std::shared_ptr<Edges> edges = std::make_shared<Edges>();
    std::shared_ptr<Adjacency_Matrix> adjacency_matrix = std::make_shared<Adjacency_Matrix>();
};


class Graph{
public:
    std::shared_ptr<s_Graph> _graph = std::make_shared<s_Graph>();

    void add_node(const std::string& name, int val);
    void add_edge(const std::string& name, int val);
    void delete_node(const std::string& name);
    void delete_edge(const std::string& name);
    void show_graph();
};


#endif