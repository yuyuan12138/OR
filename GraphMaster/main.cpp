#include "main.h"


std::vector<std::tuple<int, int, int>> read_files(){
    std::string filename = "C:\\Users\\yuyuan\\Desktop\\project\\OR\\GraphMaster\\data\\heat.in"; // 文件名
    std::ifstream infile(filename);

    if (!infile) {
        std::cerr << "can not open file: " << filename << std::endl;
    }

    // 用于存储第一行数据
    int year, value;
    infile >> year >> value;

    // 打印第一行数据
    std::cout << "first data: " << year << " " << value << std::endl;

    // 用于存储后续行数据的容器
    std::vector<std::tuple<int, int, int>> data;
    int col1, col2, col3;

    // 读取后续行数据
    while (infile >> col1 >> col2 >> col3) {
        data.emplace_back(col1, col2, col3);
    }

    infile.close();
    return data;
    // std::cout << "data:" << std::endl;
    // for (const auto& [c1, c2, c3] : data) {
    //     std::cout << c1 << " " << c2 << " " << c3 << std::endl;
    // }
}

int main() {
    const auto graph = std::make_shared<Graph>();
    std::string filename = "C:\\Users\\yuyuan\\Desktop\\project\\OR\\GraphMaster\\data\\heat.in"; // 文件名
    std::ifstream infile(filename);

    if (!infile) {
        std::cerr << "can not open file: " << filename << std::endl;
    }

    // 用于存储第一行数据
    int n, m;
    infile >> n >> m;

    // 用于存储后续行数据的容器
    std::vector<std::tuple<int, int, int>> data;
    int col1, col2, col3;

    // 读取后续行数据
    while (infile >> col1 >> col2 >> col3) {
        data.emplace_back(col1, col2, col3);
    }

    infile.close();

    std::vector<std::pair<std::string, int>> nodes;

    for (int i = 1; i <= n; i++) {
        nodes.emplace_back(std::to_string(i), i);
    }
    graph->add_nodes(nodes);


    std::vector<std::pair<std::string, int>> edges;
    for (const auto& [c1, c2, c3] : data) {
        edges.emplace_back(std::to_string(c1) + "-" + std::to_string(c2), c3);
    }
    graph->add_edges(edges);

    std::cout << graph->is_graph_connected() << std::endl;

    const auto kruskal = std::make_shared<Kruskal>(graph);
    const int mst = kruskal->solve(false);
    std::cout << mst << std::endl;
    const auto prim = std::make_shared<Prim>(graph);

    const int mst2 = prim->solve(false);
    std::cout << mst2 << std::endl;

    // std::vector<std::pair<std::string, int>> nodes;
    // nodes.emplace_back("A", 1);
    // nodes.emplace_back("B", 1);
    // nodes.emplace_back("C", 1);
    // nodes.emplace_back("D", 1);
    // graph->add_nodes(nodes);
    //
    // std::vector<std::pair<std::string, int>> edges;
    // edges.emplace_back("A-B", 10);
    // edges.emplace_back("A-C", 6);
    // edges.emplace_back("A-D", 5);
    // edges.emplace_back("B-D", 15);
    // edges.emplace_back("C-D", 4);
    // graph->add_edges(edges);
    // const auto kruskal = std::make_shared<Kruskal>(graph);
    // const int mst = kruskal->solve(true);
    //
    // const auto prim = std::make_shared<Prim>(graph);
    //
    // const int mst2 = prim->solve(true);
    // std::cout << mst << std::endl;
    // std::cout << mst2 << std::endl;
    //
    // std::cout << graph->is_graph_connected() << std::endl;
    //
    // // graph->delete_edge("B-D");
    // //
    // // std::cout << graph->is_graph_connected() << std::endl;
    // // graph->delete_edge("A-B");
    // //
    // // std::cout << graph->is_graph_connected() << std::endl;
    //
    // const auto floyd = Floyd(graph);
    // const auto dis = floyd.solve(true);
    // // graph->show_graph();
    return 0;
}