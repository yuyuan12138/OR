/***
 * @Author: yuyuan yuyuan12138x@gmail.com
 * @Date: 2024-12-24 10:47:04
 * @LastEditors: yuyuan yuyuan12138x@gmail.com
 * @LastEditTime: 2024-12-24 10:54:52
 * @FilePath: \Graph\main.cpp
 * @Description:
 * @
 * @Copyright (c) 2024 by ${git_name_email}, All Rights Reserved.
 */
#include <iostream>
#include "include/Node.h"
#include "include/Edge.h"
#include "include/Graph.h"
#include <io.h>
#include <fcntl.h>

void run_tests() {
    std::vector<std::pair<std::string, int>> nodes;
    nodes.emplace_back("A", 1);
    // graph->add_node("A", 1);
    nodes.emplace_back("B", 2);
    nodes.emplace_back("C", 3);
    const auto graph = std::make_shared<Graph>(nodes);

    std::vector<std::pair<std::string, int>> edges;
    // 添加边 - 创建一个简单双节点循环 (loop)
    edges.emplace_back("A-A", 4);  // Self-loop at node A

    // 测试：添加多重边 (Multiple Edges)
    edges.emplace_back("A-B", 5);  // First edge from A to B
    edges.emplace_back("A-B", 10); // Second edge from A to B with different weight
    graph->add_edges(edges);

    // 创建一个三节点循环 (Cycle) A -> B -> C -> A
    graph->add_edge("B-C", 6);
    graph->add_edge("C-A", 7);

    std::cout << "Graph after adding nodes and edges:\n";
    graph->show_graph();

    // 删除节点并检验环和多重边影响
    graph->delete_node("A");
    std::cout << "\nGraph after deleting node A:\n";
    graph->show_graph();

    // 新的情况：再添加节点和边
    graph->add_node("D", 4);
    graph->add_edge("B-D", 8);
    graph->add_edge("D-C", 9);

    std::cout << "\nGraph after adding node D and edges:\n";
    graph->show_graph();

    // 删除一个连接多条边的节点
    graph->delete_node("B");
    std::cout << "\nGraph after deleting node B:\n";
    graph->show_graph();
}


int main() {
    // _setmode(_fileno(stdout), _O_U8TEXT);
    std::cout << "==== Graph test start ====" << std::endl;
    run_tests();
    std::cout << "==== Graph test end ====" << std::endl;
    return 0;
}
