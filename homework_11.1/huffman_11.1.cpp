/**
 * @Author: tao
 * @Create Time: 2023-11-13 22:52:53
 * @Modified by: Your name
 * @Modified time: 2023-11-15 19:11:04
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
    char * encoding;
    
}HufNode,*HufTree;

typedef struct StrWeight{
    ElemType data;
    int weight;
    
}StrWeight;


void HufCode(int n,StrWeight *weight,HufTree &HT,StrWeight ** &HC );                    //哈夫曼编码
void InitHuf(HufTree &HT,int n);                                           //初始化哈夫曼树
void select_two_small(const HufTree &HT,int n,int &S1,int &S2);              //从前n个节点中选出两个没有双亲的结点
void reverse(char * &str);                                                   //将编码逆序
void my_strcpy(char * &str1, char* &str2);                                   //将str2复制到str1中
char Upper(char &s);
void append(char *str1,char * str2);                                        //将str2追加到str1中



int main(){ 
    //准备工作
    int node_num;                                       //存放节点个数
    StrWeight weight[MAX_NUM];                          //用于存放字符串以及出现的次数
    for(int i = 0;i<MAX_NUM;i++){                       //初始化
        weight[i].weight = 0;
    }
    char str[20];
    cout << "input str" <<endl;
    cin >> str;
    char* p = str;
    while( *p!=0 ){
        if((*p >= 'a') && (*p <='z')){
            //当为小写字母的时候
            weight[*p-'a'].weight++;
            weight[*p-'a'].data = Upper(*p);
            p++;
        }
        if((*p >= 'A') && (*p <= 'Z')){
            //当为大写字母的时候
            weight[*p-'A'].weight++;
            weight[*p-'A'].data = Upper(*p);
            p++;
        }
    }
   
    // 计算字符串中出现的字符个数，忽略大小写
    for(int i = 0;i<MAX_NUM;i++){
        if(weight[i].weight){
            node_num++;
        }

    }

    

    
    
    HufTree HT;
    StrWeight** HC;
    HufCode(node_num,weight,HT,HC);                                              //哈夫曼编码
    
    
    //输出encoding,并将输出结果存放在字符串中
    char  coding[1024]={'\0'};                                      //存放生成的编码
    cout << "Encoding :  ";
    p = str;
    while(*p){
        *p = Upper(*p);
        for(int i=1;i<=node_num;i++){
            if((*p)==HT[i].data){
                cout << HT[i].encoding;
                append(coding,HT[i].encoding);
                
                continue;
            }
        }
        p++;
    }
    cout << endl;

    // 输出解码
    cout << "Decoding :  " ;
    
    int index = 0;
    HufTree hp;
    while(coding[index]){
       
       
       hp = &HT[2*node_num-1];
          
       while(hp->lchild || hp->rchild){
        // 当左孩子或者右孩子存在时
           char ch = coding[index];
           if(ch=='1'){
              hp = hp->rchild;
            
            }
            else{
                hp = hp->lchild;
            }
            index++;
        }
        cout << hp->data;
    }
    cout << endl;
    

    
    
    system("pause");
    return  0;
}


void HufCode(int n, StrWeight * weight, HufTree &HT, StrWeight ** &HC){
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
   StrWeight * p = weight;
   for(int i = 1;i<=n;i++){
    //设置data and weight；
    while(!((*p).weight)){
        // 当权重为0时，跳过
        p++;
    }
    HT_ptr->weight = (*p).weight;
    HT_ptr->data = (*p).data;
    p++;
    HT_ptr++;
   }
   

   // 从n+1号单元开始建立哈夫曼树
   for(int i = n+1;i<2*n;i++){
    int S1,S2;
    select_two_small(HT,i-1,S1,S2);                               //选出两个无parent的最小结点
    HT[S1].parent = HT[S2].parent = &(HT[i]);
    HT[i].lchild = &HT[S1];
    HT[i].rchild = &HT[S2];
    HT[i].weight = HT[S1].weight + HT[S2].weight;
    
   }

   // 从叶节点到根节点逆向获取每个叶节点的哈夫曼编码
   HC = (StrWeight ** )malloc(n*sizeof(StrWeight*));                               //动态分配n个编码的指针
   char * temp;
   temp = (char * )malloc(n*sizeof(char));                                //分配一个临时空间存放当前获取的编码
   for(int i = 1;i<=n;i++){
    //一共有n个需要编码的字符
    int start = 0;
    HufTree c = &HT[i];
    while(c->parent != NULL){
        //当节点存在双亲时，继续向上走
        HufTree par = c->parent;
        if(par->lchild == c){
            //编码为0
            temp[start++] = '0';
        }
        else{
            //为右孩子，编码为1
            temp[start++] = '1';
        }
        c = par;
        par = par->parent;

   }
   temp[start++] = '\0';                                                   //为字符串提供结束标志
   reverse(temp);                                                          //将哈夫曼编码逆序
   
   HT[i].encoding = (char *)malloc(start * sizeof(char));                           //将临时变量传递到永久变量中
   my_strcpy(HT[i].encoding,temp);
   
   

   }
   free(temp);
   return;
   

   
   
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

void my_strcpy(char *&str1, char *&str2){
    //复制字符串
    
    char * p_2 = str2;
    char * p_1 = str1;
    while(*(p_2)){
        *p_1 = *p_2;
        p_1++;
        p_2++;
    }
    *p_1 = '\0';
}

void reverse(char *&str){
    // 操作结果 ：将字符串倒序
    char * start = str;                                            //指向字符串头部的指针
    char * end = str;                                              //指向字符串尾部的指针
    while(*(end) != '\0'){
        end++;
    }
    end--;
    while((end - start) > 0){
        char  temp;
        temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}

char Upper(char &s){
    if(s>='a' && s <= 'z')
    {
       return char(s+'A'-'a');
    }
    else return s;
}

void append(char *str1, char *str2){
    //操作结果：将str2的内容追加到str1中
    char * p1 = str1;
    char * p2 = str2;
    
    while(*p1){
        //当str1不为空
        p1++;
    }
    while(*p2){
        //当p2不为空
        *p1 = *p2;
        p1++;
        p2++;
    }
    *p1 = '\0';
}

