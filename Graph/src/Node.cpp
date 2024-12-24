#include "../include/Node.h"

void
Nodes::add_node(const std::string& name, const int val)
{
    std::shared_ptr<Node> new_node = std::make_shared<Node>();
    new_node->idx = this->_number_of_nodes;
    new_node->name = name;
    new_node->val = val;
    this->_number_of_nodes += 1;
    _nodes.push_back(new_node);
}

void 
Nodes::delete_node(const std::string& name) {
    _nodes.erase(
        std::remove_if(
            _nodes.begin(), _nodes.end(),
            [&name](const std::shared_ptr<Node>& node) {
                if (node->name == name) {
                    return true;
                }
                return false;
            }
        ),
        _nodes.end()
    );
}

void
Nodes::show_nodes(){
    for(auto node: this->_nodes){
        std::cout << "Node: "<< node->idx << std::endl;
        std::cout << "Name: "<< node->name << std::endl;
        std::cout << "Value: " << node->val << std::endl;
    }
}