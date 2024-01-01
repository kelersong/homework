#include "graph.h"
#include <iostream>
#include <iomanip>
#include <list>
#include <string>
#include <stack>
#include "Tool.h"
#define INFINITY 1000

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::string;
using std::stack;


Graph::Graph(){
    cout << "请输入顶点个数和边的个数:" <<endl;
    cin >> vexNum_h;
    cin >> edgeNum_h;

    for(int i = 0;i<vexNum_h;i++){
        /*邻接表初始化*/
        nodeList[i] = (VexNode*) malloc(sizeof(VexNode));
        if(nodeList[i] == NULL){
            cout << "nodeList 分配空间失败" <<endl;
        }
        nodeList[i]->data = i;
        nodeList[i]->firstEdge = NULL;
    }

    /*读边*/
    cout << "请输入边,格式为a b c :" <<endl;
    for(int i=0;i<edgeNum_h;i++){
        ArcNode* E;
        E =(ArcNode*) malloc(sizeof(ArcNode));
        if(E == NULL){
            cout << "E 分配空间失败" <<endl;
        }
        int start;
        cin >> start;
        cin >> E->arcVex;
        cin >> E->weight;
        E->nextEdge = nodeList[start]->firstEdge;
        nodeList[start]->firstEdge = E;
    }
}


Graph::~Graph(){
    for(int i = 0;i<vexNum_h;i++){
        nodeList[i]->firstEdge = NULL;
    }
}


int Graph::FindShortestPath(int start){
    //使用迪杰斯特拉算法
    
    int path[MAX_VEX],dist[MAX_VEX],flag[MAX_VEX]; //存放路径，最短举例，辅助数组
    for(int i = 0;i<vexNum_h;i++){
        /*初始化*/
        flag[i] = 0;
        if(i == start){
            dist[i] = 0;
        }
        else{
            dist[i] = INFINITY;
        }
    }

    /*更新dist*/
    ArcNode* E;
    E =(ArcNode*) malloc(sizeof(ArcNode));
    E = nodeList[start]->firstEdge;
    while(E!= NULL){
        dist[E->arcVex] = E->weight;
        E = E->nextEdge;
    }
    flag[start] = 1;
    
    for(int i = 0;i<vexNum_h-1;i++){
        //n-1轮
        //1、寻找最近且flag为0的顶点
        int min = INFINITY;                         //存放最小的编号
        int minDist = INFINITY;
        for(int j = 0;j<vexNum_h;j++){
            //遍历dist
            if(dist[j] < minDist && j!=start && flag[j] == 0){
                min = j;
                minDist = dist[j];
            }
        }

        flag[min] = 1;                       //选择该点
        if(minDist <INFINITY){
            //连通
            
            //再次遍历，更新到min点的举例
            ArcNode* E1;
            E1 =(ArcNode*) malloc(sizeof(ArcNode));
            E1 = nodeList[min]->firstEdge;
            while(E1 != NULL){
                if(((flag[E1->arcVex]) == 0) && (dist[E1->arcVex] > (minDist + E1->weight))){
                    dist[E1->arcVex] = minDist + E1->weight;
                    path[E1->arcVex] = min;
                    E1 = E1->nextEdge;
                    continue;
                }

                if(((flag[E1->arcVex]) == 0) && (dist[E1->arcVex] == (minDist + E1->weight)) && (dist[E1->arcVex] != INFINITY)){
                    int len1,len2;
                    len1  = 0;
                    len2 = 0;
                    int temp1 = path[E1->arcVex];
                    int temp2 = min;
                    while(temp1!= start){
                        len1++;
                        temp1 = path[temp1];
                    }
                    while(temp2!= start){
                        len2++;
                        temp2 = path[temp2];
                    }
                    if(len1 > len2){
                        dist[E1->arcVex] = minDist + E1->weight;
                        path[E1->arcVex] = min;
                        E1 = E1->nextEdge;
                    }
                }

                
                
            }
        }


    }

    /*打印路径*/
    list<string> L;                                             //存放路径字符串
    for(int i = 0;i<vexNum_h;i++){
        if(i != start){
            stack<int> S;
            S.push(i);
            int temp = i;
            while(1){
                S.push(path[temp]);
                temp = path[temp];

                if(temp == start){
                    break;
                }
            }
            Tool T;
            T.Set_Color(5);
            cout << "路径 : ";
            T.Set_Color(8);
            int temp3;                      //用于接受S中pop出的元素
            while(!S.empty()){
                temp3 = S.top();
                S.pop();
                cout << temp3;
                if(!S.empty()){
                    cout << " -> ";
                }
            }
           
           
            cout  <<"\n";
        }

    }



    return 1;
}