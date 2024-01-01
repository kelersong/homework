/**
 * @Author: 072210109 程涛
 * @Create Time: 2023-12-12 07:56:49
 * @文件名: graph.h
 * @用途: 图的建立和类方法的声明
 */


#ifndef GRAPH_H
#define GRAPH_H
#define MAX_VEX 20
/*边结构体声明*/
struct ArcNode{
    int arcVex;                                   //边的终点
    ArcNode* nextEdge;                                //指向下一条边
};

/*顶点结构体声明*/
struct VexNode{
    int data;                                     //顶点编号
    ArcNode* fistEdge;

};

class Graph{
    private:
    int vexNum;                                         //顶点个数
    VexNode* nodeList[MAX_VEX];                         //邻接表
    int root;                                           //标记根


    public:
    Graph();
    ~Graph();
    int FindPath();
};


#endif