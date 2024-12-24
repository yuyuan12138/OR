/*** 
 * @Author: yuyuan yuyuan12138x@gmail.com
 * @Date: 2024-12-24 13:13:16
 * @LastEditors: yuyuan yuyuan12138x@gmail.com
 * @LastEditTime: 2024-12-24 13:18:31
 * @FilePath: \Graph\include\Edge.h
 * @Description: 
 * @
 * @Copyright (c) ${Date} by ${yuyuan12138x@gmail.com}, All Rights Reserved. 
 */

#ifndef _EDGE_H_
#define _EDGE_H_
#include <vector>
#include "Node.h"
#include <memory>
#include <string>

struct Edge
{
    int idx;
    int val;
    std::string name;
};

class Edges{
public:
    Edges(): _number_of_edges(0) {};
    int _number_of_edges;
    std::vector<std::shared_ptr<Edge>> _edges;

    void add_edge(const std::string& name, const int val);
    void delete_edge(const std::string& name);

    void show_edges();
};

#endif