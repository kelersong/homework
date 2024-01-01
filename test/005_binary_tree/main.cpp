/**
 * @Author: 072210109 程涛
 * @Create Time: 2023-12-12 07:54:52
 * @文件名: main.cpp
 * @用途: 程序主函数
 */


#include "graph.h"
#include <iostream>
#include "Tool.h"
int main(){
    /*创建图*/
    Tool T;
    T.Set_Color(1);
    std::cout << "欢迎使用   ---课程设计第五题" <<std::endl;
    std::cout << "作者 : 072210109" <<std::endl;
    T.Set_Color(8);
    Graph(myGraph);
    myGraph.FindPath();
    system("pause");
    return 0;
}
