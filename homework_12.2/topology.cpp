/**
 * @Author: Your name
 * @Create Time: 2023-11-22 15:58:17
 * @Modified by: Your name
 * @Modified time: 2023-11-22 23:25:03
 * @Description: 用拓扑排序判断有向图是否存在回路
 *
 */

#define MAX_VEX 30
#include <iostream> 
using std::cout;
using std::cin;
using std::endl;
/*邻接点结构体*/
struct EdgeNode{
    int endNode;                    //终点编号
    EdgeNode* nextNode;             //指向下一个邻接点
};

/*头结点结构体*/
struct VexNode{
    int info;                        //顶点信息
    EdgeNode* firstNode;             //指向第一个邻接点
};

/*有向图结构体*/
struct MGraph{
    int vexNum;                      //顶点数量
    int edgeNum;                     //边数量
    VexNode* nodeList[MAX_VEX];       //头结点数组
    int visited[MAX_VEX];            //辅助数组--标识是否被访问
};
/*辅助栈结构体*/
struct MStack{
    int * base;
    int * top;
};                        
/*栈函数声明*/
void CreateStack(MStack *&S);                           //创建栈
bool Pop(MStack *&S);                                   //出栈
bool Push(MStack *&S,const int &elem);                  //入栈
void DestroyStack(MStack *&S);                          //摧毁栈
int  GetTop(MStack* &S);                                //取栈顶元素

//基本函数声明

/*创建有向图函数*/
void CreateGraph(MGraph* &G);

/*拓扑排序*/
int TopologicalSort( MGraph* &G);


int main(){
    MGraph* G;                         //有向图
    CreateGraph(G);
    int flag = TopologicalSort(G);
    cout << endl;
    if(!flag) cout << flag <<endl;
    system("pause");
    return 0;
}



// 函数实现
void CreateGraph(MGraph *&G){
    /*初始化*/
    G = (MGraph*)malloc(sizeof(MGraph));                         //开辟空间
    cout << "请输入有向图的顶点个数和边数 " <<endl;
    cin >> G->vexNum;
    cin >> G->edgeNum;
    for(int i=0;i<G->vexNum;i++){                               //初始化nodeList
        G->nodeList[i] = (VexNode*)malloc(sizeof(VexNode));      //开辟空间
        G->nodeList[i]->firstNode = NULL;
    }

    /*输入边*/
    cout << "请输入边的起点和终点" <<endl;
    for(int i=0;i<G->edgeNum;i++){
        int start,end;
        cin >> start;
        cin >> end;
        EdgeNode* E;                                              //创建邻接点指针
        E = (EdgeNode*)malloc(sizeof(EdgeNode));                  //开辟空间
        E->endNode = end;
        E->nextNode = G->nodeList[start]->firstNode;              //头插法插入边
        G->nodeList[start]->firstNode = E;                        
    }

}
int TopologicalSort( MGraph* &G){
    /*1、准备工作*/
    int count = 0;                             //统计拓扑排序过程中访问到的顶点总数
    int inDegree[MAX_VEX];                     //存放每个顶点的入度
    for(int i=0;i<MAX_VEX;i++){                //初始化
        inDegree[i] = 0;
    }

    /*2、统计每个顶点的入度*/
    for(int i=0;i<G->vexNum;i++){
        EdgeNode* p = (EdgeNode* )malloc(sizeof(EdgeNode));
        p = G->nodeList[i]->firstNode;
        while(p){
            inDegree[p->endNode]++;
            p = p->nextNode;
        }
    }
    
    /*3、将入度为0的顶点入栈*/
    MStack* S;
    CreateStack(S);
    for(int i = 0;i<G->vexNum;i++){
        if(inDegree[i] == 0){
            Push(S,i);
        }
    }
    while(S->top - S->base > 1 ){
        /*4、删除顶点关联的边，并重新计算入度*/
        int topElem = GetTop(S);
        Pop(S);
        cout << topElem <<" ";
        count++;                                                  //计数
        EdgeNode* p = (EdgeNode* )malloc(sizeof(EdgeNode));
        p = G->nodeList[topElem]->firstNode;
        while(p){
            inDegree[p->endNode]--;
            if(inDegree[p->endNode] == 0){
                Push(S,p->endNode);                               //更新后入度为0，则入栈
            }
            p = p->nextNode;
        } 
    }
    if(count == G->vexNum){
        return true;
    }
    else{
        return false;
    }
    
    
    
    
}


/*栈函数实现*/
void CreateStack(MStack *&S){
    S = (MStack*)malloc(sizeof(MStack));                            //开辟空间
    S->base = (int *)malloc(MAX_VEX* sizeof(int));
    if(S->base == NULL || S == NULL){
        cout << "栈空间开辟失败" <<endl;
        exit(1);
    }
    S->top = S->base+1;                                             //top默认指向待插入位置
}

bool Push(MStack *&S, const int &elem){
    if(S->top - S->base >= MAX_VEX){
        cout << "栈空间以满" <<endl;
        return false;
    }
    else{
        *(S->top++) = elem;
        return true;
    }
}

bool Pop(MStack *&S){
    if(S->base == S->top){
        cout << "栈元素为空,不可弹栈" <<endl;
        return false;
    }
    else{
        S->top--;
        return true;
    }
}

void DestroyStack(MStack *&S){
    S->base = NULL;
    S->top = NULL;
}

int GetTop(MStack *&S){
    if(S->base == S->top){
        cout << "栈为空"  <<endl;
    }
    else{
        return *(S->top-1);
    }
}
