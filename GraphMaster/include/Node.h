#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

struct Node {
    int idx;
    std::string name;
    int val;

    Node(const int idx, std::string name, const int val): idx(idx), name(std::move(name)), val(val){};
};

class Nodes {
public:
    bool is_repeatable_node(const std::string& name);
    std::unordered_map<std::string, int> mapping_name_to_idx;
    Nodes() = default;

    int _number_of_nodes = 0;
    std::vector<std::shared_ptr<Node>> _nodes;

    void add_node(const std::string& name, int val);
    void delete_node(const std::string& name);
    void show_nodes() const;
};

#endif
