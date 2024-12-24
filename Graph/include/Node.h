/*** 
 * @Author: yuyuan yuyuan12138x@gmail.com
 * @Date: 2024-12-24 10:55:00
 * @LastEditors: yuyuan yuyuan12138x@gmail.com
 * @LastEditTime: 2024-12-24 12:59:37
 * @FilePath: \Graph\include\Node.h
 * @Description: 
 * @
 * @Copyright (c) ${Date} by ${yuyuan12138x@gmail.com}, All Rights Reserved. 
 */
#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

struct Node
{
    int idx;
    std::string name;
    int val;
};

class Nodes{
public:
    Nodes(): _number_of_nodes(0) {};
    
    int _number_of_nodes;
    std::vector<std::shared_ptr<Node>> _nodes;
    
    void add_node(const std::string& name, const int val);
    void delete_node(const std::string& name);
    void show_nodes();
};

#endif