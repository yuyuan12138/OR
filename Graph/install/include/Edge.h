#ifndef _EDGE_H_
#define _EDGE_H_

#include <vector>
#include "Node.h"
#include <memory>
#include <string>

struct Edge {
    int idx;
    int val;
    std::string name;
};

class Edges {
public:
    Edges() : _number_of_edges(0) {};
    int _number_of_edges;
    std::vector<std::shared_ptr<Edge>> _edges;

    void add_edge(const std::string& name, int val);
    void delete_edge(const std::string& name);

    void show_edges() const;
};

#endif
