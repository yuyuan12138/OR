#include "main.h"

void print_options(cxxopts::Options& options, const int argc, char* argv[]) {
    // 定义命令行选项
    options.add_options()
        ("h,help", "Show help")  // 帮助选项
        ("f,file", "Input file", cxxopts::value<std::string>())  // 文件参数
        ("v,verbose", "Enable verbose output")  // 详细输出选项
        ("count", "Count", cxxopts::value<int>()->default_value("1")); // 计数参数，默认为 1

    // 解析命令行参数
    const auto result = options.parse(argc, argv);

    // 如果用户请求帮助，显示帮助信息
    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        return ;
    }

    // 获取参数值
    std::string file;
    if (result.count("file")) {
        file = result["file"].as<std::string>();
    }

    bool verbose = result.count("verbose") > 0;
    int count = result["count"].as<int>();

    // 使用参数
    std::cout << "File: " << file << std::endl;
    std::cout << "Verbose: " << verbose << std::endl;
    std::cout << "Count: " << count << std::endl;
}

int main(const int argc, char* argv[]) {
    cxxopts::Options options("GraphMaster", "A simple program using cxxopts");
    print_options(options, argc, argv);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    const auto graph = std::make_shared<Graph>();
    std::string filename = "..\\data\\heat.in"; // 文件名
    std::ifstream infile(filename);

    if (!infile) {
        std::cerr << "can not open file: " << filename << std::endl;
        return 1;
    }

    // 用于存储第一行数据
    int n, m;
    infile >> n >> m;

    // 用于存储后续行数据的容器
    std::vector<std::tuple<int, int, int>> data;
    data.reserve(m);
    int col1, col2, col3;

    // 读取后续行数据
    while (infile >> col1 >> col2 >> col3) {
     data.emplace_back(col1, col2, col3);
    }

    infile.close();

    std::vector<std::pair<std::string, int>> nodes;
    nodes.reserve(n);

    for (int i = 1; i <= n; i++) {
        nodes.emplace_back(std::to_string(i), i);
    }
    graph->add_nodes(nodes);


    std::vector<std::pair<std::string, int>> edges;
    edges.reserve(data.size());
    for (const auto& [c1, c2, c3] : data) {
     std::ostringstream edge_name_stream;
     edge_name_stream << c1 << "-" << c2; // 此处减少了重复转换
     edges.emplace_back(edge_name_stream.str(), c3);
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
