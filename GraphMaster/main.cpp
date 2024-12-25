#include "main.h"


int main() {
    const auto graph = std::make_shared<Graph>();
    std::vector<std::pair<std::string, int>> nodes;
    nodes.emplace_back("A", 1);
    nodes.emplace_back("B", 1);
    nodes.emplace_back("C", 1);
    nodes.emplace_back("D", 1);
    graph->add_nodes(nodes);

    std::vector<std::pair<std::string, int>> edges;
    edges.emplace_back("A-B", 10);
    edges.emplace_back("A-C", 6);
    edges.emplace_back("A-D", 5);
    edges.emplace_back("B-D", 15);
    edges.emplace_back("C-D", 4);
    graph->add_edges(edges);
    const auto kruskal = std::make_shared<Kruskal>(graph);
    const int mst = kruskal->solve();

    const auto prim = std::make_shared<Prim>(graph);

    const int mst2 = prim->solve();
    std::cout << mst << std::endl;
    std::cout << mst2 << std::endl;

    std::cout << graph->is_graph_connected() << std::endl;

    graph->delete_edge("B-D");

    std::cout << graph->is_graph_connected() << std::endl;
    graph->delete_edge("A-B");

    std::cout << graph->is_graph_connected() << std::endl;

    // graph->show_graph();
    return 0;
}