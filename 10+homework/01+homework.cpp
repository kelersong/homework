/**
 * @Author: tao
 * @Create Time: 2023-11-07 23:11:37
 * @Modified by: Your name
 * @Modified time: 2023-11-07 23:33:25
 * @Description:1、以二叉链表作存储结构，建立一棵二叉树， 输出该二叉树的中序遍历序列(递归法)，层序遍历序列，并求二叉树的深度。
 */

#define ElemType char
struct BiNode{
    //数据部分
    ElemType data;
    //指针部分
    BiNode* LeftChild;                     //指向左孩子的指针
    BiNode* RightChild;                    //指向右孩子的指针
};


void InitBiNode(ElemType data);                             //创建一个叶子结点
void InitBiNode(ElemType data,BiNode* lchild,BiNode* rchild);  //创建一个左右子树都存在的结点


struct BinaryTree{
    // 二叉树顺序表结构
    int maxSize;                             //二叉树的最大节点个数
    BiNode* elems ;                          //节点存储空间
    BiNode root;                             //二叉树的根
};