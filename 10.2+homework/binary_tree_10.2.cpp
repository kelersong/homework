/**
 * @Author: tao
 * @Create Time: 2023-11-09 16:07:12
 * @Modified by: Your name
 * @Modified time: 2023-11-10 17:26:41
 * @Description: 二叉树建树、二叉树中序遍历(非递归)、二叉树删除，结点父结点求解，结点兄弟结点求解
 */
#include <iostream>
#define STACKSIZE 128
#define ElemType char
using std::cout;
using std::cin;
using std::endl;


//节点结构
struct BinNode{
    //数据成员
    ElemType data;                        //存放数据成分
    BinNode* lchild;                      //存放左孩子指针
    BinNode* rchild;                      //存放右孩子指针
};

//函数声明
void CreateBinTree(BinNode* &T);
void InOrder(BinNode* T,void (*visit)(BinNode* node));
void InOrder(BinNode* T,bool (*combine)(BinNode* node,const ElemType &elem),void (*visit)(BinNode* node));  //如果combine比较返回值为1，执行visit函数
void show_brother(BinNode* T,const ElemType &elem);

bool search_self(BinNode* node,const ElemType &elem);
bool search_father(BinNode* node,const ElemType &elem);


void show(BinNode* node);
void delete_node(BinNode* node);





struct Stack{
    //数据成员：
    BinNode* base;                                       //栈的基地指针
    BinNode* top;                                        //栈顶指针，动态变化
   };
   
   //函数声明
   void InitStack(Stack &S);                              //初始化栈，分配空间
   bool Empty(const Stack &S);                            //判断栈是否为空
   bool Push(Stack &S, BinNode* elem);              //入栈
   bool Pop(Stack &S);                                    //弹栈
   ElemType GetTop(const Stack &S,BinNode* elem);        //返回栈顶元素，用elem接收

   

// 主程序
int main(){
    //1、根据先序序列创建一个二叉树
    BinNode* T;                            //创建一个根节点
    cout << "input the pre :" <<endl;
    CreateBinTree(T);
    //2、中序遍历，非递归方式
    InOrder(T,show);
    //3、二叉树删除
    cout << "please input elem deleted" << endl;
    InOrder(T,search_self,delete_node);
    //4、求节点的兄弟结点和双亲结点
    cout << "please input elem search for father:" <<endl;
    InOrder(T,search_father,show);
    
    system("pause");
    return 0;
}



// 函数实现
void CreateBinTree(BinNode *&T){
    // 操作结果 ：根据先序序列创建一个二叉树

    ElemType ch;
    
    cin >> ch;
    if(ch == '#') T = NULL;
    else{
        T = (BinNode*)malloc(sizeof(BinNode));
        T->data = ch;
        CreateBinTree(T->lchild);
        CreateBinTree(T->rchild);
    }
}

void InOrder(BinNode *T, void (*visit)(BinNode *node)){
    // 中序遍历，非递归
    /*
    思路：
    1、非递归要使用栈
    2、当节点的左孩子存在时，将他的左孩子入栈
    3、当节点的左孩子不存在时，访问当前节点
    4、将该节点的右孩子入栈
    5、直到将二叉树遍历完全并且栈为空
    */
   

   //遍历函数
   Stack s;
   InitStack(s);
   BinNode* q = T;                                             //用于遍历二叉树
   while((q!=NULL) || (!Empty(s))){
     while(q!=NULL){
        //当左孩子存在时，入栈
        Push(s,q->lchild);
        q = q->lchild;
     }
     if(!Empty(s)){
        //当左孩子不存在，且栈非空
        GetTop(s,q);                                           //取出栈顶元素
        visit(q);                                              //访问栈顶元素
        Pop(s);                                                //将栈顶元素弹出
        q = q->rchild;                                         //遍历右孩子分支

     }
   }

   

}

void InOrder(BinNode *T, bool (*combine)(BinNode *node, const ElemType &elem),void (*visit)(BinNode* node)){
     // 重载版本，引入参数用于比较
     
     // 中序遍历，非递归
    /*
    思路：
    1、非递归要使用栈
    2、当节点的左孩子存在时，将他的左孩子入栈
    3、当节点的左孩子不存在时，访问当前节点
    4、将该节点的右孩子入栈
    5、直到将二叉树遍历完全并且栈为空
    */
   
   // 输入elem参数
   ElemType elem;
   cout << "input elem" <<endl;
   cin >> elem;
   //遍历函数
   Stack s;
   InitStack(s);
   BinNode* q = T;                                             //用于遍历二叉树
   while((q!=NULL) && (!Empty(s))){
     while(q!=NULL){
        //当左孩子存在时，入栈
        Push(s,q->lchild);
        q = q->lchild;
     }
     if(!Empty(s)){
        //当左孩子不存在，且栈非空
        GetTop(s,q);                                           //取出栈顶元素
        if(combine(q,elem)){
            visit(q);
        }                                              //访问栈顶元素
        Pop(s);                                                //将栈顶元素弹出
        q = q->rchild;                                         //遍历右孩子分支

     }
   }

}

void show(BinNode *node){
    //在遍历中，对每个元素进行操作
    cout << node->data <<endl;
}

void delete_node(BinNode *node){
    // 操作结果: 删除某个节点，并且包括所有后代
    /*
    原理：
    
    递归删除左子树和右子树
    */
   if(node){
    delete_node(node->lchild);
    delete_node(node->rchild);
   }
}

bool search_self(BinNode *node, const ElemType &elem){
    //操作结果 对比参数和二叉树节点
    if(node->data == elem){
        return true;

    }
    else return false;
}

bool search_father(BinNode *node, const ElemType &elem){
    // 操作结果:判断是否孩子结点元素是否为elem
    if(node->lchild->data == elem || node->rchild->data == elem){
        return true;
    }
    else return false;
}

void show_brother(BinNode *T, const ElemType &elem){
    cout << "input a elem search for brother:" <<endl;
   Stack s;
   InitStack(s);
   BinNode* q = T;                                             //用于遍历二叉树
   while((q!=NULL) && (!Empty(s))){
     while(q!=NULL){
        //当左孩子存在时，入栈
        Push(s,q->lchild);
        q = q->lchild;
     }
     if(!Empty(s)){
        //当左孩子不存在，且栈非空
        GetTop(s,q);                                           //取出栈顶元素
        if(q->lchild->data == elem){
            if(q->rchild){
                cout << q->rchild->data <<endl;
            }
        }
        if(q->rchild->data == elem){
            if(q->lchild){
                cout << q->lchild->data <<endl;
            }
        }                                                       //访问栈顶元素
        Pop(s);                                                //将栈顶元素弹出
        q = q->rchild;                                         //遍历右孩子分支

     }
   }
}
    

// 栈函数实现
void InitStack(Stack &S){
    //操作结果，初始化一个栈
    S.base =(BinNode*)malloc(STACKSIZE*sizeof(BinNode));                   //开辟一块内存
    if(S.base == NULL) cout<<"内存申请失败"<<endl;                               //内存申请失败
    S.top = S.base;                                                              //初始时 top与base重合
    
}

bool Empty(const Stack &S){
    if(S.base == S.top) return true;
    else return false;
}


bool Push(Stack &S,  BinNode *elem){
    
    S.top= elem;
    S.top++;
    return true;
}

bool Pop(Stack &S){
    
    S.top--;
    return true;
}

ElemType GetTop(const Stack &S, BinNode *elem){
    //操作结果 ：将顺序栈的栈顶元素返回给elem
    if(S.top == S.base){
        return false;
    }
    elem = (S.top-1);
    return true;
}

