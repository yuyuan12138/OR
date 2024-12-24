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

int main(){
    std::cout << "Hello, from Graph!\n";
    std::shared_ptr<Nodes> nodes = std::make_shared<Nodes>();
    std::shared_ptr<Edges> edges = std::make_shared<Edges>();
    nodes->add_node("A", 1);
    // nodes->delete_node("A");
    nodes->show_nodes();
    edges->add_edge("A", 1);

    edges->show_edges();

    return 0;
}
