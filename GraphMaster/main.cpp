#include "main.h"

cxxopts::ParseResult print_options(cxxopts::Options& options, const int argc, char* argv[]) {
    options.add_options()
        ("h,help", "Show help")  // 帮助选项
        ("f,file", "Input file", cxxopts::value<std::string>())  // 文件参数
        ("v,verbose", "Enable verbose output")  // 详细输出选项
        ("count", "Count", cxxopts::value<int>()->default_value("1"))
        ("MST", "MST")
    ;

    const auto result = options.parse(argc, argv);
    return result;
}

int main(const int argc, char* argv[]) {

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cxxopts::Options options("GraphMaster", "A simple program using cxxopts");
    const auto result = print_options(options, argc, argv);

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
    }

    const bool is_strict = result.count("verbose") > 0;

    std::string filename;
    if (result.count("file")) {
        filename = result["file"].as<std::string>();
    }

    const auto graph = std::make_shared<Graph>();

    if (filename.empty()) {
        filename = "..\\data\\heat.in";
    }

    std::ifstream infile(filename);
    if (!infile) {
        std::cerr << "can not open file: " << filename << std::endl;
        return 1;
    }
    int n, m;
    infile >> n >> m;
    std::vector<std::tuple<int, int, int>> data;
    data.reserve(m);
    int col1, col2, col3;
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

    std::vector<std::tuple<std::string, std::string, std::string, int>> edges;
    edges.reserve(data.size());
    for (const auto& [c1, c2, c3] : data) {
        std::ostringstream edge_name_stream;
        edge_name_stream << c1 << "-" << c2; // 此处减少了重复转换
        edges.emplace_back(edge_name_stream.str(), std::to_string(c1), std::to_string(c2), c3);
    }
    graph->add_edges(edges);

    std::cout << graph->is_graph_connected() << std::endl;

    const auto kruskal = std::make_shared<Kruskal>(graph);
    const int mst = kruskal->solve(is_strict);
    std::cout << mst << std::endl;
    const auto prim = std::make_shared<Prim>(graph);

    const int mst2 = prim->solve(is_strict);
    std::cout << mst2 << std::endl;


    const auto floyd = Floyd(graph);
    const auto dis = floyd.solve(is_strict);

    return 0;
}
