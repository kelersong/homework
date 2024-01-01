#include "graph.h"
#include <iostream>
#include "Tool.h"

using std::cout;
using std::endl;

int main(){
    Tool T;
    T.Set_Color(1);
    cout << "欢迎使用 !" <<endl;
    cout << "作者 : 072210109 程涛" <<endl;
    T.Set_Color(8);
    Graph(myGraph);
    myGraph.FindShortestPath(0);
    system("pause");
    return 0;
}