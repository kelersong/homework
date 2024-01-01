#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VEX 20


/*边节点定义*/
struct ArcNode{
    int arcVex;                             //边的终点
    int weight;                             //边的权重
    ArcNode* nextEdge;                      //指向下一条边的指针
};

struct VexNode{
    int data;                               //编号
    ArcNode* firstEdge;                     //指向第一条边
};

class Graph{
    private:
    int vexNum_h;
    int edgeNum_h; 
    VexNode* nodeList[MAX_VEX];                    //邻接表

    public:
    Graph();                                       //构造函数
    ~Graph();                                      //析构函数
    int FindShortestPath(int start);                        //寻找最短路径函数
};


#endif