#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "Edge.h"
#include "Node.h"
#include <unordered_map>

struct Adjacency_Matrix {
    int size = 0;
    std::vector<std::string> name_of_all_nodes;
    std::vector<std::vector<int>> matrix;
};

class s_Graph {
public:
    bool is_directed = false;
    std::shared_ptr<Nodes> nodes = std::make_shared<Nodes>();
    std::shared_ptr<Edges> edges = std::make_shared<Edges>();
    std::shared_ptr<Adjacency_Matrix> adjacency_matrix = std::make_shared<Adjacency_Matrix>();
};

class Graph {
private:
    static std::pair<std::string, std::string> parse_edge_name(const std::string& edge_name);
    void validate_graph() const;
    bool is_directed;
    
public:

    Graph(): is_directed(false) {};
    explicit Graph(const bool _is_directed): is_directed(_is_directed) {};
    explicit Graph(const std::vector<std::pair<std::string, int>>& nodes) : is_directed(false){
        for (const auto&[fst, snd]: nodes) {
            add_node(fst, snd);
        }
    };
    explicit Graph(const bool _is_directed, const std::vector<std::pair<std::string, int>>& nodes): is_directed(_is_directed) {
        for (const auto&[fst, snd]: nodes) {
            add_node(fst, snd);
        }
    };
    
    std::shared_ptr<s_Graph> _graph = std::make_shared<s_Graph>();
    
    void add_node(const std::string& name, int val) const;
    void add_edge(const std::string& name, int val) const;
    void delete_node(const std::string& name) const;
    void delete_edge(const std::string& name) const;
    void show_graph() const;
    void add_nodes(const std::vector<std::pair<std::string, int>>& nodes) const;
    void add_edges(const std::vector<std::pair<std::string, int>>& edges) const;

};

#endif
