/**
 * @Author: 072210109 程涛
 * @Create Time: 2023-12-12 08:06:39
 * @文件名: graph.cpp
 * @用途: 图的类方法实现
 */


#include "graph.h"
#include <iostream>
#include <list>
#include <queue>
#include <string>



using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::queue;
using std::string;

Graph::Graph(){

    cout << "请输入顶点个数 :" <<endl;
    cin >> vexNum;
    /*初始化邻接表*/
    for(int i = 1;i<=vexNum;i++){
        //为了方便0号空间不适用
        nodeList[i] =(VexNode*) malloc(sizeof(VexNode));
        nodeList[i] ->data = i;
        nodeList[i] ->fistEdge = NULL;
    }
    cout << "请输入序列:" <<endl;
    int a;
    int count = 1;
    for(int i = 0;i<vexNum;i++){
        cin >> a;
        if(a == 0){
            count++;
            root = count-1;
            continue;
        }
        else{
            ArcNode * E;
            E =(ArcNode*) malloc(sizeof(ArcNode));
            E->nextEdge = nodeList[a]->fistEdge;
            E->arcVex = count++;
            nodeList[a]->fistEdge = E;

        }
        
    }

}


Graph::~Graph(){
    for(int i = 1;i<= vexNum;i++){
        nodeList[i]->fistEdge = NULL;
    }
}


int Graph::FindPath(){
    list<string> L;                            //存放结果
    queue<int>  queueVex;                      //存放顶点
    queue<string> path;                        //存放路径
    int curNode;
    string curPath;
    if(!root) return 0;
    queueVex.push(root);                       //顶点入队
    path.push("");                             //空字符串入队
    while(!queueVex.empty()){
        curNode = queueVex.front();
        curPath = path.front();
        
        queueVex.pop();
        path.pop();
        string temp;
        temp = curPath;
        if(nodeList[curNode]->fistEdge == NULL){
            // 为叶子节点
            
            L.push_back(temp.append(1,(char)(curNode + '0')));
        }
        if(nodeList[curNode]->fistEdge){
            queueVex.push(nodeList[curNode]->fistEdge->arcVex);
            //测试
            path.push(temp.append(1,(char)(curNode + '0')) + " -> ");
            if(nodeList[curNode]->fistEdge->nextEdge){
                queueVex.push(nodeList[curNode]->fistEdge->nextEdge->arcVex);
                path.push(curPath.append(1,(char)(curNode + '0')) + " -> ");
            }
        }
        
    }
    
    /*遍历*/
    cout << "路径如下:" <<endl;
    list<string>::iterator it = L.begin();
    while(it != L.end()){
        cout << *it <<endl;
        it++;
    }


}