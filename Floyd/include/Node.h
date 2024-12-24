/*** 
 * @Author: yuyuan yuyuan12138x@gmail.com
 * @Date: 2024-12-24 10:03:42
 * @LastEditors: yuyuan yuyuan12138x@gmail.com
 * @LastEditTime: 2024-12-24 10:43:22
 * @FilePath: \OR\Floyd\include\Node.h
 * @Description: 
 * @
 * @Copyright (c) 2024 by ${git_name_email}, All Rights Reserved. 
 */

#ifndef _Node_H_
#define _Node_H_

#include <string>
#include <vector>

struct Node{
    int val;
    std::string name;
    std::vector<Node*> neibor;
};

#endif