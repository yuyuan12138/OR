#ifndef EDGE_H
#define EDGE_H

#include <utility>
#include <vector>
#include "Node.h"
#include <memory>
#include <string>

struct Edge {
    int idx;
    int val;
    std::string name;

    Edge(const int idx, const int val, std::string name): idx(idx), val(val), name(std::move(name)){};
};

class Edges {
public:
    Edges() : _number_of_edges(0) {};
    size_t _number_of_edges;
    std::vector<std::shared_ptr<Edge>> _edges;

    void add_edge(const std::string& edge_name, int edge_value);
    void delete_edge(const std::string& name);

    void show_edges() const;
};

#endif
