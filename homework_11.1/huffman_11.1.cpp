/**
 * @Author: tao
 * @Create Time: 2023-11-13 22:52:53
 * @Modified by: Your name
 * @Modified time: 2023-11-14 02:02:53
 * @Description:哈夫曼编码
 */

/*
准备工作：
1、计算节点的个数
2、准备一个数组存储每个节点的权重
*/
#include <iostream>
#define MAX_NUM 24                                     //定义最大节点个数
#define MAX_WEIGHT 1024                                //权重最大值，视为无穷大
typedef char ElemType;
using std::cout;
using std::cin;
using std::endl;

typedef struct HufNode{
    ElemType data;
    HufNode* lchild;
    HufNode* rchild;
    HufNode* parent;
    int weight;
}HufNode,*HufTree;

void HufCode(int n,int* weight,HufTree HT,char ** HC );                    //哈夫曼编码
void InitHuf(HufTree &HT,int n);                                           //初始化哈夫曼树
void select_two_small(const HufTree &HT,int n,int &S1,int &S2);              //从前n个节点中选出两个没有双亲的结点
int main(){
    //准备工作
    int node_num;                                       //存放节点个数
    int weight[MAX_NUM]={0};                            //数组存放节点的权重
    char str[20];
    cout << "input str" <<endl;
    cin >> str;
    char* p = str;
    while( *p!=0 ){
        if((*p >= 'a') && (*p <='z')){
            //当为小写字母的时候
            weight[*p-'a']++;
            p++;
        }
        if((*p >= 'A') && (*p <= 'Z')){
            //当为大写字母的时候
            weight[*p-'A']++;
            p++;
        }
    }
    //测试
    cout << "-----------------test--------------\n";
    for(int i = 0;i<MAX_NUM;i++){
        cout << weight[i] << " ";
    }
    cout <<endl;
    cout << "------------------test-------------\n";

    for(int i = 0;i<MAX_NUM;i++){
        if(weight[i]){
            node_num++;
        }

    }

    cout << "-----------------test--------------\n";
    cout << node_num <<endl;
    cout << "-----------------test--------------\n";
    
    HufTree HT;
    char ** HC;
    HufCode(node_num,weight,HT,HC);

    
    
    system("pause");
    return  0;
}


void HufCode(int n, int* weight, HufTree HT, char **HC){
    /*
    n 表示节点的个数
    weight 是存储节点权重的数组
    HT为huffman树
    HC存放Huffman编码
    */

   if(n<=1) return ;                                       //当节点只有一个时，直接返回
   HT = (HufNode*)malloc(sizeof(HufNode)*2*n);             //用线性表存储二叉树，前n个存储的是基础单元
   InitHuf(HT,n);                                          //初始化哈夫曼树

   
   // 设置前n个节点
   HufTree HT_ptr = HT+1;                                  //0号单元不用
   int * p = weight;
   for(int i = 1;i<=n;i++){
    //设置data and weight；
    while(!(*p)){
        // 当权重为0时，跳过
        p++;
    }
    HT_ptr->weight = *p;
    p++;
    HT_ptr++;
   }

   // 从n+1号单元开始建立哈夫曼树
   for(int i = n+1;i<=2*n;i++){
    int S1,S2;
    select_two_small(HT,i-1,S1,S2);                               //选出两个无parent的最小结点
    HT[S1].parent = HT[S2].parent = &(HT[i]);
    HT[i].lchild = &HT[S1];
    HT[i].rchild = &HT[S2];
    HT[i].weight = HT[S1].weight + HT[S2].weight;
    
   }

   

   
   
}

void InitHuf(HufTree &HT,int n){
    //操作结果：初始化哈夫曼树
    for(int i=1;i<=2*n;i++){
        HT[i].lchild = NULL;
        HT[i].parent = NULL;
        HT[i].rchild = NULL;
        HT[i].weight = MAX_WEIGHT;
    }  
    
}


void select_two_small(const HufTree &HT, int n, int &S1, int &S2){
    //操作结果：从前n个节点中选出两个权值最小的无双亲结点
    int i = 1;
    while(true){
        //为S1 赋初值
        if(HT[i].parent == NULL){
            S1 =   i;
            i++;
            break;
        }
        i++;
    }

    
    
    for(int i = 1;i<=n;i++){
        //首先挑出最小的S1
        if((HT[i].parent == NULL) &&(HT[i].weight < HT[S1].weight)){
            S1 = i;
        }
    }
    
    i = 1;
    while(true){
        //为S2 赋初值
        if((HT[i].parent == NULL)&& i!=S1){
            S2 =   i;
            i++;
            break;
        }
        i++;
    }

    for(int i = 1;i<=n;i++){
        //首先挑出最小的S1
        if((HT[i].parent == NULL) &&(HT[i].weight < HT[S2].weight) && (i!=S1)){
            S2 = i;
        }
    }
}
