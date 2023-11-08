/**
 * @Author: tao
 * @Create Time: 2023-11-07 23:11:37
 * @Modified by: Your name
 * @Modified time: 2023-11-08 13:26:38
 * @Description:1、以二叉链表作存储结构，建立一棵二叉树， 输出该二叉树的中序遍历序列(递归法)，层序遍历序列，并求二叉树的深度。
 */
#include<iostream>
#define ElemType char
using std::cout;
using std::cin;
using std::endl;
struct BiNode{
    //数据部分
    ElemType data;
    //指针部分
    BiNode* LeftChild;                     //指向左孩子的指针
    BiNode* RightChild;                    //指向右孩子的指针
};







void CreateBinaryTree(BiNode *T);                //已知先序序列构造二叉树
void InOrder(BiNode *T,void(*visit)(const ElemType elem));    //中序遍历
void LevelOrder(BiNode *T,void (*visit)(const ElemType elem));//层序遍历
void show(const ElemType elem);                                                      //用于遍历操作
int  Hight(const BiNode *T);                                  //求二叉树的深度

// 主函数
int main(){
    
    //创建一个根节点
    BiNode T;
    //根据先序序列创建二叉树
    CreateBinaryTree(&T);
    //中序遍历二叉树
    InOrder(&T,show);
    //层序遍历二叉树
    LevelOrder(&T,show);
    //求二叉树的深度
    int hight = Hight(&T);
    cout << "The hight of tree is :" <<hight <<endl;
    

    
    system("pause");
    return 0;
}


//函数实现
void CreateBinaryTree(BiNode *T){
    //操作结果：根据先序序列创建一个二叉树
    char ch;
    cin.get(ch);
    if(ch == ' ') T=NULL;
    else{
        T = (BiNode*)malloc(sizeof(BiNode));                         //创建根节点
        if(!T) exit(1);
        T->data = ch;
        CreateBinaryTree(T->LeftChild);                              //创建左分支
        CreateBinaryTree(T->RightChild);                             //创建有分支
    }
}

