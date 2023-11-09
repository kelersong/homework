/**
 * @Author: tao
 * @Create Time: 2023-11-09 16:07:12
 * @Modified by: Your name
 * @Modified time: 2023-11-09 22:29:39
 * @Description: 二叉树建树、二叉树中序遍历(非递归)、二叉树删除，结点父结点求解，结点兄弟结点求解
 */

typedef char ElemType;
//节点结构
typedef struct BinNode{
    //数据成员
    ElemType data;                        //存放数据成分
    BinNode* lchild;                      //存放左孩子指针
    BinNode* rchild;                      //存放右孩子指针
};

//函数声明
void CreateBinTree(BinNode* &T);
void InOrder(BinNode* T,void (*visit)(BinNode* node));
void show(BinNode* node);
void delete_node(BinNode* node );
void search_father(BinNode* node );
void search_brother(BinNode* node);

// 主程序
int main(){
    //1、根据先序序列创建一个二叉树
    BinNode* T;                            //创建一个根节点
    CreateBinTree(T);
    //2、中序遍历，非递归方式
    InOrder(T,show);
    //3、二叉树删除
    InOrder(T,delete_node);
    //4、求节点的兄弟结点和双亲结点
    InOrder(T,search_father);
    InOrder(T,search_brother);
    system("pause");
    return 0;
}


