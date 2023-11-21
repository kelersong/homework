/**
 * @Author: Your name
 * @Create Time: 2023-11-21 15:39:28
 * @Modified by: Your name
 * @Modified time: 2023-11-21 19:16:43
 * @Description: 实现图的创建和深度遍历
 */
# define MAX_VEX 30
# include <iostream>
using std::cout;
using std::cin;
using std::endl;

struct EdgeNode{
    // 表节点结构体
    int endNode;
    EdgeNode* nextEdge;
};

struct VexNode{
    // 头结点结构体
    int nodeInf;                      //节点信息
    EdgeNode* firstEdge;
};



struct MGraph{
    // 图结构体
    int vexNum;                    //顶点数量
    int edgeNum;                   //边数量
    int visited[MAX_VEX];          //辅助数组
    VexNode* nodeList[MAX_VEX];    //头结点链表
};
// 函数声明
void CreateGraph(MGraph* &G);                                        //创建图
void TraverseBFS(MGraph* &G,int index);                              //深度优先遍历
void BFS(MGraph* G,int index);

int main(){
    MGraph* G;
    CreateGraph(G);
    TraverseBFS(G,0);
    cout << endl;
    system("pause");
    return 0;
}


void CreateGraph(MGraph *&G){
    // 操作结果 ： 创建一个图

    // 分配空间
    G = (MGraph*)malloc(sizeof(MGraph));    

    // 输入顶点和边的个数
    cout << "input vexNum , edgeNum " <<endl;
    cin >> G->vexNum;
    cin >> G->edgeNum;

    // 初始化，分配空间
    for(int i=0; i < MAX_VEX;i++){
        G->nodeList[i] = (VexNode*)malloc(sizeof(VexNode));
        G->nodeList[i]->firstEdge = NULL;
        G->nodeList[i]->nodeInf = 0;                             //顶点信息为0 表示为
    }

    // 初始化图
    for(int i = 0; i < G->edgeNum; i++){
        EdgeNode* E;
        E = (EdgeNode*) malloc(sizeof(EdgeNode));                //分配空间
        int start,end;
        cin >> start;
        cin >> end;
        
        E->endNode = end;
        E->nextEdge = G->nodeList[start]->firstEdge;
        G->nodeList[start]->firstEdge = E; 
    }

    
}

void TraverseBFS(MGraph *&G, int index){
    // 深度优先遍历
    
    //辅助数组初始化
    for(int i = 0; i<G->vexNum;i++){
        G->visited[i] = false;
    }

    for(int i=0;i<G->vexNum;i++){
        if(G->visited[i] == false){
            BFS(G,i);
        }
    }
}


void BFS(MGraph *G, int index){
    //递归调用
    G->visited[index] = true;
    cout << index << " " ;
    EdgeNode* p;
    p = G->nodeList[index]->firstEdge;
    while(p){
        if(G->visited[p->endNode] == false){
            BFS(G,p->endNode);
        }
        p = p->nextEdge;
    }
}
