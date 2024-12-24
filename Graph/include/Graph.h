
#ifndef _Graph_H_
#define _Graph_H_

#include "Edge.h"
#include "Node.h"

struct s_Graph
{
    std::shared_ptr<Nodes> nodes;
    std::shared_ptr<Edges> edges;
    std::vector<std::vector<int>> adjacency_matrix;
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