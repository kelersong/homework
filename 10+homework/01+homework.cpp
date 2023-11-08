/**
 * @Author: tao
 * @Create Time: 2023-11-07 23:11:37
 * @Modified by: Your name
 * @Modified time: 2023-11-08 22:09:02
 * @Description:1、以二叉链表作存储结构，建立一棵二叉树， 输出该二叉树的中序遍历序列(递归法)，层序遍历序列，并求二叉树的深度。
 */
#include<iostream>
#define ElemType char
using std::cout;
using std::cin;
using std::endl;
struct BiNode{
    //数据部分
    char data;
    //指针部分
    BiNode* LeftChild;                     //指向左孩子的指针
    BiNode* RightChild;                    //指向右孩子的指针
};







void CreateBinaryTree(BiNode* &T);                //已知先序序列构造二叉树
void InOrder(BiNode *T,void(*visit)( BiNode node));    //中序遍历
void LevelOrder(BiNode *T,void (*visit)( BiNode node));//层序遍历
void show(BiNode node);                               //用于遍历操作
int  Hight(const BiNode *T);                                  //求二叉树的深度
void GetLeaves(BiNode node);                                    //求二叉树的叶子结点



// 主函数
int main(){
    
    //创建一个根节点
    BiNode *T;
    //根据先序序列创建二叉树
    CreateBinaryTree(T);
    //中序遍历二叉树
    InOrder(T,show);
    cout << endl;
    //层序遍历二叉树
    LevelOrder(T,show);
    cout << endl;
    //求二叉树的深度
    int hight = Hight(T);
    cout << "The hight of tree is :" <<hight <<endl;
    // 求二叉树的叶子结点
    InOrder(T,GetLeaves);
    cout << endl;
    
    system("pause");
    return 0;
}


//函数实现
void CreateBinaryTree(BiNode* &T){
    //操作结果：根据先序序列创建一个二叉树
    char ch;    
    cin>>ch;
    if(ch == '#') T=NULL;
    else{
        T = (BiNode*)malloc(sizeof(BiNode));                         //创建根节点
        
        T->data = ch;
        CreateBinaryTree(T->LeftChild);                              //创建左分支
        CreateBinaryTree(T->RightChild);                             //创建有分支
    }
}

void InOrder(BiNode *T, void (*visit)(BiNode node)){
    //操作结果：中序遍历
    
    if(T!=NULL){
        InOrder(T->LeftChild,visit);
        visit(*T);
        InOrder(T->RightChild,visit);
    
    }
}

#define max_Size 256
void LevelOrder(BiNode *T, void (*visit)(BiNode node)){
    //层序遍历
    /*
    原理：使用队列实现，将结点的左右孩子入队，然后取出。 先进先出！
    */
    BiNode *p;                                                       //用于存放被取出的结点
    BiNode *queue[max_Size];                                         //存放树节点指针的队列
    int front,rear;                  
    front = rear = 0;                                                //初始化队列
    queue[rear] = T;                                                 //将根节点指针入队
    rear++;                                                          //更新
    while(front!=rear){
        //当队列不为空时
        p = queue[front];                                            //队首出队
        front = (front+1)%max_Size;                                  //更新，队列若已满循环
        visit(*p);                                              //访问队首元素
        if(p->LeftChild!=NULL){
            //当左孩子存在的的时候
            queue[rear] = p->LeftChild;
            rear = (rear+1)%max_Size;

        }
        if(p->RightChild!=NULL){
            //当右孩子存在的的时候
            queue[rear] = p->RightChild;
            rear = (rear+1)%max_Size;

        }
    }

}

void show(BiNode node){
    //遍历时调用
    cout << node.data ;
}


int Hight(const BiNode *T){
    //操作结果：求树的深度
    int Left_Hight,Right_Hight;
    if(T==NULL) return 0;
    else{
        Left_Hight = Hight(T->LeftChild);
        Right_Hight = Hight(T->RightChild);
        return (Left_Hight>Right_Hight)? (Left_Hight+1):(Right_Hight+1);
    }
    
}


void GetLeaves(BiNode node){
    //操作结果：得到二叉树的叶子结点
    if(node.LeftChild == NULL && node.RightChild==NULL){
        cout << node.data ;
    }
}







