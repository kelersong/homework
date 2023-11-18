/**
 * @Author: tao
 * @Create Time: 2023-11-15 20:12:25
 * @Modified by: Your name
 * @Modified time: 2023-11-18 19:03:56
 * @Description: 用邻接表作为存储结构，实现广度遍历，并且计算连通分量及边的个数
 * 
 */
#include <iostream>
#define MAX_VEX 20
using std::cout;
using std::cin;
using std::endl;
// 定义边结点结构体
typedef int VexType;
typedef struct EdgeNode{
    int endVex;                               //该边的终点编号
    EdgeNode * nextEdge;                       //指向下一条边
} EdgeNode;



// 定义顶点节点结构体
typedef struct VexNode{
    VexType data;                              //顶点的相关信息
    EdgeNode * firstEdge;                      //指向该顶点的第一条边
}VexNode;

// 定义图结构体
typedef struct MyGraph{
    int vexNum;                                //定义图的顶点的个数
    int edgeNum;                               //存储边的个数
    VexNode nodeList[MAX_VEX];                        //定义邻接表.
    int* visited;
    
}MyGraph;


//基本函数声明
void CreateGraph(MyGraph* &G);
void TraverseBFS(MyGraph *G,int &connected_num);                                        //广度优先遍历函数
void BFS(MyGraph* G,int index);                             //广度优先遍历函数辅助函数


// 主函数
int main(){
    MyGraph* G;
    CreateGraph(G);                                       //创建一个图
    cout << "done" << endl;                               //for test
    // 广度优先遍历
    int connected_num;
    TraverseBFS(G,connected_num);
    cout << endl;
    cout << connected_num << endl;
    cout << G->edgeNum <<endl;
    system("pause");
    return 0;
}


//基本函数实现
void CreateGraph(MyGraph* &G){
    //操作结果，创建一个无向图
    // 输入有关图的信息

    cout << "input the number of vex and the number of edge :" <<endl;
    

    // 开辟空间
    G = (MyGraph*)malloc(sizeof(MyGraph));
    G->edgeNum = 0;
    G->vexNum = 0;

    cin >> G->vexNum;
    
    cin >> G->edgeNum;

    for(int i = 0;i<G->vexNum;i++){
        //初始化nodeList中的结点
       
        G->nodeList[i].firstEdge = NULL;
    }
    

    // 存储边
    for(int i = 0;i<G->edgeNum;i++){
        int start , end ;
        EdgeNode*  E;                                   //创建一个临时边结点指针
        E = (EdgeNode *)malloc(sizeof(EdgeNode));

        cout << "input start and end :" <<endl;
        cin >> start;                                   //输入起点编号
        cin >> end;                                     //输入终点编号
        E->endVex = end;                                 //赋值
        //将边与顶点关联
        E->nextEdge = G->nodeList[start].firstEdge;       
        G->nodeList[start].firstEdge = E;
        EdgeNode* E1;
        E1 = (EdgeNode*)malloc(sizeof(EdgeNode));
        E1->endVex = start;
        E1->nextEdge = G->nodeList[end].firstEdge;
        G->nodeList[end].firstEdge = E1;
        
    }
}

void TraverseBFS(MyGraph *G,int &connected_num){
    //操作结果 ： 对图进行广度优先遍历
    // 1、设置visited数组默认为false
    // 2、以每个节点开始进行遍历
    G->edgeNum = 0;                                       //将边数归零，在遍历中重新计算边数
    G->visited = (int *)malloc(MAX_VEX*sizeof(int));
    for(int i = 0;i<G->vexNum;i++){
        G->visited[i] = false;                             // 将辅助数组默认值改为false
    }
    
    for(int i = 0;i<G->vexNum;i++){
        //对每个节点调用广度优先遍历
        if(G->visited[i] == false){
            BFS(G,i);
            G->visited[i] = true;
            connected_num++;
        }
    }
    G->edgeNum /= 2;
}

void BFS(MyGraph *G, int index){
    // 广度优先遍历，利用队列
    int Qu[MAX_VEX];                     //队列存放的是编号
    EdgeNode* p;
    int front , rear;
    front = rear = 0;                          //队列为空
    Qu[rear++] = index;                   //起始点入队
    G->visited[index] = true;             //修改访问状态
    while(front != rear){
        int i;
        i = Qu[front++];                    //对头元素出队
        cout << i <<" ";                  //访问对头元素
        p = G->nodeList[i].firstEdge; //将p设置为对头的第一个元素
        while(p){
            if(G->visited[p->endVex] == false){
                Qu[rear++] = p->endVex;
                G->visited[p->endVex] = true;                //修改访问状态，防止重复入队
                
                
            }
            G->edgeNum++;
            p = p->nextEdge;
        }
    }
    
}