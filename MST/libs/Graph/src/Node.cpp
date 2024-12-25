#include "../include/Node.h"

bool Nodes::is_repeatable_node(const std::string &name) {
    return this->mapping_name_to_idx.find(name) != this->mapping_name_to_idx.end();
}

void Nodes::add_node(const std::string& name, const int val) {
    if (is_repeatable_node(name)) {
        std::cout << "Error: existing repeatable node" << std::endl;
        std::cout << "Name: " << name << std::endl;
        return;
    }
    const auto new_node = std::make_shared<Node>(this->_number_of_nodes, name, val);
    this->_number_of_nodes += 1;
    _nodes.push_back(new_node);
    this->mapping_name_to_idx[new_node->name] = new_node->idx;
}

void Nodes::delete_node(const std::string& name) {
    if (!is_repeatable_node(name)) {
        std::cout << "Error: Node not found" << std::endl;
        return;
    }
    _nodes.erase(
        std::remove_if(
            _nodes.begin(), _nodes.end(),
            [&name](const std::shared_ptr<Node>& node) {
                return node->name == name;
            }
        ),
        _nodes.end()
    );
    this->mapping_name_to_idx.erase(name);
    this->_number_of_nodes = _nodes.size();

    // Update indices in mapping_name_to_idx
    for (size_t i = 0; i < _nodes.size(); ++i) {
        _nodes[i]->idx = static_cast<int>(i);
        this->mapping_name_to_idx[_nodes[i]->name] = static_cast<int>(i);
    }
}

void Nodes::show_nodes() const {
    for (const auto& node : this->_nodes) {
        std::cout << "Node idx: " << node->idx;
        std::cout << " Name: " << node->name;
        std::cout << " Value: " << node->val << std::endl;
    }
}
