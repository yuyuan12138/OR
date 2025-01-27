#ifndef GRAPH_H
#define GRAPH_H

#include "Edge.h"
#include "Node.h"
#include <unordered_map>

struct Adjacency_Matrix {
    int size = 0;
    std::vector<std::string> name_of_all_nodes;
    std::vector<std::vector<int>> matrix;
};

struct Adjacency_List {
    int size = 0;
    std::vector<std::vector<std::pair<int, std::string>>> list; // 每个节点的邻接节点和边权重
};

class s_Graph {
public:
    bool is_directed = false;
    std::shared_ptr<Nodes> nodes = std::make_shared<Nodes>();
    std::shared_ptr<Edges> edges = std::make_shared<Edges>();
    std::shared_ptr<Adjacency_Matrix> adjacency_matrix = std::make_shared<Adjacency_Matrix>();
    std::shared_ptr<Adjacency_List> adjacency_list = std::make_shared<Adjacency_List>();
};

class Graph {
private:

    void validate_graph() const;
    void is_graph_connected_dfs(size_t vertex, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) const;
    bool is_directed;
    
public:
    static std::pair<std::string, std::string> parse_edge_name(const std::string& edge_name);
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
    void add_edge(const std::string& name, const std::string& from, const std::string& to, int val) const;
    void delete_node(const std::string& name) const;
    void delete_edge(const std::string& name) const;
    void show_graph() const;
    void add_nodes(const std::vector<std::pair<std::string, int>>& nodes) const;
    void add_edges(const std::vector<std::pair<std::string, int>>& edges) const;
    void add_edges(const std::vector<std::tuple<std::string, std::string, std::string, int>>& edges) const;

    [[nodiscard]] bool is_graph_connected() const;

};

#endif
