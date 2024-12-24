#include "../include/Edge.h"

void
Edges::add_edge(const std::string& name, const int val){
    const auto new_edge = std::make_shared<Edge>();
    new_edge->idx = this->_number_of_edges;
    new_edge->name = name;
    new_edge->val = val;
    this->_number_of_edges += 1;
    this->_edges.push_back(new_edge);
}

void 
Edges::delete_edge(const std::string& name) {
    this->_edges.erase(
        std::remove_if(
            _edges.begin(), _edges.end(),
            [&name](const std::shared_ptr<Edge>& edge) {
                if (edge->name == name) {
                    return true;
                }
                return false;
            }
        ),
        _edges.end()
    );
}

void
Edges::show_edges(){
    for(const auto& edge: this->_edges){
        std::cout << "Edge: "<< edge->idx << std::endl;
        std::cout << "Name: "<< edge->name << std::endl;
        std::cout << "Value: " << edge->val << std::endl;
    }
}