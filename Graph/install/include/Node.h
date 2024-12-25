#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>

struct Node {
    int idx;
    std::string name;
    int val;
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
